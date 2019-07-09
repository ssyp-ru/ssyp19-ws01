CC=gcc
CFLAGS=-g -Wall -Wpedantic

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

gg: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o gg

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

unit_test: string_t.o
	make -C test run
	make -C test clean

clean:
	rm -f *.o
	make --no-print-directory -C test clean
