package ubftab

/* 
** Enduro/X internal UBF field table
**
** @file Exfields.h
** 
** -----------------------------------------------------------------------------
** Enduro/X Middleware Platform for Distributed Transaction Processing
** Copyright (C) 2015, ATR Baltic, SIA. All Rights Reserved.
** This software is released under one of the following licenses:
** GPL or ATR Baltic's license for commercial use.
** -----------------------------------------------------------------------------
** GPL license:
** 
** This program is free software; you can redistribute it and/or modify it under
** the terms of the GNU General Public License as published by the Free Software
** Foundation; either version 2 of the License, or (at your option) any later
** version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
** PARTICULAR PURPOSE. See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with
** this program; if not, write to the Free Software Foundation, Inc., 59 Temple
** Place, Suite 330, Boston, MA 02111-1307 USA
**
** -----------------------------------------------------------------------------
** A commercial use license is available from ATR Baltic, SIA
** contact@atrbaltic.com
** -----------------------------------------------------------------------------
*/
/*	fname	bfldid            */
/*	-----	-----            */
const (
	SRVCNM = 167772261 /* number: 101 type: string */
	EV_FLAGS = 33554536 /* number: 104 type: long */
	EV_MASK = 167772265 /* number: 105 type: string */
	EV_FILTER = 167772266 /* number: 106 type: string */
	EV_SRVCNM = 167772267 /* number: 107 type: string */
	EV_SUBSNR = 33554540 /* number: 108 type: long */
	EXDM_RESTARTS = 33554547 /* number: 115 type: long */
	TMCMD = 67108984 /* number: 120 type: char */
	TMXID = 167772281 /* number: 121 type: string */
	TMRMID = 123 /* number: 123 type: short */
	TMNODEID = 122 /* number: 122 type: short */
	TMSRVID = 124 /* number: 124 type: short */
	TMKNOWNRMS = 167772285 /* number: 125 type: string */
	TMERR_CODE = 130 /* number: 130 type: short */
	TMERR_REASON = 131 /* number: 131 type: short */
	TMERR_MSG = 167772292 /* number: 132 type: string */
	TMPROCESSID = 167772310 /* number: 150 type: string */
	TMCALLERRM = 151 /* number: 151 type: short */
	TMTXTOUT = 33554584 /* number: 152 type: long */
	TMTXTOUT_LEFT = 33554585 /* number: 153 type: long */
	TMTXSTAGE = 154 /* number: 154 type: short */
	TMTXRMID = 155 /* number: 155 type: short */
	TMTXRMSTATUS = 67109020 /* number: 156 type: char */
	TMTXRMERRCODE = 33554589 /* number: 157 type: long */
	TMTXRMREASON = 158 /* number: 158 type: short */
	TMTXTRYCNT = 33554591 /* number: 159 type: long */
	TMTXTRYMAXCNT = 33554592 /* number: 160 type: long */
	TMTXFLAGS = 33554593 /* number: 161 type: long */
	EX_CPMCOMMAND = 167772360 /* number: 200 type: string */
	EX_CPMOUTPUT = 167772361 /* number: 201 type: string */
	EX_CPMTAG = 167772362 /* number: 202 type: string */
	EX_CPMSUBSECT = 167772363 /* number: 203 type: string */
	EX_CLTID = 167772410 /* number: 250 type: string */
	EX_DATA = 201326843 /* number: 251 type: carray */
	EX_DATA_BUFTYP = 252 /* number: 252 type: short */
	EX_TSTAMP1_STR = 167772413 /* number: 253 type: string */
	EX_TSTAMP2_STR = 167772414 /* number: 254 type: string */
	EX_DATA_STR = 167772415 /* number: 255 type: string */
	EX_QSPACE = 167772460 /* number: 300 type: string */
	EX_QNAME = 167772461 /* number: 301 type: string */
	EX_QFLAGS = 33554734 /* number: 302 type: long */
	EX_QDEQ_TIME = 33554735 /* number: 303 type: long */
	EX_QPRIORITY = 33554736 /* number: 304 type: long */
	EX_QDIAGNOSTIC = 33554737 /* number: 305 type: long */
	EX_QMSGID = 201326898 /* number: 306 type: carray */
	EX_QCORRID = 201326899 /* number: 307 type: carray */
	EX_QREPLYQUEUE = 167772468 /* number: 308 type: string */
	EX_QFAILUREQUEUE = 167772469 /* number: 309 type: string */
	EX_QURCODE = 33554742 /* number: 310 type: long */
	EX_QAPPKEY = 33554743 /* number: 311 type: long */
	EX_QDELIVERY_QOS = 33554744 /* number: 312 type: long */
	EX_QREPLY_QOS = 33554745 /* number: 313 type: long */
	EX_QEXP_TIME = 33554746 /* number: 314 type: long */
	EX_QCMD = 67109179 /* number: 315 type: char */
	EX_QDIAGMSG = 167772476 /* number: 316 type: string */
	EX_QNUMMSG = 33554749 /* number: 317 type: long */
	EX_QNUMLOCKED = 33554750 /* number: 318 type: long */
	EX_QNUMSUCCEED = 33554751 /* number: 319 type: long */
	EX_QNUMFAIL = 33554752 /* number: 320 type: long */
	EX_QSTRFLAGS = 167772481 /* number: 321 type: string */
	EX_QMSGTRIES = 33554754 /* number: 322 type: long */
	EX_QMSGLOCKED = 323 /* number: 323 type: short */
	EX_QMSGIDSTR = 167772484 /* number: 324 type: string */
	EX_QNUMENQ = 33554757 /* number: 325 type: long */
	EX_QNUMDEQ = 33554758 /* number: 326 type: long */
	EX_NERROR_CODE = 400 /* number: 400 type: short */
	EX_NERROR_MSG = 167772561 /* number: 401 type: string */
	EX_NREQLOGFILE = 167772562 /* number: 402 type: string */
	EX_CC_CMD = 67109364 /* number: 500 type: char */
	EX_CC_RESOURCE = 167772661 /* number: 501 type: string */
	EX_CC_LOOKUPSECTION = 167772662 /* number: 502 type: string */
	EX_CC_SECTIONMASK = 167772663 /* number: 503 type: string */
	EX_CC_MANDATORY = 167772664 /* number: 504 type: string */
	EX_CC_FORMAT_KEY = 167772665 /* number: 505 type: string */
	EX_CC_FORMAT_FORMAT = 167772666 /* number: 506 type: string */
	EX_CC_SECTION = 167772669 /* number: 509 type: string */
	EX_CC_KEY = 167772670 /* number: 510 type: string */
	EX_CC_VALUE = 167772671 /* number: 511 type: string */
	EX_IF_ECODE = 600 /* number: 600 type: short */
	EX_IF_EMSG = 167772761 /* number: 601 type: string */
	EX_NETDATA = 201327242 /* number: 650 type: carray */
	EX_NETGATEWAY = 167772811 /* number: 651 type: string */
	EX_NETCONNID = 33555084 /* number: 652 type: long */
	EX_NETCORR = 167772813 /* number: 653 type: string */
	EX_NETFLAGS = 167772814 /* number: 654 type: string */
)
