CXX=g++
CFLAGS=-std=c++11 -Wall -Wfatal-errors

synth: synth.cpp *.h
	$(CXX) $(CFLAGS) -o synth synth.cpp
