# Determine OS
UNAME := $(shell uname)

# Set library name
ifeq ($(UNAME), Linux) # WSL and Ubuntu
library_name = -l:libcryptopp.a
endif
ifeq ($(UNAME), Darwin) # MacOS Darwin
library_name = -lcryptopp
endif

# Variables
objects = main.o cryptog.o entry.o ui.o utils.o
cpp_standard = -std=c++11
options = $(cpp_standard) -g -c

# when main.o changes, run the following command to produce "run", linking with our library
run: $(objects)
	g++ $(cpp_standard) -g *.o -o run $(library_name)

# when any .cpp or .h file change in our working directory, compile each individually.
# "-c" compiles to object file.
main.o: main.cpp cryptog.h ui.h
	g++ $(options) main.cpp

cryptog.o: cryptog.cpp cryptog.h
	g++ $(options) cryptog.cpp

entry.o: entry.cpp entry.h
	g++ $(options) entry.cpp

ui.o: ui.cpp ui.h
	g++ $(options) ui.cpp

utils.o: utils.cpp utils.h
	g++ $(options) utils.cpp

# doesn't produce anything, but we can invoke from terminal with "make clean"
clean:
	rm *.o

###### SCHEMA
# target: dependencies
#	  command