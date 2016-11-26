####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = gameSer.o\
	readGameSer.o\
	main.o

bin/wsd : $(object)
	$(LINK) -g -o bin/wsd $(object) -I /usr/include/libxml2/ -L /usr/lib/ -lxml2 -I /usr/local/include/event2/ -L /usr/local/lib/ -levent	
gameSer.o : modle/gameSer.cpp
	$(CXX) -g -c $< -Iinclude
readGameSer.o : src/readGameSer.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/include/libxml2/ -L /usr/lib/ -lxml2	
main.o : main.cpp
	$(CXX) -g -c $< -Iinclude 
clean:
	$(DEL_FILE) $(object) bin/wsd
