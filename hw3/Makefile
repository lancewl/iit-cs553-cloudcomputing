CXX = g++
CXXFLAGS = -Wall -g
SRC_DIR = ./src


main: MyDiskBench.o readFile.o writeFile.o
	$(CXX) $(CXXFLAGS) -o main MyDiskBench.o readFile.o writeFile.o
MyDiskBench.o: $(SRC_DIR)/MyDiskBench.cpp $(SRC_DIR)/readFile.h $(SRC_DIR)/writeFile.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/MyDiskBench.cpp
readFile.o: $(SRC_DIR)/readFile.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/readFile.cpp
writeFile.o: $(SRC_DIR)/writeFile.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/writeFile.cpp

.PHONY: clean
clean:
	rm *.o main
