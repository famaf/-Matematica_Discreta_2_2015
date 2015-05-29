CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJECTS = api.o

test : $(OBJECTS)
	$(CC) $(CFLAGS) -o test $(OBJECTS) main.c

api.o : api.c api.h
	$(CC) $(CFLAGS) -c api.c -o api.o

.PHONY : clean

clean :
	rm -rf test $(OBJECTS) main.o
