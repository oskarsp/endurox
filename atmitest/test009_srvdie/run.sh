#!/bin/bash
##
## @brief @(#) Test009, Testing the case when server dies & queue is being removed.
##   The svcerr reply is passed back to client!#
##   THIS CURRENLTY COVERS THE CASE WHEN SHUTDOWN IS REQUESTED, SERVER EXISTS, BUT
##   MESSAGES ARE LEFT IN QUEUE, THEY WILL GOT SVCERR. BUT IN VERY CLEAN IMPLEMENTATION
##   WE MIGHT SET THE FLAG IN SHARED MEMORY THAT SERVICE IS NOT AVAILABLE, AND LEAVE ENQUEUED
##   ONES FOR PROCESSING.
##   But for current implementation SVCERR will be OK too, at last it is not a timeout!
##
## @file run.sh
##
## -----------------------------------------------------------------------------
## Enduro/X Middleware Platform for Distributed Transaction Processing
## Copyright (C) 2009-2016, ATR Baltic, Ltd. All Rights Reserved.
## Copyright (C) 2017-2018, Mavimax, Ltd. All Rights Reserved.
## This software is released under one of the following licenses:
## AGPL or Mavimax's license for commercial use.
## -----------------------------------------------------------------------------
## AGPL license:
## 
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU Affero General Public License, version 3 as published
## by the Free Software Foundation;
##
## This program is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
## PARTICULAR PURPOSE. See the GNU Affero General Public License, version 3
## for more details.
##
## You should have received a copy of the GNU Affero General Public License along 
## with this program; if not, write to the Free Software Foundation, Inc., 
## 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##
## -----------------------------------------------------------------------------
## A commercial use license is available from Mavimax, Ltd
## contact@mavimax.com
## -----------------------------------------------------------------------------
##

export TESTNO="009"
export TESTNAME_SHORT="srvdie"
export TESTNAME="test${TESTNO}_${TESTNAME_SHORT}"

PWD=`pwd`
if [ `echo $PWD | grep $TESTNAME ` ]; then
	# Do nothing 
	echo > /dev/null
else
	# started from parent folder
	pushd .
	echo "Doing cd"
	cd $TESTNAME
fi;

. ../testenv.sh

export TESTDIR="$NDRX_APPHOME/atmitest/$TESTNAME"
export PATH=$PATH:$TESTDIR
# Configure the runtime - override stuff here!
export NDRX_CONFIG=$TESTDIR/ndrxconfig.xml
export NDRX_DMNLOG=$TESTDIR/ndrxd.log
export NDRX_LOG=$TESTDIR/ndrx.log
export NDRX_DEBUG_CONF=$TESTDIR/debug.conf
# Override timeout!
export NDRX_TOUT=4

#
# Generic exit function
#
function go_out {
    echo "Test exiting with: $1"
    xadmin stop -y
    xadmin down -y

    # If some alive stuff left...
    xadmin killall atmiclt_$TESTNO

    popd 2>/dev/null
    exit $1
}

rm *.log

xadmin down -y
xadmin start -y || go_out 1

# Have some wait for ndrxd goes in service
sleep 1

atmiclt_$TESTNO &
atmiclt_$TESTNO &
atmiclt_$TESTNO &
atmiclt_$TESTNO &

sleep 6

# We should have in log files OK-TPETIME & OK-TPESVCERR

if [ "X`grep OK-TPESVCERR *.log`" == "X" ]; then
	echo "Test error detected - no entry of OK-TPESVCERR!"
	go_out 2
fi

if [ "X`grep OK-TPETIME *.log`" == "X" ]; then
	echo "Test error detected - no entry of OK-TPETIME!"
	go_out 3
fi

# Catch is there is test error!!!
if [ "X`grep TESTERROR *.log`" != "X" ]; then
	echo "Test error detected!"
	go_out 4
fi

go_out 0

# vim: set ts=4 sw=4 et smartindent:
