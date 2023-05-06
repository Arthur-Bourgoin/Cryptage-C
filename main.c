#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "chiffrement.h"
#include "cesar.h"
#include "vigenere.h"
#include "affichage.h"
#include "decrypt.h"


int main() {
    /*
    char car = 'b';
    char car2 = car + 255;
    printf("1 : %c et 2 : %c\n", car, car2);

    char chaine[] = "DuTexteComprehensibleParUnHumainQuiNestPasEncoreCrypteEtSansEspace";
    if (verifierAlpha(chaine) == 0) {
        printf("error\n");
    } else {
        printf("Chaine initiale  : %s\n", chaine);
        char* chCryptee = chiffrerCesar(chaine, 4);
        printf("Chaine cryptee   : %s\n", chCryptee);
        char* chDecryptee = dechiffrerCesar(chCryptee, 4);
        printf("Chaine decryptee : %s\n", chDecryptee);

        char cle[] = "azerty";
        chCryptee = chiffrerVigenere(chaine, cle);
        printf("\n\nChaine cryptee   : %s\n", chCryptee);
        chDecryptee = dechiffrerVigenere(chCryptee, cle);
        printf("Chaine decryptee : %s\n", chDecryptee);
        free(chCryptee);
        free(chDecryptee);
        

    for (int i=0; i<128; i++) {
        printf("ASCII %d : %c\n", i, (char) i);
    }

    char * ficPath = NULL;
    size_t taille = 200;

    printf("taille : %ld\n", taille);
    printf("Entrez le nom du fichier que vous souhaitez chiffré (sans extension) : ");
    getline(&ficPath, &taille, stdin);
    ficPath[strlen(ficPath)-1] = '\0'; 
    strcat(ficPath, ".txt");
    printf("%s\n", ficPath);
    printf("%c\n", ficPath[strlen(ficPath)-1]);
    if (ficPath[strlen(ficPath)] == '\0') {
        printf("OK\n");
    } else {
        printf("KO\n");
    }
    printf("taille : %ld\n", taille);
    
    char* cle = NULL;
    char* validCle = NULL;
    size_t taille;
    printf("OK before\n");
    getline(&cle, &taille, stdin);
    cle[strlen(cle)-1] = '\0';
    printf("cle : %s\n", cle);
    validCle = adapterCleVigenere(20, cle);
    printf("validCle : %s\n", validCle);
    free(cle);
    free(validCle);
    printf("OK after\n");
    */

   FILE* fic = NULL;
   int tab[128] = {0};
   fic = fopen("texte.txt", "r");
   stockerFrequence(tab, fic);
   fclose(fic);
   afficherTab(tab);
   printf("test : |%c|\n", indiceMax(tab));


    while (1) {
        affichageMenuChiffrement();
        switch (choixMenu()) {
            case 0:
                printf("\nVeuillez saisir un chiffre qui correspond à un choix\n");
                break;
            case 1:
                chiffrementCesar();
                break;
            case 2:
                chiffrementDeVigenere();
                break;
            case 3:
                printf("\nFin du programme...\n");
                exit(EXIT_SUCCESS);
                break;
            default :
                printf("\nVeuillez saisir un chiffre qui correspond à un choix\n");
        }
    }


    return 1;

}