/**
 * @brief Generate code
 *
 * @file codegen.c
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
#include <atmi.h>

#include <ubf.h>
#include <ferror.h>
#include <fieldtable.h>
#include <fdatatype.h>

#include <ndrstandard.h>
#include <ndebug.h>
#include <errno.h>
#include "buildserver.h"
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/

/**
 * Generate C code for build server / build transaction manager
 * @param cfile - Auto generated buildeserver main code
 * @param thread_option - 
 * @param p_svcnm_lst - list of Srevice names
 * @param p_funcnm_lst - list of Function names
 * @param p_xaswitch - to phase commit function structure (optional may be NULL)
 * @return EXSUCCEED/EXFAIL
 */
expublic int ndrx_buildsrv_generate_code(char *cfile, int thread_option, 
                                        bs_svcnm_lst_t *p_svcnm_lst, 
                                        bs_svcnm_lst_t *p_funcnm_lst,
                                        char *p_xaswitch)
{
    int ret = EXSUCCEED;
    FILE *f = NULL;
    bs_svcnm_lst_t *bs, *bst;

    NDRX_LOG(log_info, "C-Code to compile: [%s]", cfile);

    if (NULL==(f=NDRX_FOPEN(cfile, "w")))
    {
        NDRX_LOG(log_error, "Failed to open for write [%s]: %s", 
                cfile, strerror(errno));
        EXFAIL_OUT(ret);
    }

    fprintf(f, "/* Buildserver auto-generated code */\n");
    fprintf(f, "/*---------------------------Includes-----------------------------------*/\n");
    fprintf(f, "#include <stdio.h>\n");
    fprintf(f, "#include <stdlib.h>\n");
    fprintf(f, "#include <ndebug.h>\n");
    fprintf(f, "#include <atmi.h>\n");
    fprintf(f, "#include <ndrstandard.h>\n");
    fprintf(f, "#include <ubf.h>\n");
    fprintf(f, "#include <string.h>\n");
    fprintf(f, "#include <unistd.h>\n");
    fprintf(f, "#include <xa.h>\n");
    
    fprintf(f, "/*---------------------------Externs------------------------------------*/\n");
    fprintf(f, "/* Buildserver auto generated extern service list */\n");

    /* Generate definitions */
    if (NULL!=p_xaswitch)
    {
        fprintf(f, "extern struct xa_switch_t %s;\n", p_xaswitch);
    }
    
    if (NULL != p_funcnm_lst)
    {
        EXHASH_ITER(hh, p_funcnm_lst, bs, bst)
        {
            fprintf(f, "extern void %s (TPSVCINFO *);\n", bs->funcnm);
        }
    }
    
    fprintf(f, "/*---------------------------Macros-------------------------------------*/\n");
    fprintf(f, "/*---------------------------Enums--------------------------------------*/\n");
    fprintf(f, "/*---------------------------Typedefs-----------------------------------*/\n");
    fprintf(f, "/*---------------------------Globals------------------------------------*/\n");
    fprintf(f, "/*---------------------------Statics------------------------------------*/\n");
    fprintf(f, "/* Auto generated system advertise table */\n");
    fprintf(f, "static struct tmdsptchtbl_t tmdsptchtbl[] = {\n");
    if (NULL != p_svcnm_lst)
    {
        EXHASH_ITER(hh, p_svcnm_lst, bs, bst)
        {
            fprintf(f, "    {\"%s\",\"%s\",(void (*)(TPSVCINFO *)) %s, 0, 0 },\n", 
                                    bs->svcnm, bs->funcnm, bs->funcnm);
        }
    }
    fprintf(f, "    { NULL, NULL, NULL, 0, 0 }\n");
    fprintf(f, "};\n");

    fprintf(f, "/*---------------------------Prototypes---------------------------------*/\n");
    fprintf(f, "\n");
    fprintf(f, "/* Buildserver main  */\n");
    fprintf(f, "int main( int argc, char** argv )\n");
    fprintf(f, "{\n");
    fprintf(f, "    _tmbuilt_with_thread_option=%d;\n",thread_option);
    fprintf(f, "    struct tmsvrargs_t tmsvrargs =\n");
    fprintf(f, "    {\n");
    fprintf(f, "        %s,\n", (NULL!=p_xaswitch?p_xaswitch:"NULL"));
    fprintf(f, "        &tmdsptchtbl[0],\n");
    fprintf(f, "        0,\n");
    fprintf(f, "        tpsvrinit,\n");
    fprintf(f, "        tpsvrdone,\n");
    fprintf(f, "        NULL,\n");
    fprintf(f, "        NULL,\n");
    fprintf(f, "        NULL,\n");
    fprintf(f, "        NULL,\n");
    fprintf(f, "        NULL\n");
    fprintf(f, "    };\n");
    fprintf(f, "    return( _tmstartserver( argc, argv, &tmsvrargs ));\n");
    fprintf(f, "}\n");

    NDRX_FCLOSE(f);
    f = NULL;

out:

    if (NULL!=f)
    {
        NDRX_FCLOSE(f);
    }

    return ret;
}

/**
 * Generate build client C code
 * @param cfile - Auto generated buildclient main code
 * @param p_svcnm_lst - list of Srevice names
 * @return EXSUCCEED/EXFAIL
 */
expublic int ndrx_buildclient_generate_code(char *cfile, char *p_xaswitch)
{
    int ret = EXSUCCEED;
    FILE *f = NULL;
    bs_svcnm_lst_t *bs, *bst;

    NDRX_LOG(log_info, "C-Code to compile: [%s]", cfile);

    if (NULL==(f=NDRX_FOPEN(cfile, "w")))
    {
        NDRX_LOG(log_error, "Failed to open for write [%s]: %s", 
                cfile, strerror(errno));
        EXFAIL_OUT(ret);
    }

    fprintf(f, "/* Buildclient auto-generated code */\n");
    fprintf(f, "/*---------------------------Includes-----------------------------------*/\n");
    fprintf(f, "#include <atmi.h>\n");
    fprintf(f, "#include <xa.h>\n");
    
    fprintf(f, "extern struct xa_switch_t *%s;\n", p_xaswitch);

    fprintf(f, "expublic struct tmsvrargs_t ndrx_G_tmsvrargs_stat = "
                "{%s, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL};\n",
                p_xaswitch);
    fprintf(f, "expublic struct tmsvrargs_t *ndrx_G_tmsvrargs = &ndrx_G_tmsvrargs_stat;\n");

    NDRX_FCLOSE(f);
    f = NULL;

out:

    if (NULL!=f)
    {
        NDRX_FCLOSE(f);
    }

    return ret;
}

/**
 * Get resource manager and libraries for xa_switch_name by rm_name
 * @param p_xaswitch
 * @param p_rm_lastfiles 
 * @param p_rm_name
 * @return EXSUCCEED/EXFAIL
 */
expublic int get_rm_name(char *p_xaswitch, char *p_rm_lastfiles, 
                         char *p_rm_name)
{
    int ret = EXSUCCEED;
    FILE *fp;
    char *env_ndrx_home;
    char *env_ndrx_rmfile;
    char ndrx_home_rmfile[PATH_MAX]={EXEOS};
    char *string = NULL;
    size_t len = 0;

    env_ndrx_rmfile=getenv("NDRX_RMFILE");

    if ( NULL!=env_ndrx_rmfile )
    {
        if (NULL==(fp=NDRX_FOPEN(env_ndrx_rmfile, "r")))
        {
            NDRX_LOG(log_error, "Failed to open NDRX_RMFILE [%s]: %s", 
                    env_ndrx_rmfile, strerror(errno));
            EXFAIL_OUT(ret);
        }
    }

    /* Close NDRX_RMFILE */
    NDRX_FCLOSE(fp);
    fp = NULL;

    if ( NULL == p_xaswitch )
    {
        
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
/* vim: set ts=4 sw=4 et smartindent: */
