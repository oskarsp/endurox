package main

import (
	"errors"
	"fmt"
	"os"
	"time"
	u "ubftab"

	atmi "github.com/endurox-dev/endurox-go"
)

/*
#include <signal.h>
*/
import "C"

const (
	ProgSection = "tpscl"
	TargetTps   = 1000
)

var MSomeConfigFlag string = ""
var MSomeOtherConfigFlag int = 0

//Get UTC milliseconds since epoch
//@return epoch milliseconds
func GetEpochMillis() int64 {
	now := time.Now()
	nanos := now.UnixNano()
	millis := nanos / 1000000

	return millis
}

//About incoming & outgoing messages:
type StopWatch struct {
	start int64 //Timestamp messag sent
}

//Reset the stopwatch
func (s *StopWatch) Reset() {
	s.start = GetEpochMillis()
}

//Get delta milliseconds
//@return time spent in milliseconds
func (s *StopWatch) GetDeltaMillis() int64 {
	return GetEpochMillis() - s.start
}

//Get delta seconds of the stopwatch
//@return return seconds spent
func (s *StopWatch) GetDetlaSec() int64 {
	return (GetEpochMillis() - s.start) / 1000
}

//Run the listener
func apprun(ac *atmi.ATMICtx) error {

	//Do some work here
	var feedback StopWatch
	var printTime StopWatch

	feedback.Reset()

	var calls_made float64 = 0.0
	var current_tps float64 = 0.0

	buf, err := ac.NewUBF(1024)

	var sleepMicroSec = 1

	for true {

		if err != nil {
			return errors.New(err.Error())
		}

		//Set some field for call
		if err := buf.BChg(u.EX_IF_EMSG, 0, "Hello world!"); nil != err {
			return errors.New(err.Error())
		}

		//Call the server
		if _, err := ac.TpCall("ECHO", buf, 0); nil != err {
			return errors.New(err.Error())
		}

		calls_made++

		time.Sleep(time.Duration(sleepMicroSec) * time.Microsecond)

		if feedback.GetDeltaMillis() > 400 {

			current_tps = float64(calls_made) /
				(float64(feedback.GetDeltaMillis()) / 1000.0)

			//Measure current tps...
			if current_tps > TargetTps {

				/*
					fmt.Printf("DEC: Current tps millis [%f], calls made: [%f], time:%d/%f sleep: %d\n",
						current_tps, calls_made, feedback.GetDeltaMillis(),
						float64(float64(feedback.GetDeltaMillis())/1000.0), sleepMicroSec)
				*/

				sleepMicroSec += 100
			} else {

				/*
					fmt.Printf("INC: Current tps millis [%f], calls made: [%f], time:%d/%f sleep: %d \n",
						current_tps, calls_made, feedback.GetDeltaMillis(),
						float64(float64(feedback.GetDeltaMillis())/1000.0), sleepMicroSec)
				*/

				sleepMicroSec -= 100
			}

			feedback.Reset()
			calls_made = 0
		}

		if printTime.GetDetlaSec() >= 1 {

			fmt.Printf("Current tps: [%f]\n", current_tps)
			printTime.Reset()
		}
	}

	return nil
}

//Init function
//@param ac	ATMI context
//@return error (if erro) or nil
func appinit(ac *atmi.ATMICtx) error {

	if err := ac.TpInit(); err != nil {
		return errors.New(err.Error())
	}

	return nil
}

//Un-init & Terminate the application
//@param ac	ATMI Context
//@param restCode	Return code. atmi.FAIL (-1) or atmi.SUCCEED(0)
func unInit(ac *atmi.ATMICtx, retCode int) {

	ac.TpTerm()
	ac.FreeATMICtx()
	os.Exit(retCode)
}

//Cliet process main entry
func main() {

	ac, errA := atmi.NewATMICtx()

	if nil != errA {
		fmt.Fprintf(os.Stderr, "Failed to allocate cotnext %d:%s!\n",
			errA.Code(), errA.Message())
		os.Exit(atmi.FAIL)
	}

	if err := appinit(ac); nil != err {
		ac.TpLogError("Failed to init: %s", err)
		os.Exit(atmi.FAIL)
	}

	ac.TpLogWarn("Init complete, processing...")

	if err := apprun(ac); nil != err {
		unInit(ac, atmi.FAIL)
	}

	unInit(ac, atmi.SUCCEED)
}
