#include"repertoire.h"
#include"markov.h"
#include"hachage.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void liberer_iterateur(void * it){
    iterateur_t * iter = (iterateur_t *) it;
    if(iter->courant != NULL){
        free(iter->courant);
    }
    free(iter);
}

char* prochain_mot(void* iter){
    iterateur_t* it = (iterateur_t*) iter;

    char* mot = malloc(sizeof(char)*100);
    int i = 0;
    char c = fgetc(it->fichier); // on lit le premier caractère
    // on saute les caractères qui ne sont pas des lettres
    while(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
        if(c == EOF){
            it->existe_prochain = false;
            return NULL;
        }
        c = fgetc(it->fichier);
    }

    while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        //printf("%c", c);
        mot[i] = c;
        i++;
        c = fgetc(it->fichier);
    }
    //printf("\n");

    mot[i] = '\0';
    it->courant = mot;
    if(c == '.'){
        it->fin_phrase = true;
    }
    return mot;

}

char* mot_courant(void* iter){
    iterateur_t* it = (iterateur_t*) iter;
    printf("mot courant : %s\n", it->courant);
    return it->courant;
}


iterateur_t* creer_iterateur(char* chemin){
    iterateur_t* it = malloc(sizeof(iterateur_t));
    FILE* fichier = fopen(chemin, "r");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    it->fichier = fichier;
    it->courant = NULL;
    it->fin_phrase = false;
    it->existe_prochain = true;
    it->liberer_iterateur = liberer_iterateur;
    it->prochain_mot = prochain_mot;
    it->mot_courant = mot_courant;
    return it;
}

int diviser_mots(char* chaine, char** mot){
    int compte = 0;
    char* mot_courant = strtok(chaine, " ");
    while(mot_courant != NULL){
        mot[compte] = mot_courant;
        compte++;
        mot_courant = strtok(NULL, " ");
    }
    return compte;
}

markov_t *initialiser_markov(char* chemin){
    DIR * dir = opendir(chemin);
        if (!dir) {
            fprintf(stderr, "Error: Cannot open directory '%s'\n", chemin);
            return NULL;
        }

    hachage_t* hachage = creer_hachage(1000);
    markov_t* markov = creer_markov(50 , hachage->taille);

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_REG){
            char chemin_fichier[PATH_MAX];
            snprintf(chemin_fichier,PATH_MAX, "%s/%s", chemin, entry->d_name);
            FILE * fichier = fopen(chemin_fichier, "r");
            if(!fichier){
                fprintf(stderr, "Error: Cannot open file '%s'\n", chemin_fichier);
                continue;
            }
            printf("Lecture du fichier %s: \n", chemin_fichier);
            char line[MAX_LINE_LENGTH];
            char* mot[MAX_LINE_LENGTH];
            int mot_id_precedent = 0;

            while(fgets(line, MAX_LINE_LENGTH, fichier)){
                int nb_mots = diviser_mots(line, mot);
                for(int i = 0; i < nb_mots; i++){
                    int mot_id2 = id_mot(hachage, mot[i]);
                    if(mot_id2 == -1){
                        mot_id2 = ajouter_noeud(hachage, mot[i]);
                    }
                    incrementer_poids(markov, mot_id_precedent , mot_id2);
                    mot_id_precedent = mot_id2;
                }
                mot_id_precedent = 0;
            }
            fclose(fichier);
        }
    }
    closedir(dir);
    proba(markov);
    return markov;
}

