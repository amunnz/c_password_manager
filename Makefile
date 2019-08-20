# when main.o changes, run the following command to produce "run", linking with our library
run: main.o cryptog.o entry.o ui.o utils.o
	g++ -g *.o -o run -l:libcryptopp.a -std=c++0x

# when any .cpp or .h file change in our working directory, compile each individually.
# "-c" compiles to object file.
main.o: main.cpp cryptog.h ui.h
	g++ -g -c main.cpp -std=c++0x

cryptog.o: cryptog.cpp cryptog.h
	g++ -g -c cryptog.cpp -std=c++0x

entry.o: entry.cpp entry.h
	g++ -g -c entry.cpp -std=c++0x

ui.o: ui.cpp ui.h
	g++ -g -c ui.cpp -std=c++0x

utils.o: utils.cpp utils.h
	g++ -g -c utils.cpp -std=c++0x

# doesn't produce anything, but we can invoke from terminal with "make clean"
clean:
	rm *.o

###### SCHEMA
# target: dependencies
#	  action