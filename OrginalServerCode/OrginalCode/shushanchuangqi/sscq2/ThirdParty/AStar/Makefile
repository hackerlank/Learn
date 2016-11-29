CC = g++ -o
OBJS = AStar.o

AStar : $(OBJS)
	$(AR) -r libAStar.a $(OBJS)
	cp libAStar.a ../export

.PHONY : clean

clean :
	$(RM) libAStar.a $(OBJS)
