PROJECT_TOP_DIR = $(shell cd ../; pwd)
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)
PROJECT_LIB_DIR = ../base
CFLAGS         := -g -I$(PROJECT_INC_DIR) -I/usr/include/mysql/include/

LDFLAG         := -L$(PROJECT_LIB_DIR) -lbase -L/usr/lib/mysql/ -lpthread -lrt -lmysqlclient

DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
src = main.cpp\
	  SuperServer.cpp\
	  superTimeTick.cpp\
	  superTask.cpp\
	  superTaskManager.cpp\
	  plateClient.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

SuperServer : $(object)
	$(LINK) $(CFLAGS) $(object) -o SuperServer $(LDFLAG)

$(object) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	 $(DEL_FILE) SuperServer

.PHONY : clean
clean:
	 $(DEL_FILE) $(object)
	 $(DEL_FILE) $(depend)
	 $(DEL_FILE) SuperServer

