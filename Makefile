CXX = g++
CXXFLAGS = --std=c++11 -g
SFML_INCLUDE = -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB = -L "D:/Program Files (x86)/SFML/lib" \
	-l sfml-graphics-s \
	-l sfml-window-s \
	-l sfml-system-s \
	-l opengl32 \
	-l winmm \
	-l gdi32 \
	-l freetype \
	-l jpeg \

# %: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $< $(SFML)

main: main.o Node.o
	$(CXX) $(CXXFLAGS) -o main main.o Node.o $(SFML_LIB)

main.o: main.cpp Node.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(SFML_INCLUDE)

Node.o: Node.cpp Node.h
	$(CXX) $(CXXFLAGS) -c Node.cpp
