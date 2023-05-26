#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chiffrement.h"
#include "hill.h"

char* chiffrerHill(char* chaine, int** matrixKey) {
    char* chaineAdaptee = adapterChaineHill(chaine);
    char* chaineChiffree = malloc(sizeof(char) * (strlen(chaineAdaptee)+1));
    int** validMatrixKey = adapterMatriceMod(matrixKey);
    char* matriceChiffree = NULL;
    for (int i=0; i < strlen(chaineAdaptee); i+= 2) {
        matriceChiffree = chiffrerCharHill(chaineAdaptee[i], chaineAdaptee[i+1], validMatrixKey);
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
    char* matriceChiffree = malloc(2 * sizeof(char));
    char* newMatriceChiffree = malloc(2 * sizeof(char));
    matriceChiffree[0] = (matrixKey[0][0]*c1 + matrixKey[0][1]*c2) % 127;
    matriceChiffree[1] = (matrixKey[1][0]*c1 + matrixKey[1][1]*c2) % 127;
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
    char* chaineAdaptee = adapterChaineHill(chaine);
    char* chaineDechiffree = malloc(sizeof(char) * (strlen(chaineAdaptee)+1));
    int** inverseMatrixKey = inverserMatriceMod(matrixKey);
    char* matriceDechiffree = NULL;
    for (int i=0; i < strlen(chaineAdaptee); i+= 2) {
        matriceDechiffree = chiffrerCharHill(chaineAdaptee[i], chaineAdaptee[i+1], inverseMatrixKey);
        chaineDechiffree[i] = matriceDechiffree[0];
        chaineDechiffree[i+1] = matriceDechiffree[1];
        free(matriceDechiffree);
    }
    chaineDechiffree[strlen(chaineAdaptee)] = '\0';
    if (strlen(chaine) != strlen(chaineAdaptee)) {
        chaineDechiffree[strlen(chaine)] = '\0';
    }
    free(chaineAdaptee);
    free(inverseMatrixKey[0]);
    free(inverseMatrixKey[1]);
    free(inverseMatrixKey);
    return chaineDechiffree;
}

char* dechiffrerCharHill(char c1, char c2, int** matrixKey);

//On adapte la chaine pour que le nombre de caractères soit paire
//On rajoute un espace à la fin si besoin
char* adapterChaineHill(char* chaine) {
    int taille = strlen(chaine);
    if (taille % 2 == 1) {
        taille++;
    }
    char* chaineAdaptee = malloc(sizeof(char) * (taille+1));
    strcpy(chaineAdaptee, chaine);
    if (taille != strlen(chaine)) {
        chaineAdaptee[taille-1]=' ';
        chaineAdaptee[taille]='\0'; 
    }
    return chaineAdaptee;
}

int** adapterMatriceMod(int** matrixKey) {
    int** matriceAdaptee = malloc(2 * sizeof(int*));
    matriceAdaptee[0] = malloc(2 * sizeof(int));
    matriceAdaptee[1] = malloc(2 * sizeof(int));
    matriceAdaptee[0][0] = matrixKey[0][0] % 127;
    if (matriceAdaptee[0][0] < 0) {
        matriceAdaptee[0][0] += 127;
    }
    matriceAdaptee[0][1] = matrixKey[0][1] % 127;
    if (matriceAdaptee[0][1] < 0) {
        matriceAdaptee[0][1] += 127;
    }
    matriceAdaptee[1][0] = matrixKey[1][0] % 127;
    if (matriceAdaptee[1][0] < 0) {
        matriceAdaptee[1][0] += 127;
    }
    matriceAdaptee[1][1] = matrixKey[1][1] % 127;
    if (matriceAdaptee[1][1] < 0) {
        matriceAdaptee[1][1] += 127;
    }
    return matriceAdaptee;
}

int** inverserMatriceMod(int** matrixKey) {
    int** matriceInverse = malloc(sizeof(int*) * 2);
    matriceInverse[0] = malloc(sizeof(int) * 2);
    matriceInverse[1] = malloc(sizeof(int) * 2);
    int** validMatrix = NULL;
    int det = (matrixKey[0][0]*matrixKey[1][1] - matrixKey[0][1]*matrixKey[1][0]) % 127;
    while (det<0) {
        det += 127;
    }
    if (det==0) {
        return NULL;
    }
    for (int i=0; i<127; i++) {
        if (((det*i) % 127) == 1) {
            det = i;
            break;
        }
    }
    matriceInverse[0][0] = (det * matrixKey[1][1]);
    matriceInverse[0][1] = (det * (-1 * matrixKey[0][1] + 127));
    matriceInverse[1][0] = (det * (-1 * matrixKey[1][0] + 127));
    matriceInverse[1][1] = (det * matrixKey[0][0]);
    validMatrix = adapterMatriceMod(matriceInverse);
    free(matriceInverse[0]);
    free(matriceInverse[1]);
    free(matriceInverse);
    return validMatrix;
}

int chiffrerFichierHill() {
    return 1;
}

int chiffrerLigneFichierHill(char* chaine, FILE* fic, int cle, int numLigne){
    return 1;
}

int dechiffrerFichierHill(){
    return 1;
}

int dechiffrerLigneFichierHill(char* chaine, FILE* fic, int cle, int numLigne){
    return 1;
}

int chiffrerEntreeHill(){
    char* chaine          = NULL;
    char* chaineCryptee   = NULL;
    int** matrixKey       = NULL;
    if (entrerChaineEnClair(&chaine) != 1) {
        return -2;
    }
    if (entrerCleHill(&matrixKey) != 1) {
        free(chaine);
        return -1;
    }
    printf("\nChaine en clair : \n%s\n", chaine);
    chaineCryptee = chiffrerHill(chaine, matrixKey);
    if (chaineCryptee == NULL) {
        perror("Echec chiffrement (malloc) ");
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
    if (entrerChaineChiffree(&chaineCryptee) != 1) {
        return -2;
    }
    if (entrerCleHill(&matrixKey) != 1) {
        free(chaineCryptee);
        return -1;
    }
    printf("\nChaine chiffrée : \n%s\n", chaineCryptee);
    chaineDecryptee = dechiffrerHill(chaineCryptee, matrixKey);
    if (chaineDecryptee == NULL) {
        perror("Echec déchiffrement (malloc) ");
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
    *matrixKey = malloc(sizeof(int*) * 2);
    (*matrixKey)[0] = malloc(sizeof(int) * 2);
    (*matrixKey)[1] = malloc(sizeof(int) * 2);
    printf("Entrez une matrice de chiffrement 2x2 : \n\n");
    printf("      [ a   b ]\n");
    printf("      [ c   d ]\n\n");
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            printf("Entrez le caractère M[%d][%d] : ", i, j);
            if (getline(&entree, &taille, stdin) == -1) {
                perror("\nErreur lors de la lecture de la clé");
                free((*matrixKey)[0]);
                free((*matrixKey)[1]);
                free((*matrixKey));
                return -1;
            }
            entree[strlen(entree)-1] = '\0';
            if (((*matrixKey)[i][j] = atoi(entree)) == 0) {
                printf("\nErreur, le caracatère entré n'est pas valide n'est pas valide.\n");
                free((*matrixKey)[0]);
                free((*matrixKey)[1]);
                free((*matrixKey));
                return 0;
            }
        }
    }
    free(entree);
    return 1;
}