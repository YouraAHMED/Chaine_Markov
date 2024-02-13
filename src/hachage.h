/**
Fichier hachage.h
Auteur(s): Budia Brandon
*/
#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include <stdio.h>


/**
 * @brief Structure de donnée pour représenter un noeud de la table de hachage
 */
typedef struct noeud {
    char * mot; // La clé du noeud
    int id; // L'id du noeud
    struct noeud * suivant; //Le noeud suivant dans la liste chainée
    struct noeud * precedent; //Le noeud précédent dans la liste chainée
} noeud_t;

/**
 * @brief Structure de donnée pour représenter une liste doublement chainée
 */
typedef struct listeD {
    noeud_t * tete; // Le noeud de tête de la liste
    noeud_t * queue; //Le noeud de queue de la liste
} listeD_t;

/**
 * @brief Structure de donnée pour représenter une table de hachage
 */
typedef struct hachage {
    listeD_t ** table; // La table de hachage
    int taille; // La taille de la table de hachage
    int compteur_id; // Le compteur d'id
} hachage_t;

/**
 * @brief Fonction de hachage
 * @param mot La clé à hacher
 * @param taille La taille de la table de hachage
 * @return L'index de la table de hachage où se trouve le noeud
 */
int fonction_hachage(char * mot, int taille);

/**
 * @brief Crée une table de hachage
 * @param taille La taille de la table de hachage
 * @return La table de hachage créée
 */
hachage_t * creer_hachage(int taille);

/**
 * @brief Libère la mémoire allouée pour une table de hachage
 * @param h La table de hachage à libérer
 */
void liberer_hachage(hachage_t * h);

/**
 * @brief Ajoute un noeud à la table de hachage
 * @param h La table de hachage
 * @param mot La clé du noeud à ajouter
 * @return 1 si l'ajout a réussi, 0 sinon
 */
int ajouter_noeud(hachage_t * h, char * mot);


/**
 * @brief Recherche un noeud dans la table de hachage
 * @param h La table de hachage
 * @param mot La clé du noeud à rechercher
 * @return Le noeud trouvé, NULL sinon
 */
noeud_t * rechercher_noeud(hachage_t * h, char * mot);

/**
 * @brief Vérifie si un noeud est présent dans la table de hachage
 * @param h La table de hachage
 * @param mot La clé du noeud à rechercher
 * @return 1 si le noeud est présent, 0 sinon
 */
int est_present(hachage_t * h, char * mot);


/**
 * @brief Retourne la position d'un noeud dans la table de hachage
 * @param h La table de hachage
 * @param mot La clé du noeud à rechercher
 * @return La position du noeud dans la table de hachage, -1 sinon
 */
int position_noeud(hachage_t * h, char * mot);

/**
 * @brief Retourne le mot associé à un id
 * @param h La table de hachage
 * @param id L'id du noeud à rechercher
 * @return Le mot associé à l'id, NULL sinon
 */
char * mot_id(hachage_t * h, int id);


/**
 * @brief Retourne l'id associé à un mot
 * @param h La table de hachage
 * @param mot Le mot du noeud à rechercher
 * @return L'id associé au mot, -1 sinon
 */
int id_mot(hachage_t * h, char * mot);

/**
 * @brief Affiche la table de hachage
 * @param h La table de hachage à afficher
 */
void afficher_hachage(hachage_t * h);
#endif
