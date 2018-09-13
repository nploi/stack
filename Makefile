PREFIX = /usr/local

#SRC specifies which files to compile as part of the project
EXE = build/Stack.o
#CXX specifies C++ compiler
#CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXXFLAGS = -std=c++11 #-Wall
#  CXXFLAGS += -w

THREAD = -pthread

#This is the target that compiles our executable
$(EXE): build/util.o build/block.o build/game.o main.cpp
	$(CXX) $(THREAD) $^ $(CXXFLAGS) -o $@


build/util.o: src/util.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@

build/block.o: src/block.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@

build/game.o: src/game.cpp
	$(CXX) -c $^ $(CXXFLAGS) -o $@  

test:
	./$(EXE)

clean:
	$(RM) *.o $(EXE)

install: $(EXE)
	cp build/Stack.o $(PREFIX)/bin/Stack