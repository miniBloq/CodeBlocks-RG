
# ---------------------------------------------------------------------------
#
#   Filename: testapp Makefile
#   Project: wxWebConnect
#   (C) Copyright 2009, Kirix Corporation, All Rights Reserved.
#
#   Developer(s):       Benjamin I. Williams
#
#   Changes:
#
#	5 May 2009 - Created
#
# ---------------------------------------------------------------------------


# These two settings need to be adjusted to your build environment
WX_DIR := ../wxWidgets
WX_CONFIG := ${WX_DIR}/wx-config --libs




WX_CFLAGS := $(shell ${WX_CONFIG} --prefix=${WX_DIR} --cppflags)
WX_LIBS := $(shell ${WX_CONFIG} --prefix=${WX_DIR} --libs)

EXENAME = testapp
INCLUDES = 
CPP = g++
CFLAGS = -ggdb $(WX_CFLAGS)
LIBS = -L../webconnect -lwebconnect $(WX_LIBS)
DEPENDLIBS = ../webconnect/libwebconnect.a 

OBJECTS = testapp.o

all: $(EXENAME)
    
$(EXENAME): $(OBJECTS) $(DEPENDLIBS)
		$(CPP) $(OBJECTS) $(LIBDIRS) $(LIBS) -o $(EXENAME)

clean:
	rm -f *.o *.gch $(EXENAME)

$(OBJECTS): %.o : %.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<


