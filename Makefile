CC = gcc
CFLAGS = -Wall -g

all: carwash

carwash: carwash.o wash.o
	$(CC) $(CFLAGS) carwash.o wash.o -o carwash

carwash.o: carwash.c
	$(CC) $(CFLAGS) -c carwash.c

wash.o: wash.c
	$(CC) $(CFLAGS) -c wash.c