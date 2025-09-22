hello: a.o b.o
	gcc -o hello a.o b.o

a.o: a.c
	gcc -c a.c

b.o: b.c
	gcc -c b.c

clean:
	rm -f hello a.o b.o
