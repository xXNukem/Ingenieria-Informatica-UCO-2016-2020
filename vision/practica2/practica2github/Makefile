.PHONY: clean-objects clean-all

CXX = g++
CXXFLAGS = -Wall -ggdb3 $(LIBRARY) $(INCLUDE) $(OPENCV)
LIBRARY = -L.
INCLUDE = -I.
OPENCV = `pkg-config --cflags --libs opencv`

UnsharpMask.o: UnsharpMask.cpp UnsharpMask.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ UnsharpMask.cpp

clean-objects:
	-rm *.o

clean-all: clean-objects
