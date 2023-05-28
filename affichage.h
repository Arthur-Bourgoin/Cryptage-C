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
*  Nom du fichier : affichage.h                                               *
*                                                                             *
******************************************************************************/

/*
Retourne un nombre entré par l'utilisateur entre 1 et 9, 0 si il y a une erreur
*/
int choixMenu();

/*
Affiche le menu du choix du chiffrement (Cesar, Vigenere ou Hill)
*/
void affichageMenuChiffrement();

/*
Affiche le menu de l'action à réaliser à l'aide du chiffrement sélectionné
*/
void affichageMenuTexte();

/*
Exécute l'action sélectionnée au menu précédent à l'aide du chiffrement de Vigenere
*/
void chiffrementVigenere();

/*
Exécute l'action sélectionnée au menu précédent à l'aide du chiffrement de César
*/
void chiffrementCesar();

/*
Exécute l'action sélectionnée au menu précédent à l'aide du chiffrement de Hill
*/
void chiffrementHill();
