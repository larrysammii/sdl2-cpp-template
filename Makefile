build:
	g++ -Wall ./src/*.cpp -lSDL2 -o main

run:
	./main

clean:
	rm main

