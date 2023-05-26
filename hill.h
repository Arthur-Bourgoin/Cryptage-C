
char* chiffrerHill(char* chaine, int** matrixKey);

char* chiffrerCharHill(char c1, char c2, int** matrixKey);

char* dechiffrerHill(char* chaine, int** matrixKey);

char* dechiffrerCharHill(char c1, char c2, int** matrixKey);

char* adapterChaineHill(char* chaine);

int** adapterMatriceMod(int** matrixKey);

int** inverserMatriceMod(int** matrixKey);

int chiffrerFichierHill();

int chiffrerLigneFichierHill(char* chaine, FILE* fic, int cle, int numLigne);

int dechiffrerFichierHill();

int dechiffrerLigneFichierHill(char* chaine, FILE* fic, int cle, int numLigne);

int chiffrerEntreeHill();

int dechiffrerEntreeHill();

int entrerCleHill(int*** matrixKey);