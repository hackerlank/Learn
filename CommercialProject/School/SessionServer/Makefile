PROJECT_TOP_DIR = $(shell cd ../; pwd)
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)
PROJECT_LIB_DIR = ../base -L../common -L../protol
CFLAGS         := -g -I$(PROJECT_INC_DIR) -I/usr/include/mysql/include/

LDFLAG         := -L$(PROJECT_LIB_DIR) -lbase -lcommon -lprotol -L/usr/lib/mysql/ -lpthread -lrt -lmysqlclient

DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
src =  SessionServer.cpp\
	   sessionTimeTick.cpp\
	   recordClient.cpp\
	   sessionTask.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

SessionServer: $(object)
	$(LINK) $(CFLAGS) $(object) -o SessionServer $(LDFLAG)

$(object) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	 $(DEL_FILE) SessionServer 

.PHONY : clean
clean:
	 $(DEL_FILE) $(object)
	 $(DEL_FILE) $(depend)
	 $(DEL_FILE) SessionServer 

