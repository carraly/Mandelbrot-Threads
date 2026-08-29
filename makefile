CFLAGS = -Wall -Wextra -g -fopenmp

processflow: main.o serial.o errors.o math.o openmp.o
	gcc $(CFLAGS) -o mandelbrot $^

%.o: %.c header.h
	gcc $(CFLAGS) -c $<

run: mandelbrot
	./mandelbrot

clean:
	rm -f *.o mandelbrot

.PHONY: run clean	