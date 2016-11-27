####### Compiler, tools and options

PROJECT_TOP_DIR = $(shell cd ../; pwd)  
PROJECT_BIN_DIR = $(PROJECT_TOP_DIR) 
PROJECT_SRC_DIR = $(PROJECT_TOP_DIR)  
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)  
PROJECT_LIB_DIR = $(PROJECT_TOP_DIR)  
CFLAGS         := -g -I$(PROJECT_INC_DIR)  
LDFLAG         := -L$(PROJECT_LIB_DIR)  

DEL_FILE      = rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar

####### Files
src = test.cpp\
	  main.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))
libtest.a : $(object) $(depend)
	$(AR) -rcs libtest.a $(object)
$(object) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@
$(depend) : %.d : %.cpp
	$(CXX) -MM $<  >$@
-include $(depend)
clean:
	$(DEL_FILE) $(object) 
	$(DEL_FILE) $(depend)
	$(DEL_FILE) libtest.a 

