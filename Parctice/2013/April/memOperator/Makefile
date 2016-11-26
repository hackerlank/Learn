####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = memTest.o
		 
bin/memTest : $(object)
	$(LINK) -g -o bin/memTest $(object) -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lssl -lcrypto -lxml2 -levent -lmemcached -luuid	
	
memTest.o : src/memTest.cpp
	$(CXX) -g -c $< -Iinclude
clean:
	$(DEL_FILE) $(object) bin/memTest

