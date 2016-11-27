####### Compiler, tools and options

PROJECT_TOP_DIR = $(shell cd ../; pwd)  
#PROJECT_BIN_DIR = ../common 
#PROJECT_SRC_DIR = $(PROJECT_TOP_DIR)  
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)
PROJECT_LIB_DIR = ../common 
#PROJECT_OBJ_DIR = $(PROJECT_BIN_DIR)
CFLAGS         := -g -I$(PROJECT_INC_DIR) 
LDFLAG         := -L$(PROJECT_LIB_DIR) -ltest  

DEL_FILE      = rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar

####### Files
object = func.o\
		 main.o

edit : $(object)
	$(LINK) $(CFLAGS) $(object) -o edit $(LDFLAG)
func.o : func.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ 
main.o : main.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ 
clean:
	$(DEL_FILE) $(object) 
	$(DEL_FILE) edit     
