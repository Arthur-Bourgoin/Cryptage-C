/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 3                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Chiffrement de messages                                         *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : BOURGOIN Arthur                                              *
*                                                                             *
*  Nom-prénom2 : BIGNON Charley                                               *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : main.c                                                    *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affichage.h"


int main() {
    
    int choix = 0;
    while (choix != 4) {
        affichageMenuChiffrement();
        switch (choix = choixMenu()) {
            case 1:
                chiffrementCesar();
                break;
            case 2:
                chiffrementVigenere();
                break;
            case 3:
                chiffrementHill();
                break;
            case 4:
                printf("\nFin du programme...\n");
                break;
            default :
                printf("\nVeuillez saisir un chiffre qui correspond à un choix\n");
        }
    }
    return EXIT_SUCCESS;
}