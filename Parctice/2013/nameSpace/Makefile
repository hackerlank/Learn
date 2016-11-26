####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = a.o\
		 b.o\
		 main.o
	
bin/test : $(object)
	$(LINK) -g -o bin/test $(object) 
	
a.o : src/a.cpp
	$(CXX) -g -c $< -Iinclude

b.o : src/b.cpp
	$(CXX) -g -c $< -Iinclude

main.o : src/main.cpp
	$(CXX) -g -c $< -Iinclude

clean:
	$(DEL_FILE) $(object)
