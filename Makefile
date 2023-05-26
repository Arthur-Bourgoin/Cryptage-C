CC = gcc
CFLAGS = -Wall -Wextra -g
EXEC = main
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,${SRC})

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

main.o : chiffrement.h cesar.h hill.h

cesar.o : cesar.h

vigenere.o : vigenere.h

hill.o : hill.h

chiffrement.o : chiffrement.h

affichage.o : affichage.h

clean :
	rm -f *.o $(EXEC)