all: main.o input.o
	g++ *.o -o ss

main:
	g++ -c main.cpp -o main.o

input:
	g++ -c input.cpp -o input.o

clean:
	rm ss
	rm main.o
	rm input.o
