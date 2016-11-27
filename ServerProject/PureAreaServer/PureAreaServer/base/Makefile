######## compiler, tools and options
DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar

CFLAGS         := -std=c++11 $(FLYER_COMPILE_OPT) $(PIC_FLAG) -Wall -D_GNU_SOURCE -D_REENTRANT
LDFLAG         := $(FLYER_COMPILE_OPT) -Wall -L/usr/local/lib/ -llog4cxx -L/usr/local/libxml2/lib/ -lxml2 -L../protocpp -lproto -L/usr/local/protobuf/lib/ -lprotobuf -L/usr/local/mysql/lib/mysql/ -lmysqlclient
####### Files
src = thread.cpp\
	  taskManager.cpp\
	  taskQueue.cpp\
	  timefun.cpp\
	  flyer.cpp\
	  mainThread.cpp\
	  key.cpp\
	  flyerValue.cpp\
	  flyerXmlParse.cpp\
	  cmdFunManager.cpp\
	  messageQueue.cpp\
	  parseMessage.cpp\
	  mysqlUrl.cpp\
	  mysqlHandle.cpp\
	  mysqlPool.cpp\
	  messageHandle.cpp\
	  server.cpp\
	  connect.cpp\
	  superClient.cpp\
	  superClientHandle.cpp\
	  client.cpp\
	  recycleThread.cpp\
	  verifyThread.cpp\
	  clientManager.cpp\
	  excelManager.cpp\
	  clientHandle.cpp\
	  connectHandle.cpp
		

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

libbase.a : $(object)
	$(AR) -rcs libbase.a $(object)
	@ranlib libbase.a

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
	$(DEL_FILE) *.swp
	$(DEL_FILE) .*.swp
	$(DEL_FILE) *.swo
	$(DEL_FILE) *~

