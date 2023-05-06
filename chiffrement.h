

int verifierAlpha(char* chaine);

void convertirAccent(char* chaine);

int isCaractereAccent(char c);

int isAffichableChar(char c);

int isAffichableString(char * ch);

int ouvrirFichierClair(FILE** fic, char** ficPath);

int ouvrirFichierChiffre(FILE** fic, char** ficPath);

int creerFichierChiffre(FILE** fic, char** ficPath);

int creerFichierDechiffre(FILE** fic, char** ficPath);

int entrerChaineEnClair(char** chaine);

int entrerChaineChiffree(char** chaine);

void afficherCheminFicChiffre(char* ficPath);

void afficherCheminFicDechiffre(char* ficPath);

void cleanUp(FILE* fic1, FILE* fic2, char* chaine1, char* chaine2, char* chaine3, char* chaine4);
