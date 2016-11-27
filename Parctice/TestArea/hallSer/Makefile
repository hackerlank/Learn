####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = hallSer.o\
	gameSer.o\
	global.o\
	readHallSer.o\
	main.o\
    fun.o

bin/wsd : $(object)
	$(LINK) -g -o bin/wsd $(object) -I /usr/include/libxml2/ -L /usr/lib/ -lxml2 -I /usr/local/include/event2/ -L /usr/local/lib/ -levent	
hallSer.o : modle/hallSer.cpp
	$(CXX) -g -c $< -Iinclude
gameSer.o : modle/gameSer.cpp
	$(CXX) -g -c $< -Iinclude
global.o : src/global.cpp
	$(CXX) -g -c $< -Iinclude
readHallSer.o : src/readHallSer.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/include/libxml2/ -L /usr/lib/ -lxml2	
main.o : main.cpp
	$(CXX) -g -c $< -Iinclude 
fun.o : src/fun.cpp
	$(CXX) -g -c $< -Iinclude 
clean:
	$(DEL_FILE) $(object) bin/wsd
