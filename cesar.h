
char* chiffrerCesar(char* chaine, int cle);

char chiffrerCharCesar(char c, int cle);

char* dechiffrerCesar(char* chaine, int cle);

char dechiffrerCharCesar(char c, int cle);

int adapterCleCesar(int cle);

/*
0  --> erreur clé de chiffrement
-1 --> erreur ouverture fichier clair
-2 --> erreur ouverture fichier crypté
-3 --> caractères interdits
-4 --> échec malloc chiffrerCesar()
1  --> OK
*/

int chiffrerFichierCesar();

int chiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne);

int dechiffrerFichierCesar();

int dechiffrerLigneFichierCesar(char* chaine, FILE* fic, int cle, int numLigne);

int chiffrerEntreeCesar();

int dechiffrerEntreeCesar();

int entrerCleCesar(char** entreeCle, int* cle);