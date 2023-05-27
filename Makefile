PROG_NAME=gs_viz
BUILD_DIR=build
BUILD_PATH=$(BUILD_DIR)/$(PROG_NAME)

CXX=g++
CXXFLAGS=-std=c++17

srcfiles=src/*.cpp
RM=rm -f
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

compile: desc
	mkdir $(BUILD_DIR) -p
	$(CXX) $(srcfiles) -o $(BUILD_PATH) $(LDLIBS) 
run: compile
	./$(BUILD_PATH)
clean:
	$(RM) $(BUILD_DIR)/*
desc:
	@echo +----------------------------+
	@echo \| Graph Search Visualization\ \|
	@echo \| Made by Scott Shaw\ \ \ \ \ \ \ \ \ \|
	@echo \| github.com/scott-shaw\ \ \ \ \ \ \|
	@echo +----------------------------+
