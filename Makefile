CC = g++
CFLAGS = -g -W -Wall -Werror -pedantic

OBJECTS = phone_book.o area_node.o main.o

all: phone_book.o area_node.o main.o
	$(CC) $(CFLAGS) -o a.out $(OBJECTS) 

phone_book.o: phone_book.cc phone_book.h
	$(CC) $(CFLAGS) -c phone_book.cc

area_node.o: area_node.cc area_node.h
	$(CC) $(CFLAGS) -c area_node.cc

main.o: main.cc phone_book.cc phone_book.h area_node.cc area_node.h number_node.h
	$(CC) $(CFLAGS) -c main.cc phone_book.cc area_node.cc

clean:
	rm -rf *~ *.o a.out 
