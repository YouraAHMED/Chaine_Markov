
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"src/hachage.h"
#include"src/markov.h"
#include"src/repertoire.h"
#include"src/sauvegarde.h"

int main(int argc, char *argv[])
{
/*  //cree une table de hachage
  hachage_t *h = creer_hachage(10);

  //ajoute un mot a la table de hachage
  //printf("Le hash de %s est %d" , "bonjour", hash("bonjour", 10));
  //printf("Le hash de %s est %d" , "bonne" , hash("bonne", 10));
  ajouter_noeud(h, "bonne nuit");
  ajouter_noeud(h, "bonjour");
  ajouter_noeud(h, "Bonjour");
  ajouter_noeud(h, "bonsoir");
  ajouter_noeud(h, "soir nuit");
  ajouter_noeud(h, "jour nuit");
  ajouter_noeud(h, "car jour");
  ajouter_noeud(h, "donc");
  ajouter_noeud(h, "boot");
  ajouter_noeud(h, "bis");
  ajouter_noeud(h, "saleté");
  ajouter_noeud(h, "find");
  ajouter_noeud(h, "true");
  ajouter_noeud(h, "false");
  ajouter_noeud(h, "if");
  ajouter_noeud(h, "void");
  ajouter_noeud(h, "struct");
  ajouter_noeud(h, "union");
  ajouter_noeud(h, "enum");
  ajouter_noeud(h, "typedef");
  ajouter_noeud(h, "const");
  ajouter_noeud(h, "volatile");

  //affiche la table de hachage
  afficher_hachage(h);

*//*  //cherche une valeur dans la table de hachage
  printf("La valeur de %s est (%s,%d) dans la table de hachage\n" , "bonjour", rechercher_noeud(h, "bonjour")->mot, rechercher_noeud(h, "bonjour")->id);
  //cherche une valeur dans la table de hachage apartir de son identifiant
    printf("La mot de %d est %s dans la table de hachage\n" , 1 , mot_id(h, 1) );
  //printf("La valeur de %s est %f dans la table de hachage\n" , "bonjour", chercher_hachage(h, "bonjour"));
  //trouver un mot dans la table de hachage grace a son identifiant
  printf("Le mot d'identifiant %d est %s \n" , 1 , mot_id(h, 1) );*//*




  //libere la memoire allouee pour la table de hachage
  liberer_hachage(h);
  printf("la table de hachage a ete liberee\n");*/

iterateur_t * it = creer_iterateur("dataset/contes.txt");
markov_t * m = creer_markov(20, 10000);
char * mot ;
int i = 0;
for(mot = it->prochain_mot(it) ; it->existe_prochain; mot = it->prochain_mot(it))
{
  //printf("%s\n", mot);
    ajouter_etat(m, mot);
  i++;
}
it->liberer_iterateur(it);
i = 0;
it = creer_iterateur("dataset/contes.txt");
char * motd = it->prochain_mot(it);
for(mot = it->prochain_mot(it) ; it->existe_prochain; mot = it->prochain_mot(it))
{
  //printf("%s\n", mot);

    incrementer_poids(m, id_mot(m->etats, motd), id_mot(m->etats, mot));

    motd = mot;

  i++;
}

//proba(m);
// Matrice de transition


proba(m);


    printf("marche aleatoire\n");
marche_aleatoire(m, "mort", 10);



/*    //initialisation de la graine
    if(argc == 2)
    {
      srand(atoi(argv[1]));
    }
    else
    {
      srand(time(NULL));
    }*/

    //initialisation de la chaine de markov avec initialiser_markov de repertoire.c
    //markov_t *c = initialiser_markov(argv[1]);

    //generation du texte aleatoire

  printf("C'est tout???\n");
  return EXIT_SUCCESS;
}




