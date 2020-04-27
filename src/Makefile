CC = gcc
CFLAGS = -g -Wall

OBJECTS = example.o sacli.o sacli_command.o sacli_parser.o

all: $(OBJECTS)

example.o: example.c sacli.o sacli_parser.o sacli_command.o 
	$(CC) $(CFLAGS) -o example $^ 

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

# sacli_command.o: sacli_command.c
# 	$(CC) $(CFLAGS) -c $^

# sacli_parser.o: sacli_parser.c 
# 	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o example


# src = $(wildcard *.c)
# obj = $(src:.c=.o)

# LDFLAGS = -lGL -lglut -lpng -lz -lm

# myprog: $(obj)
# 	$(CC) -o $@ $^ $(LDFLAGS)

# .PHONY: clean

# clean:
# 	rm -f $(obj) myprog
