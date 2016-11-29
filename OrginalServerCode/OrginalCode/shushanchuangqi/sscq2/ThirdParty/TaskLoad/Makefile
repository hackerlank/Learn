CC = g++ -o
OBJS = TaskConf.o TaskConfMgr.o

%.o : %.cpp
	g++ -I../tinyxml -O3 -c -fmessage-length=0 -std=c++0x -MMD -MP -o "$@" "$<"

TaskLoad : $(OBJS)
	$(AR) -r libTaskLoad.a $(OBJS)
	cp libTaskLoad.a ../export

.PHONY : clean

clean :
	$(RM) libTaskLoad.a $(OBJS)
