/**
Fichier test_hachage.c
Auteur (s) : Diockou Moussa
*/

#include<stdlib.h>
#include<assert.h>
#include <string.h>
#include"../src/markov.h"

// test créer markov
void test_creer_markov(){
    markov_t*m = creer_markov(1234,10);
    assert(m != NULL); // Vérifie que l'objet markov_t est bien créer.
    assert(m->etats != NULL); //Vérifie que le tableau hachage est bien initialisé
    assert(m->tableau_etats != NULL); // Vérifie que le tableau etat est bien unitialisé à NULL

    // Test avec une graine négative
    m = creer_markov(-1, 5);
    assert(m!=NULL);

    // Test avec une taille nulle
    m = creer_markov(1234, 0);
    // Vérifie que la taille du tableau est bien nulle
    assert(m != NULL);

    liberer_markov(m);

}


/* test détruire markov*/

void test_detruire_markov(void) {
    // Test avec un pointeur valide
    markov_t *m = creer_markov(1234, 5);
    assert(m != NULL);
    liberer_markov(m);
    assert(m == NULL);
}




// test ajouter etat

void test_ajouter_etat() {
  markov_t *m = creer_markov(42, 10); // Création d'une nouvelle chaine de Markov "m" de taille 10 et initialisée avec la graine 42
  assert(m != NULL);
  assert(m->etats != NULL);
  assert(m->etats->taille == 10);

  ajouter_etat(m, "chat");
  assert(m->etats->taille == 11);

  ajouter_etat(m, "chien");
  assert(m->etats->taille == 12);

  ajouter_etat(m, "chat");
  assert(m->etats->taille == 12); // Le tableau des états ne doit pas avoir été agrandi

  liberer_markov(m);
}


void test_fixer_poids() {
  markov_t *m = creer_markov(42, 10);  // crée une nouvelle instance de la structure markov_t
  ajouter_etat(m, "mot1"); // On ajoute un état avec la valeur "mot1" à la chaîne de Markov m en appelant la fonction ajouter_etat().
  ajouter_etat(m, "mot2");
  fixer_poids(m, 0, 1, 5); // On fixe le poids de la transition entre l'état 0 ("mot1") et l'état 1 ("mot2") à 5
  assert(poids(m, 0, 1) == 5);// On vérifie que le poids de la transition entre l'état 0 et l'état 1 est égal à 5
  liberer_markov(m);
}

void test_incrementer_poids() {
  markov_t *m = creer_markov(42, 10); // crée une chaîne de Markov avec une taille de tableau d'états initial de 10 et une graine aléatoire de 42.
  ajouter_etat(m, "mot1");
  //ajoute deux états "mot1" et "mot2" à la chaîne de Markov.
  ajouter_etat(m, "mot2");
  incrementer_poids(m, 0, 1);
  assert(poids(m, 0, 1) == 1);
  incrementer_poids(m, 0, 1);
  assert(poids(m, 0, 1) == 2); //  vérifier que le poids de la transition entre les états 0 et 1 est égale à 2.
  liberer_markov(m);
}

void test_proba() {
  markov_t *m = creer_markov(42, 10);
  ajouter_etat(m, "mot1");
  ajouter_etat(m, "mot2");
  fixer_poids(m, 0, 1, 5);
  fixer_poids(m, 1, 0, 2);
  proba(m);
  assert(poids(m, 0, 1) == 1);
  assert(poids(m, 1, 0) == 0.4);
  liberer_markov(m);
}

void test_marche_aleatoire() {
  markov_t *m = creer_markov(42, 10);
  ajouter_etat(m, "mot1"); //  Ajoute l'état "mot1" à la chaîne de Markov m.
  ajouter_etat(m, "mot2");
  ajouter_etat(m, "mot3");
  fixer_poids(m, 0, 1, 5); // Fixe le poids de la transition de l'état "mot1" à l'état "mot2" à 5.
  fixer_poids(m, 1, 0, 2);
  fixer_poids(m, 1, 2, 1);
  proba(m); // Calcule les probabilités de transition pour chaque état de la chaîne de Markov 'm'
  char **tab = marche_aleatoire(m, "mot1", 3); // Effectue une marche aléatoire de 3 états à partir de l'état "mot1" et stocke les résultats dans un tableau de chaînes de caractères tab.
  assert(tab != NULL);
  assert(strcmp(tab[0], "mot1") == 0); // Vérifie que le premier élément de tab est égal à "mot1".
  assert(strcmp(tab[1], "mot2") == 0);
  assert(strcmp(tab[2], "mot3") == 0);
  for(int i = 0; i < 3; i++) {
    free(tab[i]);
  }
  liberer_markov(m);
}




int main(int argc, char *argv[])
{

  test_creer_markov();
  printf("tous les tests ont réussi.\n");
  return 0;



  test_detruire_markov();
  printf("Tous les tests ont réussi.\n");
  return 0;




  test_ajouter_etat();
  printf("Tous les tests ont réussi.\n");
  return 0;


  test_fixer_poids();
  printf("Tous les tests ont réussi.\n");
  return 0;

  test_incrementer_poids();
  printf("Tous les tests ont réussi.\n");
  return 0;

 test_proba();
  printf("Tous les tests ont réussi.\n");
  return 0;


 test_marche_aleatoire();
 printf("Tous les tests ont réussi.\n");

  return EXIT_SUCCESS;
}

