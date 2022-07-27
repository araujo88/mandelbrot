all:
	g++ -Wall -c Complex/complex.cpp EasyBMP/sample.cpp main.cpp
	g++ -Wall -o mandelbrot complex.o main.o
clean:
	rm -rf *.o *.bmp