CC = c99
CFLAGS = -g -Wall -Wextra -pedantic
LFLAGS = -lm
LIBSRC := $(wildcard lib/src/*.c) 
EXSRC := $(wildcard example-cli/src/*.c)

debug: CFLAGS += -O0

release: CFLAGS += -O3

all: library example

library: $(patsubst %.c, %.o, $(LIBSRC))
	ar rcs lib/libeasy-time.a lib/src/*.o

example: $(patsubst %.c, %.o, $(EXSRC))
	$(CC) example-cli/src/*.o -o example-cli/easy-time -Llib -leasy-time -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm lib/src/*.o example-cli/src/*.o
