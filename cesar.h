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
*  Nom du fichier : cesar.h                                                   *
*                                                                             *
******************************************************************************/

/*
Retourne la chaine 'chaine' cryptée à l'aide de la clé 'cle'
*/
char* chiffrerCesar(char* chaine, int cle);

/*
Retourne le caractère 'c' crypté à l'aide de la clé 'cle'
*/
char chiffrerCharCesar(char c, int cle);

/*
Retourne la chaine 'chaine' décryptée à l'aide de la clé 'cle'
*/
char* dechiffrerCesar(char* chaine, int cle);

/*
Retourne le caractère 'c' décrypté à l'aide de la clé 'cle'
*/
char dechiffrerCharCesar(char c, int cle);

/*
On adapte la clé modulo 128
*/
int adapterCleCesar(int cle);

/*
Chiffre un fichier avec le chiffrement de César
0  --> erreur clé de chiffrement
-1 --> erreur ouverture fichier clair (lecture)
-2 --> erreur ouverture fichier crypté (écriture)
-3 --> caractères interdits dans une ligne du fichier ou échec malloc chiffrerCesar()
1  --> OK
*/
int chiffrerFichierCesar();

/*
Chiffre la chaine 'chaine' et l'ajoute dans le fichier fic
-1 --> La chaine n'est pas affichable
0  --> Echec malloc chiffrerCesar()
1  --> OK
*/
int chiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne);


/*
Déchiffre un fichier avec le chiffrement de César
0  --> erreur clé de chiffrement
-1 --> erreur ouverture fichier chiffré (lecture)
-2 --> erreur ouverture fichier en clair (écriture)
-3 --> caractères interdits dans une ligne du fichier ou échec malloc déchiffrerCesar()
1  --> OK
*/
int dechiffrerFichierCesar();

/*
Déchiffre la chaine 'chaine' et l'ajoute dans le fichier fic
-1 --> La chaine n'est pas affichable
0  --> Echec malloc déchiffrerCesar()
1  --> OK
*/
int dechiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne);

/*
Chiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline ou chaine non affichable
-1 --> Erreur clé de chiffrement
0  --> Echec malloc chiffrerCesar()
1  --> OK
*/
int chiffrerEntreeCesar();

/*
Déchiffre et affiche une chaine entrée au clavier
-2 --> Erreur lors de l'entrée de la chaine, erreur getline ou chaine non affichable
-1 --> Erreur clé de chiffrement
0  --> Echec malloc déchiffrerCesar()
1  --> OK
*/
int dechiffrerEntreeCesar();

/*
Demande et stocke une clé dans le format du chiffrement César
-1 --> Erreur getline()
0  --> Le format de la clé n'est pas valide
1  --> OK
*/
int entrerCleCesar(char** entreeCle, int* cle);