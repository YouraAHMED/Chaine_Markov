
/*
Fichier markov.h
Auteur(s):Ahmed youra */


#ifndef __MARKOV_H__
#define __MARKOV_H__
#include"hachage.h"
// Vous travaillerez ici




/**
 * @brief Structure de donnée pour représenter une chaine de markov
 */

typedef struct markov_s{
    hachage_t  *etats; //Les états de la chaine de markov

    double *tableau_etats; // Le tableau de pointeurs vers les états de la chaine de markov

} markov_t;



/**
 * @brief Crée une chaine de markov
 * @param graine La graine pour le générateur de nombres aléatoires
 * @param taille La taille de la chaine de markov
 * @ensures m->etats->taille == taille
 * @ensures m->etats->tableau != NULL
 * @ensures memset(m->etats->tableau, 0, sizeof(int) * taille * taille)
 * @return La chaine de markov initialisée avec la graine `graine` et de taille `taille`
 */

markov_t *creer_markov(int graine , int taille);


/**
 * @brief Libère la mémoire allouée pour une chaine de markov
 * @param m La chaine de markov à libérer
 * @requires m a été initialisé avec creer_markov
 * @ensures m == NULL
 */

void liberer_markov(markov_t *m);


/**
 * @brief Ajoute un état à la chaine de markov
 * @param m La chaine de markov
 * @param mot Le mot à ajouter
 * @requires m a été initialisé avec creer_markov
 * @requires mot != NULL
 * @requires strlen(mot) > 0
 * @ensures m->etats->taille == m->etats->taille + 1
 * @ensures m->etats->tableau[m->etats->taille - 1] == mot
 */

void ajouter_etat(markov_t *m, char *mot);

/**
  * @brief fixe le poids d'une transition
  * @param m La chaine de markov
  * @param etat1 L'id de l'état de départ
  * @param etat2 L'id de l'état d'arrivée
  * @param poids Le poids de la transition
  * @requires m a été initialisé avec creer_markov
  * @requires etat1 >= 0 && etat1 < m->etats->taille && etat2 >= 0 && etat2 < m->etats->taille
  * @requires poids >= 0
  * @ensures m->etats->tableau[etat1 * m->etats->taille + etat2] == poids
*/
void fixer_poids(markov_t *m,  int etat1, int etat2, double poids);


/**
 * @brief Renvoie le poids d'une transition
 * @param m La chaine de markov
 * @param etat1 L'id de l'état de départ
 * @param etat2 L'id de l'état d'arrivée
 * @requires m a été initialisé avec creer_markov
 * @requires etat1 >= 0 && etat1 < m->etats->taille && etat2 >= 0 && etat2 < m->etats->taille
 * @ensures res >= 0 && res <= 1
 * @return Le poids de la transition
 */
double poids(markov_t *m, int etat1, int etat2);

/**
    * @brief Incrementer le poids d'une transition
    * @param m La chaine de markov
    * @param etat1 L'id de l'état de départ
    * @param etat2 L'id de l'état d'arrivée
    * @requires m a été initialisé avec creer_markov
    * @requires etat1 >= 0 && etat1 < m->etats->taille && etat2 >= 0 && etat2 < m->etats->taille
    * @ensures m->etats->tableau[etat1 * m->etats->taille + etat2] == m->etats->tableau[etat1 * m->etats->taille + etat2] + 1
  */
void incrementer_poids(markov_t *m, int etat1, int etatid2);


/**
 * @brief Renvoie la probabilité de passer d'un état à un autre
 * @param m La chaine de markov
 * @param etat1 L'id de l'état de départ
 * @param etat2 L'id de l'état d'arrivée
 * @requires m a été initialisé avec creer_markov
 * @requires etat1 >= 0 && etat1 < m->etats->taille && etat2 >= 0 && etat2 < m->etats->taille
 * @ensures res >= 0 && res <= 1
 * @return La probabilité de passer de l'état etat1 à l'état etat2
 */

void proba(markov_t *m);
/**
    * @brief Renvoie la probabilité de passer d'un état à un autre
    * @param m La chaine de markov
    * @param etat_initial Le mot de départ
    * @param nb_mots Le nombre de mots à générer
    * @requires m a été initialisé avec creer_markov
    * @requires etat_initial != NULL
    * @requires strlen(etat_initial) > 0
    * @requires nb_mots > 0
    * @ensures res != NULL
    * @return Un tableau de mots générés aléatoirement
    */
char ** marche_aleatoire(markov_t *m, char *etat_initial, int nb_mots);


#endif

