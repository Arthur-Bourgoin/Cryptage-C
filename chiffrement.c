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
*  Nom du fichier : chiffrement.c                                             *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "chiffrement.h"


int isAffichableChar(char c) {
    if ((int) c < 32 || c == 127) {
        return 0;
    }
    return 1;
}

int isAffichableString(char * ch) {
    for (int i = 0; i < (int) strlen(ch); i++) {
        if (isAffichableChar(ch[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int ouvrirFichierClair(FILE** fic, char** ficPath) {
    size_t taille = 0;
    printf("\nEntrez le nom du fichier que vous souhaitez chiffré (sans extension) : ");
    //On récupère le nom du fichier
    if (getline(ficPath, &taille, stdin) == -1) {
        perror("\nErreur lors de la lecture du chemin du fichier ");
        return -1;
    }
    (*ficPath)[strlen(*ficPath)-1] = '\0';
    strcat(*ficPath, ".txt");
    //On ouvre le fichier en mode lecture
    if ((*fic = fopen(*ficPath, "r")) == NULL) {
        perror("\nErreur lors de l'ouverture du fichier ");
        return 0;
    }
    return 1;
}

int ouvrirFichierChiffre(FILE** fic, char** ficPath) {
    size_t taille = 0;
    printf("\nEntrez le nom du fichier que vous souhaitez déchiffré (sans extension) : ");
    //On récupère le nom du fichier
    if (getline(ficPath, &taille, stdin) == -1) {
        perror("\nErreur lors de la lecture du chemin du fichier ");
        return -1;
    }
    (*ficPath)[strlen(*ficPath)-1] = '\0';
    strcat(*ficPath, ".txt");
    //On ouvre le fichier en mode lecture 
    if ((*fic = fopen(*ficPath, "r")) == NULL) {
        perror("\nErreur lors de l'ouverture du fichier ");
        return 0;
    }
    return 1;
}

int creerFichierChiffre(FILE** fic, char** ficPath) {
    size_t taille = 0;
    printf("Entrez le nom du fichier chiffré à créer (sans extension) : ");
    //On récupère le nom du fichier
    if (getline(ficPath, &taille, stdin) == -1) {
        perror("\nErreur lors de la lecture du chemin du fichier ");
        return -1;
    }
    (*ficPath)[strlen(*ficPath)-1] = '\0';
    strcat(*ficPath, ".txt");
    //On ouvre (ou crée) le fichier en mode écriture
    if ((*fic = fopen(*ficPath, "w")) == NULL) {
        perror("\nErreur lors de l'ouverture du fichier ");
        return 0;
    }
    return 1;
}

int creerFichierDechiffre(FILE** fic, char** ficPath) {
    size_t taille = 0;
    printf("Entrez le nom du fichier déchiffré à créer (sans extension) : ");
    //On récupère le nom du fichier
    if (getline(ficPath, &taille, stdin) == -1) {
        perror("Erreur lors de lecture du chemin du fichier ");
        return -1;
    }
    (*ficPath)[strlen(*ficPath)-1] = '\0';
    strcat(*ficPath, ".txt");
    //On ouvre (ou crée) le fichier en mode écriture
    if ((*fic = fopen(*ficPath, "w")) == NULL) {
        perror("\nErreur lors de l'ouverture du fichier ");
        return 0;
    }
    return 1;
}

int entrerChaineEnClair(char** chaine) {
    size_t taille = 0;
    printf("\nEntrez une chaine de caractères affichables en ASCII (de 32 à 126) : ");
    //On récupère la chaine en claire
    if (getline(chaine, &taille, stdin) == -1) {
        perror("Erreur lors de la lecture de la chaine ");
        return -1;
    }
    (*chaine)[strlen(*chaine)-1] = '\0';
    //On vérifie que la chaine ne contient pas de caractères interdits
    if (!isAffichableString(*chaine)) {
        printf("\nErreur, la chaine contient des caractères interdits.\n");
        free(*chaine);
        return 0;
    }
    return 1;
}

int entrerChaineChiffree(char** chaine) {
    size_t taille = 0;
    printf("\nEntrez une chaine chiffrée (caractères ASCII de 32 à 126) : ");
    //On récupère la chaine chiffrée
    if (getline(chaine, &taille, stdin) == -1) {
        perror("Erreur lors de la lecture de la chaine ");
        return -1;
    }
    (*chaine)[strlen(*chaine)-1] = '\0';
    //On vérifie que la chaine ne contient pas de carcatères interdits
    if (!isAffichableString(*chaine)) {
        printf("\nErreur, la chaine contient des caractères interdits.\n");
        free(*chaine);
        return 0;
    }
    return 1;
}


void afficherCheminFicChiffre(char* ficPath) {
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\nLe fichier chiffré est enregistré dans : %s/%s\n", cwd, ficPath);
    } else {
        printf("\nLe fichier chiffré est enregistré dans : ./%s\n", ficPath);
    }
}

void afficherCheminFicDechiffre(char* ficPath) {
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\nLe fichier déchiffré est enregistré dans : %s/%s\n", cwd, ficPath);
    } else {
        printf("\nLe fichier déchiffré est enregistré dans : ./%s\n", ficPath);
    }
}

void cleanUp(FILE* fic1, FILE* fic2, char* chaine1, char* chaine2, char* chaine3, char* chaine4) {
    if (fic1 != NULL)
        fclose(fic1);
    if (fic2 != NULL)
        fclose(fic2);
    if (chaine1 != NULL)
        free(chaine1);
    if (chaine2 != NULL)
        free(chaine2);
    if (chaine3 != NULL)
        free(chaine3);
    if (chaine4 != NULL)
        free(chaine4);
}