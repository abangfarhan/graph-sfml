CXX = g++
CXXFLAGS = --std=c++11 -g -Wall
INC = -I ./include/
SFML_INCLUDE = -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB = -L "D:/Program Files (x86)/SFML/lib" \
	-l sfml-graphics-s-d \
	-l sfml-window-s-d \
	-l sfml-system-s-d \
	-l opengl32 \
	-l winmm \
	-l gdi32 \
	-l freetype \
	-l jpeg \

# %: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $< $(SFML)

bin/main: build/main.o build/Node.o
	$(CXX) $(CXXFLAGS) -o bin/main build/main.o build/Node.o $(SFML_LIB)

build/main.o: src/main.cpp include/Node.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o build/main.o -c src/main.cpp $(INC) $(SFML_INCLUDE)

build/Node.o: src/Node.cpp include/Node.h
	$(CXX) $(CXXFLAGS) -o build/Node.o -c src/Node.cpp $(INC)

bin/shortest-path-djikstra: build/shortest-path-djikstra.o build/NodeDjikstra.o build/Node.o
	$(CXX) $(CXXFLAGS) -o bin/shortest-path-djikstra build/shortest-path-djikstra.o build/NodeDjikstra.o build/Node.o $(SFML_LIB)

build/shortest-path-djikstra.o: src/shortest-path-djikstra.cpp include/NodeDjikstra.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o build/shortest-path-djikstra.o -c src/shortest-path-djikstra.cpp $(INC) $(SFML_INCLUDE)

build/NodeDjikstra.o: src/NodeDjikstra.cpp include/NodeDjikstra.h
	$(CXX) $(CXXFLAGS) -o build/NodeDjikstra.o -c src/NodeDjikstra.cpp $(INC)

clean:
	rm build/*.*
