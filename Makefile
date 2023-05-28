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

main.o : affichage.h

cesar.o : cesar.h chiffrement.h

vigenere.o : vigenere.h chiffrement.h

hill.o : hill.h chiffrement.h

chiffrement.o : chiffrement.h

affichage.o : affichage.h cesar.h vigenere.h hill.h

clean :
	rm -f *.o $(EXEC)