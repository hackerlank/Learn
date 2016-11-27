PROJECT_TOP_DIR = $(shell cd ../; pwd)
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)
PROJECT_LIB_DIR = $(PROJECT_TOP_DIR)
CFLAGS         := -g -I$(PROJECT_INC_DIR)

LDFLAG         := -L$(PROJECT_LIB_DIR) 
DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar
####### Files
src = main.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

libcommon.a : $(object)
	$(AR) -rcs libcommon.a $(object)

$(object) : %.o : %.cpp
	 $(CXX) -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	 $(DEL_FILE) libcommon.a

.PHONY : clean
clean:
	 $(DEL_FILE) $(object)
	 $(DEL_FILE) $(depend)
	 $(DEL_FILE) libcommon.a

