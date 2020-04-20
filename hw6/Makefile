CXX := g++
CXXFLAGS := -Wall -g -Wno-c++11-extensions
SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OUT_DIR := data logs obj

all: $(OUT_DIR) mySort

mySort:  $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^

$(OUT_DIR):
	mkdir -p ${OUT_DIR}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f mySort
	rm -rf $(OBJ_DIR)
