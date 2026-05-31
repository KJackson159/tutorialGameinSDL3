all:
	g++ -Isrc/include -Lsrc/lib main.cpp src/*.cpp -o main -lmingw32 -lSDL3 -lSDL3_image 