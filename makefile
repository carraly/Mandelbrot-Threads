CFLAGS = -Wall -Wextra -g

processflow: main.o serial.o errors.o
	gcc $(CFLAGS) -o mandelbrot $^

%.o: %.c header.h
	gcc $(CFLAGS) -c $<

run: mandelbrot
	./mandelbrot

clean:
	rm -f *.o mandelbrot

.PHONY: run clean	