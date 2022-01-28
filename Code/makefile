CC = gcc
CFLAGS = -std=c99
OBJECTS = lab1_IO.o main.o
APP_NAME = main

$(APP_NAME): $(OBJECTS)
	$(CC) -pthread $(CFLGS) -o $(APP_NAME) $(OBJECTS) -lm

lab1_IO.o : lab1_IO.c
	$(CC) $(CFLAGS) -c lab1_IO.c -o lab1_IO.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm *.o $(APP_NAME)
