#
# tkdemo --
#
# Run the Tk demo at anytime after Extended Tcl is installed.
# 
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
# $Id: tkdemo.tcl,v 3.0 1993/11/19 07:01:10 markd Rel markd $
#------------------------------------------------------------------------------
#

#@package: Tk-demo tkdemo

proc tkdemo {} {
    global auto_path
    if {[info commands tkwait] == ""} {
        error "tkdemo may only be used from wishx"
    }
    set demos [searchpath $auto_path demos]
    if {$demos == "" || ![file isdirectory $demos]} {
        error "can't find Tk `demos' directory on the auto_path (auto_path):
    }
    uplevel #0 source $demos/widget
}


