/**
 * @brief UBF Header generator
 *
 * @file buildserver.h
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
#ifndef BUILDSERVER_H_
#define BUILDSERVER_H_
/*------------------------------Includes--------------------------------------*/
#include <utlist.h>
/*------------------------------Externs---------------------------------------*/
extern char ndrx_G_build_cmd[];
/*------------------------------Macros----------------------------------------*/
/*------------------------------Enums-----------------------------------------*/
/*------------------------------Typedefs--------------------------------------*/
/**
 * List of Function and Service names 
 */
typedef struct bs_svcnm_lst bs_svcnm_lst_t;
struct bs_svcnm_lst
{
    char svcnm[XATMI_SERVICE_NAME_LENGTH+1];
    char funcnm[128+1];
    int is_new_funcnm;
    EX_hash_handle hh; /* makes this structure hashable        */
};

/*------------------------------Globals---------------------------------------*/
/*------------------------------Statics---------------------------------------*/
/*------------------------------Prototypes------------------------------------*/
extern int ndrx_buildsrv_generate_code(char *cfile, int thread_option, 
                                       bs_svcnm_lst_t *p_svcnm_lst, 
                                       bs_svcnm_lst_t *p_funcnm_lst,
                                       char *p_xaswitch);

extern int ndrx_compile_srv_c(char *cfile, char *f_files, 
                              char *l_files, char *rm_libs);

extern int get_rm_name(char *p_xaswitch, char *p_rm_lastfiles, char *p_rm_name);

#endif /* BUILDSERVER_H_ */
/* vim: set ts=4 sw=4 et smartindent: */
