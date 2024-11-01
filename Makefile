all:
	gcc main.c lista.c memoria.c -o main

run: all
	./main

clean:
	rm -f main
