CXX = g++
CXXFLAGS = -Wall -g
SRC_DIR = ./src

main: main.o internal_sort.o external_sort.o io.o
	$(CXX) $(CXXFLAGS) -o main main.o internal_sort.o external_sort.o io.o -pthread
main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/internal_sort.h $(SRC_DIR)/external_sort.h $(SRC_DIR)/io.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp
internal_sort.o: $(SRC_DIR)/internal_sort.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/internal_sort.cpp
external_sort.o: $(SRC_DIR)/external_sort.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/external_sort.cpp
io.o: $(SRC_DIR)/io.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/io.cpp

.PHONY: clean
clean:
	rm *.o main
