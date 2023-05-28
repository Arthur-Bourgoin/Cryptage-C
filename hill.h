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
*  Nom du fichier : hill.h                                                    *
*                                                                             *
******************************************************************************/

/*
Pour toutes les fonctions, on traitera chaque opération modulo 127 et non 128.
Cela nous permet d'éviter les erreurs liées au fait qu'on ne peut pas inverser la 
matrice modulo 128 si le déterminant n'est pas inversible modulo 128. 
127 étant un nombre premier, ∀ x ∈ ℤ/127ℤ, ∃ y ∈ ℤ/127ℤ tel que x*y = 1 mod 127
Autrement dit n'importe quel entier est inversible modulo 127 (sauf 0).
De plus, 127 étant un caractère non affichable, ce n'est pas embêtant qu'on ne puisse pas l'utiliser.
*/

/*
Retourne la chaine 'chaine' cryptée à l'aide de la matrice clé 'cle'
*/
char* chiffrerHill(char* chaine, int** matrixKey);

/*
Retourne char[2] qui contient les caractères c1 et c2 chiffrés à l'aide de la matrice clé 'cle'
On se sert de cette même fonction pour déchiffrer (avec la matrice inverse)
*/
char* chiffrerCharHill(char c1, char c2, int** matrixKey);

/*
Retourne la chaine 'chaine' décryptée à l'aide de la matrice clé 'cle'
*/
char* dechiffrerHill(char* chaine, int** matrixKey);


/*
Adapte la chaine 'chaine' pour que le nombre de caractères soit pair
Rajoute un espace ' ' en fin de chaine si le nombre de carcatères est impair
*/
char* adapterChaineHill(char* chaine);

/*
Réduit la matrice modulo 127
On supprime les coefficients négatifs en ajoutant 127
*/
int** adapterMatriceMod(int** matrixKey);

/*
Renvoie l'inverse de la matrice 'matrixKey' modulo 127
*/
int** inverserMatriceMod(int** matrixKey);

/*
Chiffre un fichier avec le chiffrement de Hill
0  --> erreur matrice de chiffrement
-1 --> erreur ouverture fichier clair (lecture)
-2 --> erreur ouverture fichier crypté (écriture)
-3 --> echec de la fonction chiffrerHill() ou le fichier contient des caractères interdits
1  --> OK
*/
int chiffrerFichierHill();

/*
Chiffre la chaine 'chaine' et l'ajoute dans le fichier 'fic'
-1 --> La chaine n'est pas affichable
0  --> Echec de la fonction chiffrerHill()
1  --> OK
*/
int chiffrerLigneFichierHill(char* chaine, FILE* fic, int** matrixKey, int numLigne);

/*
Déchiffre un fichier avec le chiffrement de Hill
0  --> erreur matrice de chiffrement
-1 --> erreur ouverture fichier clair (lecture)
-2 --> erreur ouverture fichier crypté (écriture)
-3 --> echec de la fonction dechiffrerHill() ou le fichier contient des caractères interdits
1  --> OK
*/
int dechiffrerFichierHill();

/*
Déchiffre la chaine 'chaine' et l'ajoute dans le fichier 'fic'
-1 --> La chaine n'est pas affichable
0  --> Echec de la fonction dechiffrerHill()
1  --> OK
*/
int dechiffrerLigneFichierHill(char* chaine, FILE* fic, int** matrixKey, int numLigne);

/*
Chiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline() ou chaine non affichable
-1 --> Erreur matrice de chiffrement
0  --> Erreur lors du chiffrement de la chaine, chiffrerHill()
1  --> OK
*/
int chiffrerEntreeHill();

/*
Déchiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline ou chaine non affichable
-1 --> Erreur matrice de chiffrement
0  --> Erreur lors du déchiffrement de la chaine, dechiffrerHill()
1  --> OK
*/
int dechiffrerEntreeHill();

/*
Demande et stocke une clé dans le format du chiffrement de Hill (matrice 2x2)
0  --> Erreur lors de l'allocation de mémoire pour la matrice
-1 --> Erreur getline()
-2 --> Un des carcatères entrés n'est pas valide
-3 --> Le déterminant est égal à 0
1  --> OK
*/
int entrerCleHill(int*** matrixKey);

/*
Nettoie la mémoire
*/
void cleanUpHill(FILE* fic1, FILE* fic2, char* chaine1, char* chaine2, char* chaine3, int** matrixKey);