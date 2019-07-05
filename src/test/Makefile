CC=gcc
CFLAGS=-g

string_test: test_string.c
	$(CC) $(CFLAGS) test_string.c ../string_t.o -o test_string

cli_test: cli_test.c
	$(CC) $(CFLAGS) cli_test.c ../string_t.o ../cli.o ../list.o ../arg_registry.o -o cli_test


run: string_test
	./test_string

clean:
	rm -f test_string output.txt cli_test
