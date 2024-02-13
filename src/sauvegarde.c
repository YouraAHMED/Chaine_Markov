#include"sauvegarde.h"


void creerFichier(char* chemin , char* texte){
    FILE *fichier = fopen(chemin, "w");
    if(fichier == NULL){
        printf("Erreur lors de la creation du fichier");
        return;
    }
    fprintf(fichier, "%s", texte);
    fclose(fichier);
}


FILE* ouvrirFichier(char* chemin){
    FILE *fichier = fopen(chemin, "a");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    return fichier;
}

void ecrireFichier(FILE* fichier, char* texte){

    fprintf(fichier, "%s", texte);
}
