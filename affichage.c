#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "affichage.h"
#include "vigenere.h"
#include "cesar.h"
#include "hill.h"

int choixMenu() {
    char* choix = NULL;
    size_t taille = 0;
    int code;
    if (getline(&choix, &taille, stdin) != 2 || !isdigit(choix[0])) {
        free(choix);
        return 0;
    } else {
        code = atoi(choix);
        free(choix);
        return code;
    }
}

void affichageMenuChiffrement() {
    printf("\n              CHOISISSEZ LE CHIFFREMENT SOUHAITÉ\n\n");
    printf("******************************\n");
    printf("* 1. Chiffrement de Cesar    *\n");
    printf("* 2. Chiffrement de Vigenere *\n");
    printf("* 3. Chiffrement de Hill     *\n");
    printf("* 4. Fin du programme        *\n");
    printf("******************************\n");
    printf("\nVotre choix : ");
}

void affichageMenuTexte() {
    printf("*******************************************\n");
    printf("* 1. Chiffrer un texte entré au clavier   *\n");
    printf("* 2. Chiffrer un fichier texte            *\n");
    printf("* 3. Déchiffrer un texte entré au clavier *\n");
    printf("* 4. Déchiffrer un fichier texte          *\n");
    printf("* 5. Revenir au choix du chiffrement      *\n");
    printf("* 6. Fin du programme                     *\n");
    printf("*******************************************\n");
    printf("\nVotre choix : ");
}

void chiffrementVigenere() {
    int choix = 0;
    while (choix!=5) {
        printf("\n                    CHIFFREMENT DE VIGENERE\n\n");
        affichageMenuTexte();
        switch (choix = choixMenu()) {
            case 0:
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
                break;
            case 1:
                chiffrerEntreeVigenere();
                break;
            case 2:
                chiffrerFichierVigenere();
                break;
            case 3:
                dechiffrerEntreeVigenere();
                break;
            case 4:
                dechiffrerFichierVigenere();
                break;
            case 5:
                break;
            case 6:
                printf("\nFin du programme...\n");
                exit(EXIT_SUCCESS);
                break;
            default :
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
        }
    }
}

void chiffrementCesar() {
    int choix = 0;
    while (choix!=5) {
        printf("\n                        CHIFFREMENT CESAR\n\n");
        affichageMenuTexte();
        switch (choix = choixMenu()) {
            case 0:
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
                break;
            case 1:
                chiffrerEntreeCesar();
                break;
            case 2:
                chiffrerFichierCesar();
                break;
            case 3:
                dechiffrerEntreeCesar();
                break;
            case 4:
                dechiffrerFichierCesar();
                break;
            case 5:
                break;
            case 6:
                printf("\nFin du programme...\n");
                exit(EXIT_SUCCESS);
                break;
            default :
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
        }
    }
}

void chiffrementHill() {
    int choix = 0;
    while (choix!=5) {
        printf("\n                         CHIFFREMENT HILL\n\n");
        affichageMenuTexte();
        switch (choix = choixMenu()) {
            case 0:
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
                break;
            case 1:
                chiffrerEntreeHill();
                break;
            case 2:
                chiffrerFichierHill();
                break;
            case 3:
                dechiffrerEntreeHill();
                break;
            case 4:
                dechiffrerFichierHill();
                break;
            case 5:
                break;
            case 6:
                printf("\nFin du programme...\n");
                exit(EXIT_SUCCESS);
                break;
            default :
                printf("\nVeuillez saisir un chiffre qui correspond à un choix.\n");
        }
    }
}