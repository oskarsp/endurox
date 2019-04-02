/**
 * @brief Part of UBF library
 *   Utility for generating field header files.
 *   Also the usage of default `fld.tbl' is not supported, as seems to be un-needed
 *   feature.
 *
 * @file buildserver.c
 */
/* -----------------------------------------------------------------------------
 * Enduro/X Middleware Platform for Distributed Transaction Processing
 * Copyright (C) 2009-2016, ATR Baltic, Ltd. All Rights Reserved.
 * Copyright (C) 2017-2018, Mavimax, Ltd. All Rights Reserved.
 * This software is released under one of the following licenses:
 * AGPL or Mavimax's license for commercial use.
 * -----------------------------------------------------------------------------
 * AGPL license:
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License, version 3 as published
 * by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Affero General Public License, version 3
 * for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * -----------------------------------------------------------------------------
 * A commercial use license is available from Mavimax, Ltd
 * contact@mavimax.com
 * -----------------------------------------------------------------------------
 */

/*---------------------------Includes-----------------------------------*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ndrx_config.h>
#include <atmi.h>
#include <atmi_int.h>
#include <sys_unix.h>
#include <ctype.h>

#include <ubf.h>
#include <ferror.h>
#include <fieldtable.h>
#include <fdatatype.h>

#include <ndrstandard.h>
#include <ndebug.h>
#include "buildserver.h"

/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
expublic char ndrx_G_build_cmd[PATH_MAX+1] = "cc";
/*---------------------------Statics------------------------------------*/

/**
 * Function to parse Service/Function from string 
 * @param s_value string to be parsed
 * @param advtbl advertising table to return
 * @return 
 */
exprivate int parse_s_string(char *p_string, bs_string_list_t *bs_list)
{
    int ret = EXSUCCEED;
    char srvcnm[128+1]={EXEOS};
    char funcnm[15+1]={EXEOS};
    char *f, *p, *str=NULL;
    bs_string_list_t tmp;

    f=strchr(p_string, ':');
    if (NULL != f)
    {
        NDRX_STRCPY_SAFE(funcnm, f+1);
    }

    for (p = strtok_r(p_string, ",:", &str); 
         p != NULL && (0!=strcmp(f+1,p) ); 
         p = strtok_r(NULL, ",:", &str))
    {
        if (NULL != f)
        {
            NDRX_STRCPY_SAFE(tmp.funcnm, f+1);
        }
        else 
        {
            NDRX_STRCPY_SAFE(tmp.funcnm, p);
        }
        NDRX_STRCPY_SAFE(tmp.srvcnm, p);

        LL_APPEND(bs_list, tmp);
        NDRX_LOG(log_debug, "SVCNM=[%s] FUNCNM=[%s]\n", advtbl.svcnm, advtbl.funcnm);
    }

    out:
    return ret;
}

/**
 * Function to read Service/Function from file
 * @param s_value File name to load Services/Function
 * @param advtbl advertising table to return
 * @return EXSUCCEED/EXFAIL
 */
exprivate int parse_s_file(char *infile, bs_string_list_t *bs_list)
{
    int ret = EXSUCCEED;
    FILE * fp;
    char *string = NULL;
    size_t len = 0;

    if (NULL==(fp=NDRX_FOPEN(infile+1, "r")))
    {
        NDRX_LOG(log_error, "Failed to open file [%s] for reading: %s", 
                infile+1, strerror(errno));
        EXFAIL_OUT(ret);
    }

    while (EXFAIL != ndrx_getline(&string, &len, fp))
    {
        ndrx_str_rstrip(string," \t\n");
NDRX_LOG(log_error, "Parse string [%s] len=[%d]", string, (int)len);
        if ('#'==string[0])
        {
            NDRX_LOG(log_error, "Skip comment [%s]", string);
        }
        else if ( EXSUCCEED!= parse_s_string(string, list) )
        {
            EXFAIL_OUT(ret);
        }
    }

out:
    NDRX_FCLOSE(fp);
    fp = NULL;

    if (NULL!=string)
    {
        NDRX_FREE(string);
    }

    return ret;
}

/**
 * Main entry point for view compiler
 */
int main(int argc, char **argv)
{
    int ret = EXSUCCEED;
    int i;
    int c;
    int lang_mode = HDR_C_LANG;
    char ofile[PATH_MAX+1]="SERVER";
    char cfile[PATH_MAX+1]="ndrx_bs_XXXXXX.c";
    FILE *f=NULL;
    char *env_cc, *env_cflags, *env_ndrx_home;
    char ndrx_lib[PATH_MAX+1]={EXEOS};
    char ndrx_inc[PATH_MAX+1]={EXEOS};
    char *s_value=NULL, *f_value=NULL, *l_value=NULL;
    char svcnm[15+1]={EXEOS};
    char funcnm[128+1]={EXEOS};
    char tmp[PATH_MAX];
    int thread_option=EXFALSE;
    int keep_buildserver_main=EXFALSE;
    bs_string_list_t *bs_list=NULL;
    char build_cmd[PATH_MAX+1];
    
    NDRX_BANNER;
    
    fprintf(stderr, "BUILDSERVER Compiler\n\n");

    while ((c = getopt (argc, argv, "Cktvrgs:o:f:l:")) != -1)
    {
        switch (c)
        {
            case 'C':
                NDRX_LOG(log_warn, "Ignoring option C for COBOL");
                break;
            case 's':
                s_value= optarg;
                if ( '@'==s_value[0] )
                {
                    if (EXSUCCEED != parse_s_file(s_value, bs_list) )
                    {
                        NDRX_LOG(log_warn, 
                             "Failed to read Service/Function from [%s]", 
                             s_value);
                        EXFAIL_OUT(ret);
                    }
                }
                else 
                {
                    if ( EXSUCCEED != parse_s_string(s_value, bs_list) )
                    {
                        NDRX_LOG(log_warn, 
                             "Failed to {parse Service(s)/Function from value ", 
                             s_value);
                        EXFAIL_OUT(ret);
                    }
                }
                break;
            case 'o':
                NDRX_STRCPY_SAFE(ofile, optarg);
                NDRX_LOG(log_debug, "ofile: [%s]", ofile);
                break;
            case 'f':
                f_value = optarg;
                break;
            case 'l':
                l_value = optarg;
                break;
            case 'r':
            case 'g':
                NDRX_LOG(log_error, "ERROR! Please use tmsrv with corresponding "
                    "shared libraries! No need to build resource manager.");
                EXFAIL_OUT(ret);
                break;
            case 'k':
                keep_buildserver_main=EXTRUE;
                break;
            case 't':
                thread_option = EXTRUE;
                break;
            case 'v':
                fprintf(stderr, "Debug output shall be configured in "
                    "ndrxdebug.conf or CCONFIG\n");
                break;
            case '?':
                EXFAIL_OUT(ret);
            default:
                NDRX_LOG(log_error, "Default case...");
                EXFAIL_OUT(ret);
        }
    }
    
    /* Plot the the header */
    if (HDR_C_LANG==lang_mode)
    {
        if ( EXFAIL==mkstemps(cfile,2) )
        {
            NDRX_LOG(log_error, "Failed with error %s\n", strerror(errno));
            EXFAIL_OUT(ret);
        }
        
        if (EXSUCCEED!=ndrx_buildserver_generate_code(cfile, thread_option, bs_list))
        {
            NDRX_LOG(log_error, "Failed to generate code!");
            EXFAIL_OUT(ret);
        }
    }
    env_cc = getenv("CC");
    if (NULL!=env_cc && env_cc[0]!=0)
    {
        snprintf(ndrx_G_build_cmd, sizeof(ndrx_G_build_cmd), "%s", env_cc);
    }
    env_cflags = getenv("CFLAGS");
    env_ndrx_home = getenv("NDRX_HOME");

    if (NULL!=env_ndrx_home && env_ndrx_home[0]!=0)
    {
        snprintf(ndrx_lib, sizeof(ndrx_lib), "-I%s/include", env_ndrx_home);
        snprintf(ndrx_inc, sizeof(ndrx_inc), "-L%s/lib", env_ndrx_home);
    }
        
    NDRX_LOG(log_debug, "Build command set to: [%s]", ndrx_G_build_cmd);

    snprintf(build_cmd, sizeof(build_cmd), 
             "%s "      /* C language compilation command */
             "%s "      /* CFLAGS */
             "-o %s "   /* outfile */
             "%s "      /* generated C file with main() */
             "%s "      /* ndrx_home/include */
             "%s "      /* ndrx_home/lib */
             "%s "      /* First files */
             "%s "      /* EnduroX specific libraries */
             "%s ",     /* Last Files */
             ndrx_G_build_cmd,
             (NULL==env_cflags?"":env_cflags),
             ofile,
             NULL!=cfile,
             ndrx_inc,
             ndrx_lib, 
             f_value,
             "-l$atmisrv -latmi -lubf -lnstd $dyn_libs -lm -lc -lpthread ", /* TODO */
             l_value
        );
    
    NDRX_LOG(log_debug, "build_cmd: [%s]", build_cmd);
    
out:

    if (EXFALSE == keep_buildserver_main)
    {
        unlink(cfile);
    }

    return ret;
}

/* vim: set ts=4 sw=4 et smartindent: */
