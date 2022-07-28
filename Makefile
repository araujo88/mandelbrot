all:
	g++ -Wall -c Complex/complex.cpp main.cpp
	g++ -Wall -o mandelbrot complex.o main.o
	g++ -Wall -o generate_images generate_images.cpp 
clean:
	rm -rf *.o *.bmp mandelbrot generate_images