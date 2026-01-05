# Define compiler and compilation flags
CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm  # math library

#Name of the executable
TARGET = sentiment

#Files needed
OBJS = main.o vaderSentiment.o

#Default to build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.c utility.h
	$(CC) $(CFLAGS) -c main.c

vaderSentiment.o: vaderSentiment.c utility.h
	$(CC) $(CFLAGS) -c vaderSentiment.c

clean:
	rm -f $(TARGET) $(OBJS)