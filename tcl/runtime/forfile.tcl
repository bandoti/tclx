#
# forfile.tcl --
#
# Proc to execute code on every line of a file.
#------------------------------------------------------------------------------
# Copyright 1992-1994 Karl Lehenbauer and Mark Diekhans.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation for any purpose and without fee is hereby granted, provided
# that the above copyright notice appear in all copies.  Karl Lehenbauer and
# Mark Diekhans make no representations about the suitability of this
# software for any purpose.  It is provided "as is" without express or
# implied warranty.
#------------------------------------------------------------------------------
# $Id: forfile.tcl,v 3.0 1993/11/19 07:00:24 markd Rel markd $
#------------------------------------------------------------------------------
#

#@package: TclX-forfile for_file

proc for_file {var filename code} {
    upvar $var line
    set fp [open $filename r]
    while {[gets $fp line] >= 0} {
        uplevel $code
    }
    close $fp
}

