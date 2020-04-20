CXX = g++
CXXFLAGS = -Wall -g
SRC_DIR = ./src
DATA_DIR=./data

mySort: mySort.o internal_sort.o external_sort.o io.o min_heap.o 
	$(CXX) $(CXXFLAGS) -o mySort mySort.o internal_sort.o external_sort.o io.o min_heap.o -pthread
	mkdir -p $(DATA_DIR)
mySort.o: $(SRC_DIR)/mySort.cpp $(SRC_DIR)/internal_sort.h $(SRC_DIR)/external_sort.h $(SRC_DIR)/io.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/mySort.cpp
internal_sort.o: $(SRC_DIR)/internal_sort.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/internal_sort.cpp
external_sort.o: $(SRC_DIR)/external_sort.cpp $(SRC_DIR)/min_heap.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/external_sort.cpp
io.o: $(SRC_DIR)/io.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/io.cpp
min_heap.o: $(SRC_DIR)/min_heap.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/min_heap.cpp

.PHONY: clean
clean:
	rm *.o mySort
