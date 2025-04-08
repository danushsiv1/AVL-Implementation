CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = main.cpp AVLTree.cpp AVLNode.cpp
OBJECTS = main.o AVLTree.o AVLNode.o
EXEC = wordrange

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

$(OBJECTS): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

clean:
	rm -f $(OBJECTS) $(EXEC)