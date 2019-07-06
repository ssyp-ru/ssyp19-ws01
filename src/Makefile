CC=gcc
CFLAGS=-g

string_t.o: string_t.c string_t.h
	$(CC) $(CFLAGS) string_t.c -c

unit_test: string_t.o
	make -C test run

clean:
	rm *.o main
	make -C test clean
