# Makefile for compiling App.cpp

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall

# Source files
SRCS := minimax.cpp

# Executable name
TARGET := minimax

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(TARGET)
