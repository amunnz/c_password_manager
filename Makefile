# when main.o changes, run the following command to produce "run", linking with our library
run: main.o cryptog.o entry.o ui.o utils.o
	g++ -g *.o -o run -l:libcryptopp.a

# when any .cpp or .h file change in our working directory, compile each individually.
# "-c" compiles to object file.
main.o: main.cpp cryptog.h ui.h
	g++ -g -c main.cpp

cryptog.o: cryptog.cpp cryptog.h
	g++ -g -c cryptog.cpp

entry.o: entry.cpp entry.h
	g++ -g -c entry.cpp

ui.o: ui.cpp ui.h
	g++ -g -c ui.cpp

utils.o: utils.cpp utils.h
	g++ -g -c utils.cpp

# doesn't produce anything, but we can invoke from terminal with "make clean"
clean:
	rm *.o

###### SCHEMA
# target: dependencies
#	  action