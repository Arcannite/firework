all: igniter

igniter:
	gcc -c utils.c
	gcc -c igniter.c
	gcc utils.o igniter.o -o igniter

clean:
	rm -f *.o igniter