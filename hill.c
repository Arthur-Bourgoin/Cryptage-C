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
*  Nom du fichier : hill.c                                                    *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chiffrement.h"
#include "hill.h"

char* chiffrerHill(char* chaine, int** matrixKey) {
    //On adapte le nombre de caractère de la chaine
    char* chaineAdaptee = adapterChaineHill(chaine);
    if (chaineAdaptee==NULL) {
        return NULL;
    }
    char* chaineChiffree = malloc(sizeof(char) * (strlen(chaineAdaptee)+1));
    if (chaineChiffree == NULL) {
        free(chaineAdaptee);
        return NULL;
    }
    //On réduit la matrice modulo 127 afin de réduire la complexité des opérations
    int** validMatrixKey = adapterMatriceMod(matrixKey);
    if (validMatrixKey == NULL) {
        free(chaineChiffree);
        free(chaineAdaptee);
        return NULL;
    }
    char* matriceChiffree = NULL;
    //On chiffre les caractères deux par deux
    for (int i=0; i < (int) strlen(chaineAdaptee); i+= 2) {
        matriceChiffree = chiffrerCharHill(chaineAdaptee[i], chaineAdaptee[i+1], validMatrixKey);
        if (matriceChiffree == NULL) {
            free(chaineChiffree);
            free(chaineAdaptee);
            free(validMatrixKey[0]);
            free(validMatrixKey[1]);
            free(validMatrixKey);
            return NULL;
        }
        chaineChiffree[i] = matriceChiffree[0];
        chaineChiffree[i+1] = matriceChiffree[1];
        free(matriceChiffree);
    }
    chaineChiffree[strlen(chaineAdaptee)] = '\0';
    free(chaineAdaptee);
    free(validMatrixKey[0]);
    free(validMatrixKey[1]);
    free(validMatrixKey);
    return chaineChiffree;
}

char* chiffrerCharHill(char c1, char c2, int** matrixKey) {
    //Tableau qui va contenir les deux caractères chiffrés
    char* matriceChiffree = malloc(2 * sizeof(char));
    if (matriceChiffree == NULL) {
        return NULL;
    }
    //Tableau qui va contenir les deux caractères chiffrés si besoin entre chaque boucle 
    char* newMatriceChiffree = malloc(2 * sizeof(char));
    if (newMatriceChiffree == NULL) {
        free(matriceChiffree);
        return NULL;
    }
    matriceChiffree[0] = (matrixKey[0][0]*c1 + matrixKey[0][1]*c2) % 127;
    matriceChiffree[1] = (matrixKey[1][0]*c1 + matrixKey[1][1]*c2) % 127;
    //Tant que un des deux caractères n'est pas affichable, on continue à chiffrer
    //Boucle infinie impossible car les 2 caractères en clair sont obligatoirement affichables
    //   --> Dans une application linéaire, un vecteur ne peut pas avoir 2 antécédents
    while (!isAffichableChar(matriceChiffree[0]) || !isAffichableChar(matriceChiffree[1])) {
            newMatriceChiffree[0] = (matrixKey[0][0]*matriceChiffree[0] + matrixKey[0][1]*matriceChiffree[1]) % 127;
            newMatriceChiffree[1] = (matrixKey[1][0]*matriceChiffree[0] + matrixKey[1][1]*matriceChiffree[1]) % 127;
            matriceChiffree[0] = newMatriceChiffree[0];
            matriceChiffree[1] = newMatriceChiffree[1];
    }
    free(newMatriceChiffree);
    return matriceChiffree;
}

char* dechiffrerHill(char* chaine, int** matrixKey) {
    //On adapte le nombre de caractère de la chaine
    char* chaineAdaptee = adapterChaineHill(chaine);
    if (chaineAdaptee == NULL) {
        return NULL;
    }
    char* chaineDechiffree = malloc(sizeof(char) * (strlen(chaineAdaptee)+1));
    if (chaineDechiffree == NULL) {
        free(chaineAdaptee);
        return NULL;
    }
    //On récupère l'inverse de la matrice de chiffrement en paramètre
    int** inverseMatrixKey = inverserMatriceMod(matrixKey);
    if (inverseMatrixKey == NULL) {
        free(chaineAdaptee);
        free(chaineDechiffree);
        return NULL;
    }
    char* matriceDechiffree = NULL;
    //On déchiffre les carcatères deux par deux
    for (int i=0; i < (int) strlen(chaineAdaptee); i+= 2) {
        matriceDechiffree = chiffrerCharHill(chaineAdaptee[i], chaineAdaptee[i+1], inverseMatrixKey);
        if (matriceDechiffree == NULL) {
            free(chaineDechiffree);
            free(chaineAdaptee);
            free(inverseMatrixKey[0]);
            free(inverseMatrixKey[1]);
            free(inverseMatrixKey);
            return NULL;
        }
        chaineDechiffree[i] = matriceDechiffree[0];
        chaineDechiffree[i+1] = matriceDechiffree[1];
        free(matriceDechiffree);
    }
    chaineDechiffree[strlen(chaineAdaptee)] = '\0';
    free(chaineAdaptee);
    free(inverseMatrixKey[0]);
    free(inverseMatrixKey[1]);
    free(inverseMatrixKey);
    return chaineDechiffree;
}

char* adapterChaineHill(char* chaine) {
    int taille = strlen(chaine);
    if (taille % 2 == 1) {
        taille++;
    }
    //On crée une nouvelle chaine de taille paire
    char* chaineAdaptee = malloc(sizeof(char) * (taille+1));
    if (chaineAdaptee == NULL) {
        return NULL;
    }
    //Si nécessaire, on ajoute un espace '' en fin de chaine pour
    //que le nombre de caractère soit pair
    strcpy(chaineAdaptee, chaine);
    if (taille != (int) strlen(chaine)) {
        chaineAdaptee[taille-1]=' ';
        chaineAdaptee[taille]='\0'; 
    }
    return chaineAdaptee;
}

int** adapterMatriceMod(int** matrixKey) {
    //Initialisation de la matrice
    int** matriceAdaptee = malloc(2 * sizeof(int*));
    if (matriceAdaptee == NULL) {
        return NULL;
    }
    matriceAdaptee[0] = malloc(2 * sizeof(int));
    if (matriceAdaptee[0] == NULL) {
        free(matriceAdaptee);
        return NULL;
    }
    matriceAdaptee[1] = malloc(2 * sizeof(int));
    if (matriceAdaptee[1] == NULL) {
        free(matriceAdaptee);
        free(matriceAdaptee[0]);
        return NULL;
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            //On réduit modulo 127
            matriceAdaptee[i][j] = matrixKey[i][j] % 127;
            //On supprime les coefficients négatifs
            if (matriceAdaptee[i][j] < 0) {
                matriceAdaptee[i][j] += 127;
            }
        }
    }
    return matriceAdaptee;
}

int** inverserMatriceMod(int** matrixKey) {
    //Initialisation de la matrice
    int** matriceInverse = malloc(sizeof(int*) * 2);
    if (matriceInverse == NULL) {
        return NULL;
    }
    matriceInverse[0] = malloc(sizeof(int) * 2);
    if (matriceInverse[0] == NULL) {
        free(matriceInverse);
        return NULL;
    }
    matriceInverse[1] = malloc(sizeof(int) * 2);
    if (matriceInverse[1] == NULL) {
        free(matriceInverse[0]);
        free(matriceInverse);
        return NULL;
    }
    int** validMatrix = NULL;
    //Calcul du déterminant
    int det = (matrixKey[0][0]*matrixKey[1][1] - matrixKey[0][1]*matrixKey[1][0]) % 127;
    while (det<0) {
        det += 127;
    }
    if (det==0) {
        return NULL;
    }
    //On cherche l'inverse du déterminant modulo 127 et on l'affecte à det
    for (int i=1; i<127; i++) {
        if (((det*i) % 127) == 1) {
            det = i;
            break;
        }
    }
    //On calcule l'inverse de la matrice modulo 127 à l'aide de l'inverse du déterminant
    matriceInverse[0][0] = (det * matrixKey[1][1]);
    matriceInverse[0][1] = (det * (-1 * matrixKey[0][1] + 127));
    matriceInverse[1][0] = (det * (-1 * matrixKey[1][0] + 127));
    matriceInverse[1][1] = (det * matrixKey[0][0]);
    //On réduit la matrice modulo 127
    validMatrix = adapterMatriceMod(matriceInverse);
    free(matriceInverse[0]);
    free(matriceInverse[1]);
    free(matriceInverse);
    return validMatrix;
}

int chiffrerFichierHill() {
    FILE* fic             = NULL;
    FILE* ficCryptee      = NULL;
    char * ficPath        = NULL;
    char * ficCrypteePath = NULL;
    char * chaine         = NULL;
    int** matrixKey       = NULL;
    int numLigne = 1;
    size_t taille = 0;
    //On ouvre le fichier à lire
    if (ouvrirFichierClair(&fic, &ficPath) != 1) {
        cleanUpHill(fic, ficCryptee, ficPath, ficCrypteePath, chaine, matrixKey);
        return -1;
    }
    //On crée le fichier dans lequel on va écrire
    if (creerFichierChiffre(&ficCryptee, &ficCrypteePath) != 1) {
        cleanUpHill(fic, ficCryptee, ficPath, ficCrypteePath, chaine, matrixKey);
        return -2;
    }
    //On récupère la matrice de chiffrement
    if (entrerCleHill(&matrixKey) != 1) {
        fclose(ficCryptee);
        remove(ficCrypteePath);
        ficCryptee = NULL;
        //Inutile de free(), on gère déjà la libération de la mémoire dans entrerCleHill()
        matrixKey = NULL;
        cleanUpHill(fic, ficCryptee, ficPath, ficCrypteePath, chaine, matrixKey);
        return 0;
    }
    //On chiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while (getline(&chaine, &taille, fic) != -1) {
        if ( chiffrerLigneFichierHill(chaine, ficCryptee, matrixKey, numLigne) != 1 ) {
            cleanUpHill(fic, ficCryptee, ficPath, ficCrypteePath, chaine, matrixKey);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicChiffre(ficCrypteePath);
    cleanUpHill(fic, ficCryptee, ficPath, ficCrypteePath, chaine, matrixKey);
    return 1;
}

int chiffrerLigneFichierHill(char* chaine, FILE* fic, int** matrixKey, int numLigne){
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
    chaineCryptee = chiffrerHill(chaine, matrixKey);
    if (chaineCryptee == NULL) {
        perror("\nEchec lors du chiffrement, fonction chiffrerHill().\n");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineCryptee);
    free(chaineCryptee);
    return 1;
}

int dechiffrerFichierHill(){
    FILE* ficCryptee        = NULL;
    FILE* ficDecryptee      = NULL;
    char * ficCrypteePath   = NULL;
    char * ficDecrypteePath = NULL;
    char * chaine           = NULL;
    int** matrixKey         = NULL;
    size_t taille = 0;
    int numLigne = 1;
    //On ouvre le fichier que l'on souhaite déchiffré
    if (ouvrirFichierChiffre(&ficCryptee, &ficCrypteePath) != 1) {
        cleanUpHill(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, matrixKey);
        return -1;        
    }
    //On crée le fichier dans lequel on va écrire le texte en clair
    if (creerFichierDechiffre(&ficDecryptee, &ficDecrypteePath) != 1) {
        cleanUpHill(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, matrixKey);
        return -2;
    }
    //On récupère la clé de chiffrement
    if (entrerCleHill(&matrixKey) != 1) {
        fclose(ficDecryptee);
        remove(ficDecrypteePath);
        ficDecryptee = NULL;
        //Inutile de free(), on gère déjà la libération de la mémoire dans entrerCleHill()
        matrixKey = NULL;
        cleanUpHill(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, matrixKey);
        return 0;
    }
    //On déchiffre les lignes une par une tant qu'on ne rencontre pas d'erreur
    while (getline(&chaine, &taille, ficCryptee) != -1) {
        if ( dechiffrerLigneFichierHill(chaine, ficDecryptee, matrixKey, numLigne) != 1 ) {
            cleanUpHill(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, matrixKey);
            return -3;
        }
        numLigne++;
    }
    afficherCheminFicDechiffre(ficDecrypteePath);
    cleanUpHill(ficCryptee, ficDecryptee, ficCrypteePath, ficDecrypteePath, chaine, matrixKey);
    return 1;
}

int dechiffrerLigneFichierHill(char* chaine, FILE* fic, int** matrixKey, int numLigne){
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
    chaineDecryptee = dechiffrerHill(chaine, matrixKey);
    if (chaineDecryptee == NULL) {
        perror("\nEchec lors du déchiffrement, fonction chiffrerHill().\n");
        return 0;
    }
    fprintf(fic, "%s\r\n", chaineDecryptee);
    free(chaineDecryptee);
    return 1;
}

int chiffrerEntreeHill(){
    char* chaine          = NULL;
    char* chaineCryptee   = NULL;
    int** matrixKey       = NULL;
    //On récupère la chaine à chiffrée
    if (entrerChaineEnClair(&chaine) != 1) {
        return -2;
    }
    //On récupère la matrice de chiffrement
    if (entrerCleHill(&matrixKey) != 1) {
        free(chaine);
        return -1;
    }
    printf("\nChaine en clair : \n%s\n", chaine);
    chaineCryptee = chiffrerHill(chaine, matrixKey);
    //On vérifie le retour de chiffrerHill
    if (chaineCryptee == NULL) {
        perror("Echec chiffrerHill() ");
        free(chaine);
        free(matrixKey[0]);
        free(matrixKey[1]);
        free(matrixKey);
        return 0;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    free(chaine);
    free(chaineCryptee);
    free(matrixKey[0]);
    free(matrixKey[1]);
    free(matrixKey);
    return 1;
}

int dechiffrerEntreeHill(){
    char* chaineCryptee   = NULL;
    char* chaineDecryptee = NULL;
    int** matrixKey       = NULL;
    //On récupère la chaine à déchiffrée
    if (entrerChaineChiffree(&chaineCryptee) != 1) {
        return -2;
    }
    //On récupère la matrice de chiffrement
    if (entrerCleHill(&matrixKey) != 1) {
        free(chaineCryptee);
        return -1;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    chaineDecryptee = dechiffrerHill(chaineCryptee, matrixKey);
    //On vérifie le retour de dechiffrerHill()
    if (chaineDecryptee == NULL) {
        perror("Echec déchiffrerHill() ");
        free(chaineCryptee);
        free(matrixKey[0]);
        free(matrixKey[1]);
        free(matrixKey);
        return 0;
    }
    printf("\nChaine déchiffrée : \n%s\n", chaineDecryptee);
    free(chaineCryptee);
    free(chaineDecryptee);
    free(matrixKey[0]);
    free(matrixKey[1]);
    free(matrixKey);
    return 1;
}

int entrerCleHill(int*** matrixKey){
    char* entree = NULL;
    size_t taille = 0;
    //Initialisation de la matrice
    *matrixKey = malloc(sizeof(int*) * 2);
    if ((*matrixKey) == NULL) {
        return 0;
    }
    (*matrixKey)[0] = malloc(sizeof(int) * 2);
    if ((*matrixKey)[0] == NULL) {
        free(*matrixKey);
        return 0;
    }
    (*matrixKey)[1] = malloc(sizeof(int) * 2);
    if ((*matrixKey)[1] == NULL) {
        free((*matrixKey)[0]);
        free(*matrixKey);
        return 0;
    }
    printf("Entrez une matrice de chiffrement 2x2 :\n");
    printf("    - valeur 0 interdite pour les coefficients\n");
    printf("    - déterminant obligatoirement différent de 0 (ad-bc != 0)\n\n");
    printf("      [ a   b ]\n");
    printf("      [ c   d ]\n\n");
    //On demande à l'utilisateur de rentrer les coefficients un par un
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            printf("Entrez le caractère M[%d][%d] : ", i, j);
            if (getline(&entree, &taille, stdin) == -1) {
                perror("\nErreur lors de la lecture de la clé.\n");
                free((*matrixKey)[0]);
                free((*matrixKey)[1]);
                free((*matrixKey));
                return -1;
            }
            entree[strlen(entree)-1] = '\0';
            //Test de la validité de chaque coefficients
            if (((*matrixKey)[i][j] = atoi(entree)) == 0) {
                printf("\nErreur, le caractère entré n'est pas valide.\n");
                free(entree);
                free((*matrixKey)[0]);
                free((*matrixKey)[1]);
                free((*matrixKey));
                return -2;
            }
        }
    }
    //Affichage matrice
    printf("\n      [ %d   %d ]\n", (*matrixKey)[0][0], (*matrixKey)[0][1]);
    printf("      [ %d   %d ]\n\n", (*matrixKey)[1][0], (*matrixKey)[1][1]);
    //Vérification de la valeur du déterminant
    int det = ((*matrixKey)[0][0]*(*matrixKey)[1][1] - (*matrixKey)[0][1]*(*matrixKey)[1][0]) % 127;
    if (det<0) {
        det += 127;
    }
    if (det == 0) {
        printf("\nErreur, le déterminant de la matrice est égal à 0.\n");
        free(entree);
        free((*matrixKey)[0]);
        free((*matrixKey)[1]);
        free((*matrixKey));
        return -3;
    }
    free(entree);
    return 1;
}

void cleanUpHill(FILE* fic1, FILE* fic2, char* chaine1, char* chaine2, char* chaine3, int** matrixKey) {
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
    if (matrixKey != NULL) {
        if (matrixKey[0] != NULL) {
            free(matrixKey[0]);
        }
        if (matrixKey[1] != NULL) {
            free(matrixKey[1]);
        }
        free(matrixKey);
    }
}
