//
// Created by Sebastien on 20/03/2024.
//
#include "../includes/extractFile.h"
#define MAX_LINES 100
#define MAX_LENGTH 100
FILE *fichier;
char nom_fichier[] = "exemple.txt";
char ligne[MAX_LENGTH];
char *tableau[MAX_LINES];
int nb_lignes = 0;

int extractFile(){

    fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    while (fgets(ligne, MAX_LENGTH, fichier) != NULL) {
        // Allouer de la mémoire pour stocker la ligne dans le tableau
        tableau[nb_lignes] = malloc(strlen(ligne) + 1);
        if (tableau[nb_lignes] == NULL) {
            printf("Erreur lors de l'allocation mémoire.\n");
            return 1;
        }
        // Copier la ligne dans le tableau
        strcpy(tableau[nb_lignes], ligne);
        nb_lignes++;
    }
    // Afficher le contenu du tableau
    printf("Contenu du fichier :\n");
    for (int i = 0; i < nb_lignes; i++) {
        printf("%s", tableau[i]);
        // Libérer la mémoire allouée pour chaque ligne
        free(tableau[i]);
    }
}
