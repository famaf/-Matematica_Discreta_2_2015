CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -g
OBJECTS = API.o

test : $(OBJECTS)
	$(CC) $(CFLAGS) -o test $(OBJECTS) main.c

API.o : API.c API.h
	$(CC) $(CFLAGS) -c API.c -o API.o

.PHONY : clean

clean :
	rm -rf test $(OBJECTS) main.o
