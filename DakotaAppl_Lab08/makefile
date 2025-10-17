CC = gcc
CFLAGS = -Wall -g -std=c11

all: NFLscoring tempConversion

NFLscoring: NFLscoring.o
	$(CC) $(CFLAGS) -o NFLscoring NFLscoring.o

tempConversion: tempConversion.o
	$(CC) $(CFLAGS) -o tempConversion tempConversion.o

NFLscoring.o: NFLscoring.c
	$(CC) $(CFLAGS) -c NFLscoring.c

tempConversion.o: tempConversion.c
	$(CC) $(CFLAGS) -c tempConversion.c

clean:
	rm -f *.o NFLscoring tempConversion

.PHONY: all clean