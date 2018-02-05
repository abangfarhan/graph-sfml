CXX := g++
CXXFLAGS := --std=c++11 -g -Wall
INC := -I include
SFML_INCLUDE := -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB := -L "D:/Program Files (x86)/SFML/lib" \
	-l sfml-graphics-s-d \
	-l sfml-window-s-d \
	-l sfml-system-s-d \
	-l opengl32 \
	-l winmm \
	-l gdi32 \
	-l freetype \
	-l jpeg \

bin/main: build/main.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/main.o: src/main.cpp include/Node.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC) $(SFML_INCLUDE)

build/Node.o: src/Node.cpp include/Node.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

bin/sp-djikstra: build/sp-djikstra.o build/NodeDjikstra.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/sp-djikstra.o: src/sp-djikstra.cpp include/NodeDjikstra.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC) $(SFML_INCLUDE)

build/NodeDjikstra.o: src/NodeDjikstra.cpp include/NodeDjikstra.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

clean:
	rm build/*.*
