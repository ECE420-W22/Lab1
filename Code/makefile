CC = gcc
OBJECTS = lab1_IO.o main.o
APP_NAME = main

$(APP_NAME): $(OBJECTS)
	$(CC) -pthread -o $(APP_NAME) $(OBJECTS) -lm

lab1_IO.o : lab1_IO.c
	$(CC) -c lab1_IO.c -o lab1_IO.o

main.o : main.c
	$(CC) -c main.c -o main.o

clean:
	rm *.o $(APP_NAME)