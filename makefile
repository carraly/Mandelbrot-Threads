CFLAGS = -Wall -Wextra -g -fopenmp -pthread	

processflow: main.o serial.o errors.o math.o openmp.o pthreads1.o
	gcc $(CFLAGS) -o mandelbrot $^

%.o: %.c header.h
	gcc $(CFLAGS) -c $<

run: mandelbrot
	./mandelbrot

clean:
	rm -f *.o mandelbrot

.PHONY: run clean	