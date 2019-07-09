CC=gcc
CFLAGS=-g

string_test: test_string.c
	$(CC) $(CFLAGS) test_string.c ../string_t.o -o test_string

run: string_test
	./test_string

clean:
	rm -f test_string output.txt *.o main 
