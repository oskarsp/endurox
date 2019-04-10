/**
 * @brief 
 *   
 *
 * @file compile_c.c
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
#include <typed_view.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
extern int ndrx_compile_c(char *cfile, int compile_type)
{
    int ret=EXSUCCEED;
    

#if 0
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
#endif 
    
    
    return ret;
}