# when main.o changes, run the following command to produce "run"
run: main.o
	g++ main.o -o run -lcryptopp

# when main.cpp and/or password_manager.h change, run the following
# command to produce "main.o" -c flag simply compiles into an object file
main.o: main.cpp password_manager.h
	g++ -c main.cpp

# doesn't produce anything, but we can invoke from terminal with "make clean"
clean:
	rm *.o

###### SCHEMA
# target: dependencies
#	  action
