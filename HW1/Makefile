CXX := g++
ARG := -std=c++17

all: problem3 problem4 problem6 problem7

problem3: problem3.o OneMaxPopulation.o
	$(CXX) $(ARG) problem3.o OneMaxPopulation.o -o problem3

problem4: problem4.o OneMaxPopulation.o
	$(CXX) $(ARG) problem4.o OneMaxPopulation.o -o problem4

problem6: problem6.o OneMaxPopulation.o
	$(CXX) $(ARG) problem6.o OneMaxPopulation.o -o problem6

problem7: problem7.o OneMaxPopulation.o
	$(CXX) $(ARG) problem7.o OneMaxPopulation.o -o problem7

problem3.o: 50-bit-OneMax-Problem-3.cpp
	$(CXX) $(ARG) 50-bit-OneMax-Problem-3.cpp -c -o problem3.o

problem4.o: 50-bit-OneMax-Problem-4.cpp
	$(CXX) $(ARG) 50-bit-OneMax-Problem-4.cpp -c -o problem4.o

problem6.o: 50-bit-OneMax-Problem-6.cpp
	$(CXX) $(ARG) 50-bit-OneMax-Problem-6.cpp -c -o problem6.o

problem7.o: 50-bit-OneMax-Problem-7.cpp
	$(CXX) $(ARG) 50-bit-OneMax-Problem-7.cpp -c -o problem7.o

OneMaxPopulation.o: OneMaxPopulation.cpp
	$(CXX) $(ARG) OneMaxPopulation.cpp -c -o OneMaxPopulation.o

clean:
	rm -rf *.o problem3 problem4 problem6 problem7
