#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hachage.h"
int fonction_hachage(char * mot, int taille){
    int h = 7;
    for (int i = 0; i < strlen(mot); i++) {
        h = (h * 31 + mot[i]) % taille;
    }
    return h;
}

hachage_t * creer_hachage(int taille){
    hachage_t * h = malloc(sizeof(hachage_t));
    h->taille = taille;
    h->compteur_id = 0;
    h->table = malloc(sizeof(listeD_t *) * taille);
    for (int i = 0; i < taille; i++) {
        h->table[i] = malloc(sizeof(listeD_t));
        h->table[i]->tete = NULL;
        h->table[i]->queue = NULL;
    }
    return h;
}

void liberer_hachage(hachage_t *h) {
    for (int i = 0; i < h->taille; i++) {
        listeD_t *liste = h->table[i];
        noeud_t *courant = liste->tete;
        while (courant != NULL) {
            noeud_t *suivant = courant->suivant;
            free(courant);
            courant = suivant;
        }
        free(liste);
    }
    free(h->table);
    free(h);
}

int ajouter_noeud(hachage_t * h, char * mot) {
    noeud_t * noeud = rechercher_noeud(h, mot);
    if(noeud != NULL){
        return 0;
    }
    int index = fonction_hachage(mot, h->taille);
    //printf("index : %d \n" , index);
    //on recupere la liste a l'index car
    listeD_t *liste = h->table[index];
    noeud_t *nouveau = malloc(sizeof(noeud_t));
    nouveau->mot = mot;
    nouveau->id = h->compteur_id++;
    //printf("nouveaux id : %d\n" , nouveau->id);
    nouveau->suivant = NULL;
    nouveau->precedent = liste->queue;
    if(liste->tete == NULL){
        liste->tete = nouveau;
        liste->queue = nouveau;
    }else{
        liste->queue->suivant = nouveau;
        nouveau->precedent = liste->queue;
        liste->queue = nouveau;
    }
    return 1;
}


noeud_t *rechercher_noeud(hachage_t *h, char *mot) {
    int index = fonction_hachage(mot, h->taille);
    listeD_t *liste = h->table[index];
    noeud_t *courantDebut = liste->tete;
    noeud_t *courantFin = liste->queue;
    while(courantDebut != NULL && courantFin != NULL && courantDebut != courantFin){
        if(strcmp(courantDebut->mot, mot) == 0){
            return courantDebut;
        }
        if(strcmp(courantFin->mot, mot) == 0){
            return courantFin;
        }
        courantDebut = courantDebut->suivant;
        courantFin = courantFin->precedent;
    }
    return NULL;
}


int est_present(hachage_t * h, char * mot){
    return rechercher_noeud(h, mot) != NULL;
}

int position_noeud(hachage_t * h, char * mot){
    noeud_t * noeud = rechercher_noeud(h, mot);
    if(noeud == NULL){
        return -1;
    }
    return noeud->id;
}

char * mot_id(hachage_t * h, int id){
    int i;
    for (i = 0; i < h->taille; i++) {
        listeD_t * liste = h->table[i];
        if(liste == NULL){
            continue;
        }
        noeud_t * courantDebut = liste->tete;
        noeud_t * courantFin = liste->queue;
        while(courantDebut != NULL && courantFin != NULL && courantDebut->id <= id && courantFin->id >= id){
            if(courantDebut->id == id){
                return courantDebut->mot;
            }
            if(courantFin->id == id){
                return courantFin->mot;
            }
            courantDebut = courantDebut->suivant;
            courantFin = courantFin->precedent;
        }

    }
    return NULL;
}
int id_mot(hachage_t * h, char * mot){
    noeud_t * noeud = rechercher_noeud(h, mot);
    if(noeud == NULL){
        return -1;
    }
    return noeud->id;
}


void afficher_hachage(hachage_t * h) {
    for (int i = 0; i < h->taille; i++) {
        printf("%d : ", i);
        if (h->table[i] != NULL) {
            listeD_t *courant = h->table[i];
            noeud_t *noeud = courant->tete;
            while (noeud != NULL) {
                printf("(%s, %d) -> ", noeud->mot, noeud->id);
                noeud = noeud->suivant;
            }
         }
        printf("NULL\n");
}
}



