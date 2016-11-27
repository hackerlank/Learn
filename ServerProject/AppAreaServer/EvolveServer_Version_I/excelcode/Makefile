######## compiler, tools and options
DEL_FILE      = rm -rf
CC            = gcc
CXX           = g++
LINK          = g++
AR            = ar

CFLAGS := -std=c++11 $(FLYER_COMPILE_OPT) $(PIC_FLAG) -Wall -D_GNU_SOURCE -D_REENTRANT

LDFLAG := $(FLYER_COMPILE_OPT) -Wall -L/usr/local/lib/ -llog4cxx -L/usr/local/libxml2/lib/ -lxml2 -L../base -lbase -L../protocpp -lproto -L/usr/local/protobuf/lib/ -lprotobuf -L/usr/local/mysql/lib/mysql/ -lmysqlclient

src= $(wildcard *.cpp)
object = $(patsubst %.cpp,%.o,$(src))
depend = $(patsubst %.cpp,%.d,$(src))

libexcel.a : $(object)
	$(AR) -rcs libexcel.a $(object)
	@ranlib libexcel.a

$(object) : %.o : %.cpp
	$(CXX) -g -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cpp
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	$(DEL_FILE) libexcel.a
	
.PHONY : clean
clean:
	$(DEL_FILE) $(object)
	$(DEL_FILE) $(depend)
	$(DEL_FILE) libexcel.a
	$(DEL_FILE) *.swp
	$(DEL_FILE) .*.swp
	$(DEL_FILE) *.swo
	$(DEL_FILE) *~
