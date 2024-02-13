#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>
#include "markov.h"
#include "hachage.h"
/**
Fichier repertoire.h
Auteur(s): Nael TALBIOUI
*/
#ifndef __REPERTOIRE_H__
#define __REPERTOIRE_H__
#define MAX_LINE_LENGTH 1024
#define DT_REG		8

// Vous travaillerez ici


typedef struct iterateur_s{
    FILE* fichier; // pointeur sur le fichier

    char *courant ; // mot courant

    bool fin_phrase; // indique si le mot courant est la fin d'une phrase

    bool existe_prochain; // indique si il existe un prochain mot

    void (*liberer_iterateur)(void* it); // pointeur sur la fonction qui libère la mémoire

    char* (*prochain_mot)(void* it); // pointeur sur la fonction qui retourne le prochain mot

    char* (*mot_courant)(void* it); //pointeur sur la fonction qui retourne le mot courant



} iterateur_t;


/**
 * Fonction qui cree un iterateur
 * @param chemin le chemin du fichier
 * @return l'iterateur cree
 */
iterateur_t* creer_iterateur(char* chemin);

/**
 * Fonction qui divise une chaine de caractere en mots
 * @param chaine la chaine de caractere a diviser
 * @param mot la ou les mots seront stockes
 * @return le nombre de mots
 */

int diviser_mots(char* chaine, char** mot);


/**
 * Fonction qui initialise une chaîne de markov à partir des mots d'un fichier
 * @param chemin Le chemin du repertoire à lire
 * @return La chaine de markov créée
*/
markov_t *initialiser_markov(char* chemin);





#endif
