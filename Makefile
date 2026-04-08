CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o code

clean:
	rm -f code
