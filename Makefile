CXX := g++
CXXFLAGS := -std=c++17 $(shell wx-config --cxxflags)
LDFLAGS := $(shell wx-config --libs)

SRC := $(wildcard code/*.cpp)
OUT := code/d2rrunes

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
