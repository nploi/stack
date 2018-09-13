PREFIX = /usr/local

#SRC specifies which files to compile as part of the project
EXE = Stack.o
#CXX specifies C++ compiler
#CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXXFLAGS = -std=c++11 #-Wall
#  CXXFLAGS += -w

THREAD = -pthread

#This is the target that compiles our executable
$(EXE): util.o block.o game.o ../main.cpp
	$(CXX) $(THREAD) $^ $(CXXFLAGS) -o $@


util.o: ../src/util.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@

block.o: ../src/block.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@

game.o: ../src/game.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@  

test:
	echo "3" | ./$(EXE)

clean:
	$(RM) *.o $(EXE)

install: $(EXE)
	cp Stack.o $(PREFIX)/bin/Stack