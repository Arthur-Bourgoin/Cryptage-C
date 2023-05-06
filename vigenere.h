char* chiffrerVigenere(char* chaine, char* cle);

char chiffrerCharVigenere(char c, int cle);

char* dechiffrerVigenere(char* chaine, char* cle);

char dechiffrerCharVigenere(char c, int cle);

char* adapterCleVigenere(int size, char* key);

int chiffrerFichierVigenere();

int chiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne);

int dechiffrerFichierVigenere();

int dechiffrerLigneFichierVigenere(char* chaine, FILE* fic, char* cle, int numLigne);

int chiffrerEntreeVigenere();

int dechiffrerEntreeVigenere();

int entrerCleVigenere(char** cle);
