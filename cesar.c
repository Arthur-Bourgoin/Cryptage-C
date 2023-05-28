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
*  Nom du fichier : cesar.c                                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "cesar.h"
#include "chiffrement.h"


char* chiffrerCesar(char* chaine, int cle) {
    int validKey = adapterCleCesar(cle);
    char* chaineCryptee = malloc( (strlen(chaine)+1) * sizeof(char) );
    if (chaineCryptee == NULL) {
        return NULL;
    }
    //On chiffre les caractères un par un
    for (int i = 0; i < (int) strlen(chaine); i++) {
        chaineCryptee[i] = chiffrerCharCesar(chaine[i], validKey);
    }
    chaineCryptee[strlen(chaine)] = '\0';
    return chaineCryptee;    
}


char chiffrerCharCesar(char c, int cle) {
    char charCrypte = (c + cle) % 128;
    //On continue à chiffrer tant que le caractère n'est pas affichable
    while (!isAffichableChar(charCrypte)) {
        charCrypte = (charCrypte + cle) % 128;
    }
    return charCrypte;
}


char* dechiffrerCesar(char* chaine, int cle) {
    int validKey = adapterCleCesar(cle);
    char* chaineDecryptee = malloc( (strlen(chaine)+1) * sizeof(char) );
    if (chaineDecryptee == NULL) {
        return NULL;
    }
    //On déchiffre les carcatères un par un
    for (int i = 0; i < (int) strlen(chaine); i++) {
        chaineDecryptee[i] = dechiffrerCharCesar(chaine[i], validKey);
    }
    chaineDecryptee[strlen(chaine)] = '\0';
    return chaineDecryptee; 
}


char dechiffrerCharCesar(char c, int cle) {
    //On inverse la clé pour déchiffrer, -10 = +118   mod 128
    cle = 128 - cle;
    char charDecrypte = (c + cle) % 128;
    //On continue à déchiffrer tant que le caractère n'est pas affichable
    while (!isAffichableChar(charDecrypte)) {
        charDecrypte = (charDecrypte + cle) % 128;
    }
    return charDecrypte;
}


int adapterCleCesar(int cle) {
    int validKey = cle % 128;
    //Si la clé est négative, on l'adapte en ajoutant 128 : -3 = +125  mod 128
    if (validKey < 0) {
        validKey = 128 + validKey;
    }
    return validKey;
}


int chiffrerFichierCesar() {
    FILE* fic             = NULL;
    FILE* ficCryptee      = NULL;
    char * ficPath        = NULL;
    char * ficCrypteePath = NULL;
    char * chaine         = NULL;
    char * entreeCle      = NULL;
    int cle = 0;
    int numLigne = 1;
    size_t taille = 0;
    //On ouvre le fichier à lire
    if (ouvrirFichierClair(&fic, &ficPath) != 1) {
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, entreeCle);
        return -1;
    }
    //On crée le fichier dans lequel on va écrire
    if (creerFichierChiffre(&ficCryptee, &ficCrypteePath) != 1) {
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, entreeCle);
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleCesar(&entreeCle, &cle) != 1) {
        fclose(ficCryptee);
        remove(ficCrypteePath);
        ficCryptee = NULL;
        cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, entreeCle);
        return 0;
    }
    //On chiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while (getline(&chaine, &taille, fic) != -1) {
        if ( chiffrerLigneFichierCesar(chaine, ficCryptee, cle, numLigne) != 1 ) {
            cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, entreeCle);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicChiffre(ficCrypteePath);
    cleanUp(fic, ficCryptee, ficPath, ficCrypteePath, chaine, entreeCle);
    return 1;
}


int chiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne) {
    char* chaineCryptee = NULL;
    int index = strlen(chaine)-1;
    //On enlève les caractères de fin de ligne non affichable : \r, \n,...
    while ( index>=0 && !isAffichableChar(chaine[index])) {
        chaine[index] = '\0';
        index--;
    }
    //On vérifie si la ligne contient bien seulement des caractères affichables
    if ( !isAffichableString(chaine) ) {
        printf("\nErreur, le fichier contient des caractères interdits.\n");
        printf("Le chiffrement s'est arrêté à la ligne %d.\n", numLigne);
        return -1;
    }
    chaineCryptee = chiffrerCesar(chaine, cle);
    if (chaineCryptee == NULL) {
        perror("\nEchec chiffrement (malloc) ");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineCryptee);
    free(chaineCryptee);
    return 1;
}


int dechiffrerFichierCesar() {
    FILE* ficCryptee        = NULL;
    FILE* ficDecryptee      = NULL;
    char * ficCrypteePath   = NULL;
    char * ficDecrypteePath = NULL;
    char * chaine           = NULL;
    char * entreeCle        = NULL;
    size_t taille = 0;
    int cle = 0;
    int numLigne = 1;
    //On ouvre le fichier que l'on souhaite déchiffré
    if (ouvrirFichierChiffre(&ficCryptee, &ficCrypteePath) != 1) {
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, entreeCle);
        return -1;        
    }
    //On crée le fichier dans lequel on va écrire le texte en clair
    if (creerFichierDechiffre(&ficDecryptee, &ficDecrypteePath) != 1) {
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, entreeCle);
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleCesar(&entreeCle, &cle) != 1) {
        fclose(ficDecryptee);
        remove(ficDecrypteePath);
        ficDecryptee = NULL;
        cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, entreeCle);
        return 0;
    }
    //On déchiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while (getline(&chaine, &taille, ficCryptee) != -1) {
        if ( dechiffrerLigneFichierCesar(chaine, ficDecryptee, cle, numLigne) != 1 ) {
            cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, entreeCle);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicDechiffre(ficDecrypteePath);
    cleanUp(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, entreeCle);
    return 1;
}


int dechiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne) {
    char* chaineDecryptee = NULL;
    int index = strlen(chaine)-1;
    //On enlève les carcatères de fin de ligne non affichable : \r, \n,...
    while ( index>=0 && !isAffichableChar(chaine[index])) {
        chaine[index] = '\0';
        index--;
    }
    //On vérifie si la chaine est affichable
    if ( !isAffichableString(chaine) ) {
        printf("\nErreur, le fichier contient des caractères interdits.\n");
        printf("Le chiffrement s'est arrêté à la ligne %d.\n", numLigne);
        return -1;
    }
    chaineDecryptee = dechiffrerCesar(chaine, cle);
    if (chaineDecryptee == NULL) {
        perror("\nEchec déchiffrement (malloc) ");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineDecryptee);
    free(chaineDecryptee);
    return 1;
}


int chiffrerEntreeCesar() {
    char* chaine          = NULL;
    char* chaineCryptee   = NULL;
    char* entreeCle       = NULL;
    int cle;
    //On récupère la chaine à chiffrée
    if (entrerChaineEnClair(&chaine) != 1) {
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleCesar(&entreeCle, &cle) != 1) {
        free(chaine);
        return -1;
    }
    printf("\nChaine en clair : \n%s\n", chaine);
    chaineCryptee = chiffrerCesar(chaine, cle);
    //On vérifie le retour de chiffrerCésar
    if (chaineCryptee == NULL) {
        perror("Echec chiffrement (malloc) ");
        free(chaine);
        free(entreeCle);
        return 0;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    free(chaine);
    free(chaineCryptee);
    free(entreeCle);
    return 1;
}


int dechiffrerEntreeCesar() {
    char* chaineCryptee   = NULL;
    char* chaineDecryptee = NULL;
    char* entreeCle       = NULL;
    int cle;
    //On récupère la chaine à déchiffrée
    if (entrerChaineChiffree(&chaineCryptee) != 1) {
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleCesar(&entreeCle, &cle) != 1) {
        free(chaineCryptee);
        return -1;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    chaineDecryptee = dechiffrerCesar(chaineCryptee, cle);
     //On vérifie le retour de déchiffrerCesar
    if (chaineDecryptee == NULL) {
        perror("Echec déchiffrement (malloc) ");
        free(chaineCryptee);
        free(entreeCle);
        return 0;
    }
    printf("\nChaine déchiffrée : \n%s\n", chaineDecryptee);
    free(chaineCryptee);
    free(chaineDecryptee);
    free(entreeCle);
    return 1;
}


int entrerCleCesar(char** entreeCle, int* cle) {
    size_t taille = 0;
    printf("Entrez la clé de chiffrement (caractères numériques) : ");
    //On récupère la clé au format char[]
    if (getline(entreeCle, &taille, stdin) == -1) {
        perror("\nErreur lors de la lecture de la clé ");
        return -1;
    }
    (*entreeCle)[strlen(*entreeCle)-1] = '\0';
    //On vérifie si le format de la clé est bien valide
    if ((*cle = atoi(*entreeCle)) == 0) {
        printf("\nErreur, la clé de chiffrement n'est pas valide.\n");
        free(*entreeCle);
        *entreeCle = NULL;
        return 0;
    }
    return 1;
}

