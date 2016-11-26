####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = client.o\
	readClient.o\
	main.o

bin/wsd : $(object)
	$(LINK) -g -o bin/wsd $(object) -I /usr/include/libxml2/ -L /usr/lib/ -lxml2 -I /usr/local/include/event2/ -L /usr/local/lib/ -levent	
client.o : modle/client.cpp
	$(CXX) -g -c $< -Iinclude
readClient.o : src/readClient.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/include/libxml2/ -L /usr/lib/ -lxml2	
main.o : main.cpp
	$(CXX) -g -c $< -Iinclude 
clean:
	$(DEL_FILE) $(object) bin/wsd
