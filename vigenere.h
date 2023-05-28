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
*  Nom du fichier : vigenere.h                                                *
*                                                                             *
******************************************************************************/

/*
Retourne la chaine 'chaine' cryptée à l'aide de la clé 'cle'
*/
char* chiffrerVigenere(char* chaine, char* cle);

/*
Retourne le caractère 'c' crypté à l'aide de la clé 'cle'
*/
char chiffrerCharVigenere(char c, int cle);

/*
Retourne la chaine 'chaine' décryptée à l'aide de la clé 'cle'
*/
char* dechiffrerVigenere(char* chaine, char* cle);

/*
Retourne le caractère 'c' décrypté à l'aide de la clé 'cle'
*/
char dechiffrerCharVigenere(char c, int cle);

/*
Adapte la taille de la clé pour qu'elle corresponde à 'size'
adapterCleVigenere(5, "key") --> "keyke"
adapterCleVigenere(2, "key") --> "ke"
*/
char* adapterCleVigenere(int size, char* key);

/*
Chiffre un fichier avec le chiffrement de Vigenere
0  --> erreur clé de chiffrement
-1 --> erreur ouverture fichier clair (lecture)
-2 --> erreur ouverture fichier crypté (écriture)
-3 --> caractères interdits dans une ligne du fichier ou échec malloc chiffrerVigenere()
1  --> OK
*/
int chiffrerFichierVigenere();

/*
Chiffre la chaine 'chaine' et l'ajoute dans le fichier fic
-1 --> La chaine n'est pas affichable
0  --> Echec malloc chiffrerVigenere()
1  --> OK
*/
int chiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne);

/*
Déchiffre un fichier avec le chiffrement de Vigenere
0  --> erreur clé de chiffrement
-1 --> erreur ouverture fichier chiffré (lecture)
-2 --> erreur ouverture fichier en clair (écriture)
-3 --> caractères interdits dans une ligne du fichier ou échec malloc déchiffrerVigenere()
1  --> OK
*/
int dechiffrerFichierVigenere();

/*
Déchiffre la chaine 'chaine' et l'ajoute dans le fichier fic
-1 --> La chaine n'est pas affichable
0  --> Echec malloc déchiffrerVigenere()
1  --> OK
*/
int dechiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne);

/*
Chiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline() ou chaine non affichable
-1 --> Erreur clé de chiffrement
0  --> Echec malloc chiffrerVigenere()
1  --> OK
*/
int chiffrerEntreeVigenere();

/*
Déchiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline() ou chaine non affichable
-1 --> Erreur clé de chiffrement
0  --> Echec malloc déchiffrerVigenere()
1  --> OK
*/
int dechiffrerEntreeVigenere();

/*
Demande et stocke une clé dans le format du chiffrement Vigenere
-1 --> Erreur getline()
0  --> La clé contient des caractères non affichables (ASCII de 0 à 31)
1  --> OK
*/
int entrerCleVigenere(char** cle);
