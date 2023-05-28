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
*  Nom du fichier : vigenere.c                                                *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vigenere.h"
#include "chiffrement.h"

char* chiffrerVigenere(char * chaine, char* cle) {
    char* validKey = adapterCleVigenere(strlen(chaine), cle);
    char* chaineCryptee = malloc( (strlen(chaine)+1) * sizeof(char) );
    //On chiffre les carcatères un par un
    for (int i=0; i < (int) strlen(chaine); i++) {
        chaineCryptee[i] = chiffrerCharVigenere(chaine[i], (int) validKey[i]);
    }
    free(validKey);
    chaineCryptee[strlen(chaine)] = '\0';
    return chaineCryptee;
}


char chiffrerCharVigenere(char c, int cle) {
    char charCrypte = (c + cle) % 128;
    //On continue à chiffrer tant que le caractère n'est pas affichable
    while (!isAffichableChar(charCrypte)) {
        charCrypte = (charCrypte + cle) % 128;
    }
    return charCrypte;
}


char* dechiffrerVigenere(char* chaine, char* cle) {
    char* validKey = adapterCleVigenere(strlen(chaine), cle);
    char* chaineDecryptee = malloc( (strlen(chaine)+1) * sizeof(char) );
    //On déchiffre les caractères un par un
    for (int i=0; i < (int) strlen(chaine); i++) {
        chaineDecryptee[i] = dechiffrerCharVigenere(chaine[i], (int) validKey[i]);
    }
    free(validKey);
    chaineDecryptee[strlen(chaine)] = '\0';
    return chaineDecryptee;
}


char dechiffrerCharVigenere(char c, int cle) {
    //On inverse la clé pour déchiffrer, -10 = +118   mod 128
    cle = 128 - cle;
    char charDecrypte = (c + cle) % 128;
    //On continue à déchiffrer tant que le caractère n'est pas affichable
    while (!isAffichableChar(charDecrypte)) {
        charDecrypte = (charDecrypte + cle) % 128;
    }
    return charDecrypte;
}


char* adapterCleVigenere(int size, char* key) {
    char* validKey = malloc(size * (sizeof(char)+1));
    if (validKey == NULL) {
        return NULL;
    }
    //On répète les caractères pour adapter la taille de la chaine
    for (int i=0; i<size; i++) {
        validKey[i] = key[i % strlen(key)];
    }
    validKey[size] = '\0';
    return validKey;
}


int chiffrerFichierVigenere() {
    FILE* fic            = NULL;
    FILE* ficCryptee     = NULL;
    char* ficPath        = NULL;
    char* ficCrypteePath = NULL;
    char* chaine         = NULL;
    char* cle            = NULL;
    int numLigne         = 1;
    size_t taille        = 0;
    //On ouvre le fichier à lire
    if ( ouvrirFichierClair(&fic, &ficPath) != 1 ) {
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, cle);
        return -1;
    }
    //On crée le fichier dans lequel on va écrire
    if ( creerFichierChiffre(&ficCryptee, &ficCrypteePath) != 1 ) {
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, cle);
        return -2;
    }
    //On récupère la clé de chiffrement
    if ( entrerCleVigenere(&cle) != 1 ) {
        fclose(ficCryptee);
        remove(ficCrypteePath);
        ficCryptee = NULL;
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, cle);
        return 0;
    }
    //On chiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while ( getline(&chaine, &taille, fic) != -1 ) {
        if ( chiffrerLigneFichierVigenere(chaine, ficCryptee, cle, numLigne) != 1 ) {
            cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, cle);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicChiffre(ficCrypteePath);
    cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, cle);
    return 1;
}

int chiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne) {
    char* chaineCryptee = NULL;
    int index = strlen(chaine)-1;
    //On enlève les caractères de fin de ligne non affichable : \r, \n,...
    while (index >= 0 && !isAffichableChar(chaine[index])) {
        chaine[index] = '\0';
        index--;
    }
    //On vérifie si la ligne contient bien seulement des caractères affichables
    if (!isAffichableString(chaine)) {
        printf("\nErreur, la chaine contient des caractères interdits.\n");
        printf("Le chiffrement s'est arrêté à la ligne %d.\n", numLigne);
        return -1;
    }
    chaineCryptee = chiffrerVigenere(chaine, cle);
    if (chaineCryptee == NULL) {
        perror("\nEchec chiffrement (malloc) ");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineCryptee);
    free(chaineCryptee);
    return 1;
}

int dechiffrerFichierVigenere() {
    FILE* ficCryptee       = NULL;
    FILE* ficDecryptee     = NULL;
    char* ficCrypteePath   = NULL;
    char* ficDecrypteePath = NULL;
    char* chaine           = NULL;
    char* cle              = NULL;
    int numLigne           = 1;
    size_t taille          = 0;
    //On ouvre le fichier que l'on souhaite déchiffré
    if ( ouvrirFichierChiffre(&ficCryptee, &ficCrypteePath) != 1 ) {
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, cle);
        return -1;
    }
    //On crée le fichier dans lequel on va écrire le texte en clair
    if ( creerFichierDechiffre(&ficDecryptee, &ficDecrypteePath) != 1 ) {
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, cle);
        return -2;
    }
    //On récupère la clé de chiffrement
    if ( entrerCleVigenere(&cle) != 1 ) {
        fclose(ficDecryptee);
        remove(ficDecrypteePath);
        ficDecryptee = NULL;
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, cle);
        return 0;
    }
    //On déchiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while (getline(&chaine, &taille, ficCryptee) != -1) {
        if ( dechiffrerLigneFichierVigenere(chaine, ficDecryptee, cle, numLigne) != 1 ) {
            cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, cle);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicDechiffre(ficDecrypteePath);
    cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, cle);
    return 1;
}

int dechiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne) {
    char* chaineDecryptee;
    int index = strlen(chaine)-1;
    //On enlève les carcatères de fin de ligne non affichable : \r, \n,...
    while (index >= 0 && !isAffichableChar(chaine[index])) {
        chaine[index] = '\0';
        index--;
    }
    //On vérifie si la chaine est affichable
    if (!isAffichableString(chaine)) {
        printf("\nErreur, le fichier contient des caractères interdits.\n");
        printf("Le chiffrement s'est arrêté à la ligne %d.\n", numLigne);
        return -1;
    }
    chaineDecryptee = dechiffrerVigenere(chaine, cle);
    if (chaineDecryptee == NULL) {
        perror("\nEchec déchiffrement (malloc) ");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineDecryptee);
    free(chaineDecryptee);
    return 1;    
}


int chiffrerEntreeVigenere() {
    char* chaine        = NULL;
    char* chaineCryptee = NULL;
    char* cle           = NULL;
    //On récupère la chaine à chiffrée
    if (entrerChaineEnClair(&chaine) != 1) {
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleVigenere(&cle) != 1) {
        free(chaine);
        return -1;
    }
    printf("\nChaine en clair : \n%s\n", chaine);
    chaineCryptee = chiffrerVigenere(chaine, cle);
    //On vérifie le retour de chiffrerVigenere
    if (chaineCryptee == NULL) {
        perror("Echec chiffrement (malloc) ");
        free(chaine);
        free(cle);
        return 0;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    free(chaine);
    free(chaineCryptee);
    free(cle);
    return 1;
}


int dechiffrerEntreeVigenere() {
    char* chaine        = NULL;
    char* chaineDecryptee = NULL;
    char* cle           = NULL;
    if ( entrerChaineChiffree(&chaine) != 1 ) {
        return -2;
    }
    if ( entrerCleVigenere(&cle) != 1 ) {
        free(chaine);
        return -1;
    }
    printf("\nChaine en clair : \n%s\n", chaine);
     //On vérifie le retour de déchiffrerVigenere
    chaineDecryptee = dechiffrerVigenere(chaine, cle);
    if (chaineDecryptee == NULL) {
        perror("Echec chiffrement (malloc) ");
        free(chaine);
        free(cle);
        return 0;
    }
    printf("\nChaine déchiffrée : \n%s\n", chaineDecryptee);
    free(chaine);
    free(chaineDecryptee);
    free(cle);
    return 1;
}

int entrerCleVigenere(char** cle) {
    size_t taille = 0;
    printf("Entrez la clé de chiffrement (caractères ASCII de 32 à 126) : ");
    //On récupère la clé au format char[]
    if (getline(cle, &taille, stdin) == -1) {
        perror("\nErreur lors de la lecture de la clé ");
        return -1;
    }
    (*cle)[strlen(*cle)-1] = '\0';
    //On vérifie si la clé est affichable
    if ( !isAffichableString(*cle) ) {
        printf("\nErreur, la clé de chiffrement contient des caractères invalides.\n");
        free(*cle);
        *cle = NULL;
        return 0;
    }
    return 1;
}