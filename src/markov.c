#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "markov.h"

markov_t *creer_markov(int graine , int taille){
  markov_t *m = malloc(sizeof(markov_t));
  if(m == NULL){
    return NULL;
  }
  srand(graine);
   m->etats = creer_hachage(taille);
   int nbEtats = taille * taille;
    m->tableau_etats = malloc(nbEtats*sizeof(double));
    memset(m->tableau_etats, 0, nbEtats*sizeof(double));
   return m;
}

void liberer_markov(markov_t *m){
  if(m!=NULL){
    if(m->etats!=NULL){
      liberer_hachage(m->etats);
    }
    if(m->tableau_etats!=NULL){
      free(m->tableau_etats);
    }
    free(m);
  }
}

void ajouter_etat(markov_t *m, char *mot){
    if(rechercher_noeud(m->etats, mot)==NULL){
        ajouter_noeud(m->etats, mot);
    }
}

void fixer_poids(markov_t *m, int etat1, int etat2, double poids) {
    if (etat1 >= 0 && etat1 < m->etats->taille && etat2 >= 0 && etat2 < m->etats->taille)
        m->tableau_etats[etat1 * m->etats->taille + etat2] = poids;
    }


double poids(markov_t *m, int etat1, int etat2){
    if(etat1>=0 && etat1<m->etats->taille && etat2>=0 && etat2<m->etats->taille){
        return m->tableau_etats[etat1 * m->etats->taille + etat2];
    }
    return 0;
}

void incrementer_poids(markov_t *m, int etat1, int etat2){
    if(etat1>=0 && etat1<m->etats->taille && etat2>=0 && etat2<m->etats->taille){
        double proba = poids(m, etat1, etat2);
        fixer_poids(m, etat1, etat2, proba + 1);
    }
}

void proba(markov_t *m){
    // Normalisation des probabilités
    for(int i = 0; i < m->etats->compteur_id; i++){
        double somme = 0;
        for(int j = 0; j < m->etats->compteur_id; j++){
            somme += poids(m, i, j);
        }
        for(int j = 0; j < m->etats->compteur_id; j++){
            if(somme != 0){
                fixer_poids(m, i, j, poids(m, i, j) / somme);
            }else{
                fixer_poids(m, i, j, 0);
            }
        }
    }
}

char ** marche_aleatoire(markov_t *m, char *etat_initial, int nb_mots){
    noeud_t *n = rechercher_noeud(m->etats, etat_initial);
    if(n == NULL){
        printf("%s\n", etat_initial);
        return NULL;
    }

    char **tab = malloc((nb_mots+1)*sizeof(char*));
    if(tab == NULL){
        return NULL;
    }

    double *probas = malloc(m->etats->compteur_id * sizeof(double));
    if(probas == NULL){
        return NULL;
    }

    // On fixe la probabilité initiale de chaque état
    memset(probas, 0, m->etats->compteur_id * sizeof(double));
    probas[n->id] = 1;

    double *probas_suivants = malloc(m->etats->compteur_id * sizeof(double));
    printf("Etat initial : %s\n", etat_initial);
    for(int i = 0; i < nb_mots; i++) {
        // On calcule la probabilité de chaque état de suivre l'état initial
        memset(probas_suivants, 0, m->etats->compteur_id * sizeof(double));
        for(int j = 0; j < m->etats->compteur_id; j++){
            for(int k = 0; k < m->etats->compteur_id; k++){
                probas_suivants[j] += probas[k] * poids(m, k, j);
            }
            probas[j] = probas_suivants[j];
        }


        // On choisit un état suivant au hasard
        double r = (double)rand() / (double)RAND_MAX;
        double somme = 0;
        int id_suivant = 0;
        while(somme < r){
            somme += probas_suivants[id_suivant];
            id_suivant = (id_suivant + 1) % m->etats->compteur_id;
        }

        // On ajoute le mot correspondant à l'état suivant
        tab[i] = mot_id(m->etats, id_suivant);

        printf("%s ", tab[i]);
    }
    printf("\n");

    return tab;

}

