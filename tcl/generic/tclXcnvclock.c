/* 
 * tclXcnvclock.c --
 *
 *      Contains the TCL convertclock command.  This is in a module seperate
 * from clock so that it can be excluded, along with the yacc generated code,
 * since its rather large.
 *-----------------------------------------------------------------------------
 * Copyright 1991-1993 Karl Lehenbauer and Mark Diekhans.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies.  Karl Lehenbauer and
 * Mark Diekhans make no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 *-----------------------------------------------------------------------------
 * $Id: tclXcnvclock.c,v 2.4 1993/03/06 21:42:30 markd Exp markd $
 *-----------------------------------------------------------------------------
 */

#include "tclExtdInt.h"

static int
GetTimeZone _ANSI_ARGS_((time_t  currentTime));


/*
 *-----------------------------------------------------------------------------
 *
 * GetTimeZone --
 *   Determines the current timezone.  The method varies wildly between
 * different Unix implementations, so its hidden in this function.
 *
 * Parameters:
 *   o currentTime (I) - The clock value that is to be used for the current
 *     time.
 * 
 * Returns:
 *    Minutes east of GMT.
 *-----------------------------------------------------------------------------
 */
static int
GetTimeZone (currentTime)
    time_t  currentTime;
{
#ifdef TCL_USEGETTOD
    struct timeval tv;
    struct timezone tz;

    gettimeofday( &tv, &tz );
    return tz.tz_minuteswest;
#else
    struct tm  *timeDataPtr = localtime (&currentTime);

#ifdef TCL_TM_GMTOFF
    return -(timeDataPtr->tm_gmtoff / 60);
#endif
#ifdef TCL_TIMEZONE_VAR 
    return timezone / 60;
#endif
#if !defined(TCL_TM_GMTOFF) && !defined(TCL_TIMEZONE_VAR)
    return timeDataPtr->tm_tzadj  / 60;
#endif
#endif
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_ConvertclockCmd --
 *     Implements the TCL convertclock command:
 *         convertclock dateString ?GMT|{}?
 *
 * Results:
 *     Standard TCL results.
 *
 *-----------------------------------------------------------------------------
 */
int
Tcl_ConvertclockCmd (clientData, interp, argc, argv)
    ClientData  clientData;
    Tcl_Interp *interp;
    int         argc;
    char      **argv;
{
    long        clockVal;
    time_t      baseClock;
    int         zone;

    if ((argc < 2) || (argc > 4)) {
        Tcl_AppendResult (interp, tclXWrongArgs, argv [0], 
                          " dateString ?GMT|{}? ?baseclock?", (char *) NULL);
	return TCL_ERROR;
    }
    if (argc == 4) {
        if (Tcl_GetLong (interp, argv [3], &baseClock) != TCL_OK)
            return TCL_ERROR;
    } else
        time (&baseClock);

    if ((argc > 2) && (argv [2][0] != '\0')) {
        if (!STREQU (argv [2], "GMT")) {
            Tcl_AppendResult (interp, "invalid argument: expected `GMT', ",
                              "got : `", argv [2], "'", (char *) NULL);
            return TCL_ERROR;
        }
        zone = 0; /* Zero minutes from GMT */
    } else {
        zone = GetTimeZone (baseClock);
    }

    if (Tcl_GetDate (argv [1], baseClock, zone, &clockVal) < 0) {
        Tcl_AppendResult (interp, "Unable to convert date-time string \"",
                          argv [1], "\"", (char *) NULL);
	return TCL_ERROR;
    }
    sprintf (interp->result, "%ld", clockVal);
    return TCL_OK;
}

