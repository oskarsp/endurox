#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <ndebug.h>
#include <atmi.h>


#include <ubf.h>
#include <Exfields.h>
#include <test.fd.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/

#ifndef SUCCEED
#define SUCCEED			0
#endif

#ifndef	FAIL
#define FAIL			-1
#endif



/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/


/**
 * Service entry
 * @return SUCCEED/FAIL
 */
int TESTSV (TPSVCINFO *p_svc)
{
	int ret = SUCCEED;
	

	UBFH *p_ub = (UBFH *)p_svc->data;

	tplogprintubf(log_info, "Got request", p_ub);
	
	
	/* allocate some stuff for more data to put in  */
	if (NULL==(p_ub = (UBFH *)tprealloc((char *)p_ub, 4096)))
	{
		ret=FAIL;
		goto out;
	}

	d+=1;

	if (FAIL==Badd(p_ub, T_DOUBLE_FLD, (char *)&d, 0))
	{
		ret=FAIL;
		goto out;
	}

	TP_LOG(log_info, "Got response from server: [%s]", retbuf);
	
out:

	tpreturn(  ret==SUCCEED?TPSUCCESS:TPFAIL,
		0L,
		(char *)p_ub,
		0L,
		0L);



}

/**
 * Initialize the application
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int init(int argc, char** argv)
{
	int ret = SUCCEED;

	TP_LOG(log_info, "Initializing...");

	if (SUCCEED!=tpinit(NULL))
	{
		TP_LOG(log_error, "Failed to Initialize: %s", 
			tpstrerror(tperrno));
		ret = FAIL;
		goto out;
	}
	

	
	/* Advertise our service */
	if (SUCCEED!=tpadvertise("TESTSV", "TESTSV"))
	{
		TP_LOG(log_error, "Failed to initialize TESTSV!");
		ret=FAIL;
		goto out;
	}	

out:

	
	return ret;
}

/**
 * Terminate the application
 */
void uninit(int status)
{
	int ret = SUCCEED;
	
	TP_LOG(log_info, "Uninitializing...");
	
	ret = tpterm();
	
	return ret;
}

/**
 * Server program main entry
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int main(int argc, char** argv)
{
	/* Launch the Enduro/x thread */
	return ndrx_main_integra(argc, argv, init, uninit, 0);
}

