####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = main.o
	
bin/test : $(object)
	$(LINK) -g -o bin/test $(object) 
	
main.o : src/main.cpp
	$(CXX) -g -c $< -Iinclude

clean:
	$(DEL_FILE) $(object)
