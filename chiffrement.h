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
*  Nom du fichier : chiffrement.h                                             *
*                                                                             *
******************************************************************************/


/*
Renvoie 0 si le caractère n'est pas affichable, 1 sinon
Affichable = 31 < c < 127
*/
int isAffichableChar(char c);

/*
Renvoie 0 si la chaine contient des caractères non affichables, 1 sinon
*/
int isAffichableString(char * ch);

/*
Ouvre en mode lecture le fichier de nom 'ficPath' dans 'fic'
*/
int ouvrirFichierClair(FILE** fic, char** ficPath);

/*
Ouvre en mode lecture le fichier de nom 'ficPath' dans 'fic'
*/
int ouvrirFichierChiffre(FILE** fic, char** ficPath);

/*
Ouvre ou crée en mode écriture le fichier de nom 'ficPath' dans 'fic'
*/
int creerFichierChiffre(FILE** fic, char** ficPath);

/*
Ouvre ou crée en mode écriture le fichier de nom 'ficPath' dans 'fic'
*/
int creerFichierDechiffre(FILE** fic, char** ficPath);

/*
Stock une chaine SANS ACCENT entrée par l'utilisateur dans 'chaine'
Seulement caractères ASCII de 32 à 126 autorisés
*/
int entrerChaineEnClair(char** chaine);

/*
Stock une chaine entrée par l'utilisateur dans 'chaine'
Seulement caractères ASCII de 32 à 126 autorisés
*/
int entrerChaineChiffree(char** chaine);

/*
Affiche le chemin du fichier 'ficPath'
*/
void afficherCheminFicChiffre(char* ficPath);

/*
Affiche le chemin du fichier 'ficPath'
*/
void afficherCheminFicDechiffre(char* ficPath);

/*
Nettoie la mémoire
*/
void cleanUp(FILE* fic1, FILE* fic2, char* chaine1, char* chaine2, char* chaine3, char* chaine4);
