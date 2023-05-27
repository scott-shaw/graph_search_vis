PROG_NAME=build/gs_viz

CXX=g++
CXXFLAGS=-std=c++17

srcfiles=src/*.cpp
RM=rm -f
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

compile:
	$(CXX) $(srcfiles) -o $(PROG_NAME) $(LDLIBS) 
run: compile
	./$(PROG_NAME)
clean:
	$(RM) build/*
