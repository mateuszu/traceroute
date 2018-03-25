
CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wextra

main: main.o utilities.o receive.o send.o
	$(CPP) $(CPPFLAGS) -o main main.o utilities.o receive.o send.o 

main.o: main.cpp

utilities.o: utilities.cpp utilities.h

receive.o: receive.cpp receive.h

send.o: send.cpp send.h

clean:
	rm -f *.o
	
distclean:
	rm -f *.o main 