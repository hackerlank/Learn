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
src = GatewayServer.cpp\
	  gateTimeTick.cpp\
	  sessionClient.cpp\
	  recordClient.cpp\
	  gateTask.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

GatewayServer : $(object)
	$(LINK) $(CFLAGS) $(object) -o GatewayServer $(LDFLAG)

$(object) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	 $(DEL_FILE) GatewayServer

.PHONY : clean
clean:
	 $(DEL_FILE) $(object)
	 $(DEL_FILE) $(depend)
	 $(DEL_FILE) GatewayServer

