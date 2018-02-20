CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors 

Pa1: main.o 
	$(CXX) $(CXXFLAGS) main.o -o Pa1

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f Pa1 *.o 

