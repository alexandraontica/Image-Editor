CFLAGS=-Wall -Werror

.PHONY: clean run

run: build
	./main

build: main.c imageprocessing.c bmp.c ux.c
	gcc main.c imageprocessing.c bmp.c ux.c $(CFLAGS) -o main

clean:
	rm -f main main
