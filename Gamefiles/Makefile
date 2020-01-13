#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := game.cpp inputHandler.cpp objectStorage.cpp collisionBox.cpp

# header files in this project

HEADERS := game.hpp renderer.hpp circle.hpp command.hpp gameObject.hpp gameStorage.hpp inputHandler.hpp moveCommand.hpp floor.hpp objectStorage.hpp collisionBox.hpp

# other places to look for files for this project
SEARCH  := 

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)/Makefile.native
