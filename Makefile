all: clean main.c
	gcc -pthread main.c -o main

clean:
	rm -f main
