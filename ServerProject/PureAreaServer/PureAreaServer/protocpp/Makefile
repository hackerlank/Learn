######## compiler, tools and options

DEL_FILE      = -rm -rf
CC            = gcc
LINK          = g++
AR            = ar

CFLAGS         := -std=c++11 $(FLYER_COMPILE_OPT) $(PIC_FLAG) -Wall -D_GNU_SOURCE -D_REENTRANT
LDFLAG         := $(FLYER_COMPILE_OPT) -Wall -L/usr/local/protobuf/lib/ -lprotobuf

####### Files
src = serialize.pb.cc system.pb.cc 
		

object = $(patsubst %.cc,%.o,$(src))
depend = $(patsubst %.cc,%.d,$(src))

libproto.a : $(object)
	$(AR) -rcs libproto.a $(object)
	@ranlib libproto.a

$(object) : %.o : %.cc
	$(CXX) -g -c $(CFLAGS) $< -o $@

$(depend) : %.d : %.cc
	$(CXX) -M -c $(CFLAGS) $<  >$@

-include $(depend)

.PHONY : cleanlib
cleanlib:
	$(DEL_FILE) libproto.a
	
.PHONY : clean
clean:
	$(DEL_FILE) $(object)
	$(DEL_FILE) $(depend)
	$(DEL_FILE) libproto.a
	$(DEL_FILE) *.swp
	$(DEL_FILE) .*.swp
	$(DEL_FILE) *.swo
	$(DEL_FILE) *~
