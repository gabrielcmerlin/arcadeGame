all:
	g++ -o exec *.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -pthread
run:
	./exec
clean:
	rm exec