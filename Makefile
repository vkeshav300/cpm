build:
	g++ -std=c++17 -Isrc/Include -Lsrc/lib -o cpm main.cpp ./src/*.cpp