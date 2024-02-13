/**
Fichier test_hachage.c
Auteur (s) : Diockou Moussa
*/

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include"../src/hachage.h"

void test_fonction_hachage(){
    printf("test_fonction_hachage\n");
    char *chaine = "test";
    int taille = 10;
    int h = fonction_hachage(chaine, taille);
    assert(h >= 0);
    assert(h < taille);
    printf("OK\n");
  }

void test_creer_hachage(){
    printf("test_creer_hachage\n");
    int taille = 10;
    hachage_t *hachage = creer_hachage(taille);
    assert(hachage != NULL);
    assert(hachage->taille == taille);
    assert(hachage->table != NULL);
    assert(hachage->compteur_id == 0);
    for(int i = 0; i < taille; i++){
      assert(hachage->table[i] == NULL);
    }
    printf("OK\n");
  }

void test_liberer_hachage(){
    printf("test_liberer_hachage\n");
    int taille = 10;
    hachage_t *hachage = creer_hachage(taille);
    assert(hachage != NULL);
    assert(hachage->taille == taille);
    assert(hachage->table != NULL);
    assert(hachage->compteur_id == 0);
    for(int i = 0; i < taille; i++){
      assert(hachage->table[i] == NULL);
    }
    liberer_hachage(hachage);
    printf("OK\n");
  }

/*void test_ajouter_noeud(){
    printf("test_ajouter_noeud\n");
    int taille = 10;
    hachage_t *hachage = creer_hachage(taille);
    assert(hachage != NULL);
    assert(hachage->taille == taille);
    assert(hachage->table != NULL);
    assert(hachage->compteur_id == 0);
    for(int i = 0; i < taille; i++){
      assert(hachage->table[i] == NULL);
    }
    char *chaine = "test";
    int id = ajouter_noeud(hachage, chaine);
    assert(id == 1);
    assert(hachage->compteur_id == 1);
    assert(hachage->table[fonction_hachage(chaine, taille)] != NULL);
    assert(hachage->table[fonction_hachage(chaine, taille)]->id == id);
    assert(hachage->table[fonction_hachage(chaine, taille)]->nom != NULL);
    assert(strcmp(hachage->table[fonction_hachage(chaine, taille)]->nom, chaine) == 0);
    printf("OK\n");
  }*/

int main(int argc, char *argv[])
{

  //assert(1);
  return EXIT_SUCCESS;
}



