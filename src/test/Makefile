CC=gcc
CFLAGS=-g

all: string_test test_rev

string_test: test_string.c
	$(CC) $(CFLAGS) test_string.c ../string_t.o -o test_string

test_rev: test_rev.c
	$(CC) $(CFLAGS) test_rev.c ../fs.o ../rev.o ../init.o -o test_rev


cli_test: cli_test.c
	$(CC) $(CFLAGS) cli_test.c ../string_t.o ../cli.o ../list.o ../arg_registry.o -o cli_test


run: string_test test_rev cli_test
	./test_string
	./test_rev
	./cli_test

clean:
	rm -f test_string output.txt *.o main
