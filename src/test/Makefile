CC=gcc
CFLAGS=-g

all: string_test test_rev

string_test: test_string.c
	$(CC) $(CFLAGS) test_string.c ../string_t.o -o test_string

test_rev: test_rev.c
	$(CC) $(CFLAGS) test_rev.c ../fs.o ../rev.o ../init.o -o test_rev

run: string_test test_rev
	./test_string
	./test_rev

clean:
	rm -f test_string output.txt *.o main 
