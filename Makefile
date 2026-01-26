all:
	g++ -Isrc/include -Lsrc/lib src/*.cpp -o main -lmingw32 -lSDL3 -lSDL3_image 