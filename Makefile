build:
	g++ -Wall -std=c++20 ./src/*.cpp -lSDL2 -o main

run:
	./main

clean:
	rm main

