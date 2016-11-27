DEL_FILE      = -rm -rf
CC            = gcc
CXX           = g++
LINK          = g++

CFLAGS         := -std=c++11 $(FLYER_COMPILE_OPT) $(PIC_FLAG) -Wall -D_GNU_SOURCE -D_REENTRANT
LDFLAG         := $(FLYER_COMPILE_OPT) -Wall -L../base -lbase -L../protocpp -lproto -lpthread -lrt -L/usr/local/apr/lib -lapr-1 -L/usr/local/apr-util/lib -laprutil-1 -L/usr/local/lib/ -llog4cxx -L/usr/local/libxml2/lib/ -lxml2 -L/usr/local/protobuf/lib/ -lprotobuf -L/usr/local/mysql/lib/mysql/ -lmysqlclient 
FLYER_LIB = ../base/libbase.a ../protocpp/libproto.a
####### Files
src = client.cpp\
	  timeTick.cpp

object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

Client : $(object) $(FLYER_LIB)
	$(CXX) $(CFLAGS) $(object) -o Client $(LDFLAG)

$(object) : %.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -MM -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	 $(DEL_FILE) Client

.PHONY : clean
clean:
	 $(DEL_FILE) $(object)
	 $(DEL_FILE) $(depend)
	 $(DEL_FILE) Client
	 $(DEL_FILE) *.swp
	 $(DEL_FILE) .*.swp
	 $(DEL_FILE) *.swo
	 $(DEL_FILE) *~
