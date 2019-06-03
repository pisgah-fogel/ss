all: main input help
	g++ build/*.o -o ss

main:
	mkdir build
	g++ -c main.cpp -o build/main.o

input:
	g++ -c utils/input.cpp -o build/input.o

help:
	g++ -c commands/help.cpp -o build/help.o

clean:
	rm -r build
	rm ss
