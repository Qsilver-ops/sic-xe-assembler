CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = src/main.cpp src/pass1.cpp src/pass2.cpp src/optable.cpp

lxe: $(SRC)
	$(CXX) $(CXXFLAGS) -o lxe $(SRC)

clean:
	rm -f lxe
