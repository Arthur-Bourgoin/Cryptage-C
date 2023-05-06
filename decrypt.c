#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "cesar.h"
#include "decrypt.h"
#include "chiffrement.h"

int stockerFrequence(int* tab, FILE* fic) {
    int caractere = 0;
    while( (caractere = fgetc(fic)) != EOF ) {
        tab[caractere]++;
    }
    return 1;
}

void afficherTab(int* tab) {
    for (int i = 0; i < 128; i++) {
        printf("%d : %c --> |%d|\n", i, i, tab[i]);
    }
}

int indiceMax(int* tab) {
    int max = 0;
    int indiceMax = -1;
    for(int i = 0; i < 128; i++) {
        if (tab[i] > max) {
            max = tab[i];
            indiceMax = i;
        }
    }
    return indiceMax;
}
