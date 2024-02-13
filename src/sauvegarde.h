#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Fichier sauvegarde.h
Auteur(s):
*/
#ifndef __SAUVEGARDE_H__
#define __SAUVEGARDE_H__

// Vous travaillerez ici

/**
 * Fonction qui cree un fichier au chemin donne
 * @param chemin le chemin du fichier a creer
*/
void creerFichier(char* chemin , char* texte);

/**
 * Fonction qui ouvre un fichier
 * @param chemin le chemin du fichier a ouvrir
 * @return le fichier ouvert
*/
FILE* ouvrirFichier(char* chemin);

/**
 * Fonction qui ecrit une chaine de caractere dans un fichier
 * @param fichier le fichier dans lequel ecrire
 * @param texte le texte a ecrire
*/
void ecrireFichier(FILE* fichier, char* texte);


#endif

