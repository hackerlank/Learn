######## compiler, tools and options
PROJECT_TOP_DIR = $(shell cd ../; pwd)
PROJECT_BIN_DIR = $(PROJECT_TOP_DIR)
PROJECT_SRC_DIR = $(PROJECT_TOP_DIR)
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)
PROJECT_LIB_DIR = ../protol
CFLAGS         := -g -I$(PROJECT_INC_DIR) -I/usr/include/mysql/include/

LDFLAG         := -L$(PROJECT_LIB_DIR) -lprotol
DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar

####### Files
src = main.cpp\
	  baseLog.cpp\
	  baseTime.cpp\
	  basePthread.cpp\
	  baseEntry.cpp\
	  global.cpp\
	  baseThread.cpp\
	  baseSqlTable.cpp\
	  baseSqlRecord.cpp\
	  baseSqlHandle.cpp\
	  baseSqlPool.cpp\
	  baseTaskThread.cpp\
	  baseMsgContainer.cpp\
	  baseSocket.cpp\
	  baseTcpTask.cpp\
	  baseSyncThread.cpp\
	  baseRecycleThread.cpp\
	  baseOkayThread.cpp\
	  baseVerifyThread.cpp\
	  baseTaskPool.cpp\
	  baseService.cpp\
	  baseNetService.cpp\
	  baseTcpService.cpp\
	  baseTcpClient.cpp\
	  baseTcpClientBuffer.cpp\
	  baseSuperClient.cpp\
	  baseSubService.cpp\
	  baseProperty.cpp\
	  baseCheckWaitThread.cpp\
	  baseCheckConnectThread.cpp\
	  baseTcpClientThread.cpp\
	  baseTcpClientTaskPool.cpp\
	  baseTcpClientTask.cpp\
	  baseTcpTaskQueue.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

libbase.a : $(object)
	$(AR) -rcs libbase.a $(object)

$(object) : %.o : %.cpp
	$(CXX) -g -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	$(DEL_FILE) libbase.a
	
.PHONY : clean
clean:
	$(DEL_FILE) $(object)
	$(DEL_FILE) $(depend)
	$(DEL_FILE) libbase.a
