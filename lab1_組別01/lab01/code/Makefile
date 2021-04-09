CXXFLAGS=-std=c++11
# CROSS_COMPILE=aarch64-linux-gnu-
CXX=g++
OBJ=circular_sector.o ellipse.o sort.o triangle.o main.o
SRC=circular_sector.cpp ellipse.cpp sort.cpp triangle.cpp main.cpp
EXE=lab01

all:clean $(EXE)
$(EXE):$(OBJ) 
	$(CXX) $(CXXFLAGS) -o $@ $^
	# $(CROSS_COMPILE)$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ) 

$(OBJ):$(SRC) 
	$(CXX) $(CXXFLAGS) -c $?
	# $(CROSS_COMPILE)$(CXX) $(CXXFLAGS) -c $(SRC)

clean:

	rm -f $(EXE)

	rm -f $(OBJ)
# file ./
# ssh -Y nvida@ 192.....