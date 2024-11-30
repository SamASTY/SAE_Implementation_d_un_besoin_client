#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Etudiant.h"
#include "Actions.h"


int main(void) {
    ETUDIANTS TabEtudiants[NBEtudiantMax]; // initialisation du tableau d'etudiant
    ABSENCE TabAbsence[NBMaxAbsence]; // initialisation du tableau d'etudiant
    unsigned int IDEtudiants = 1;
    unsigned int IDAbsence = 1;
    while (1) {
        // boucle infini jusqu'a ce que la commande saisi sois exit
        //printf("Saisisez votre commande : \n");
        char Commande[TailleMaxCommande]; // stockage de la commande
        if (fgets(Commande, TailleMaxCommande, stdin) != NULL) {
            int taille = strlen(Commande);
            if (taille < 2) {
                // verification que la commande n'est pas vide
                printf("La commande est vide, veuillez reesayer\n");
                viderBuffer();
                continue;
            }
            if (taille == TailleMaxCommande - 1 && Commande[taille - 1] != '\n') {
                // verification que la commande n'est pas trop grande
                printf("La commande est trop longue, veuillez reesayer\n");
                viderBuffer();
                continue;
            }
            if (taille < TailleMaxCommande && Commande[taille - 1] == '\n') {
                //on lit l'entrée et on enleve le retour a la ligne pour que l'entrée devienne une chaine de caractère
                Commande[taille - 1] = '\0';
                taille--;
            }
        } else {
            // la commande ne correspond pas
            printf("Il y a eu une erreur dans la lecture de la commande");
            viderBuffer();
            continue;
        }

        char *detailscommande = strtok(Commande, " ");
        char TabCommande[NBMaxCommande][TailleMaxCommande];
        int nbcommandes = 0;
        while (detailscommande != NULL) {
            strcpy(TabCommande[nbcommandes++], detailscommande);
            detailscommande = strtok(NULL, " ");
        }

        for (int i = 0; TabCommande[0][i]; i++) {
            // met la commande en minuscules
            TabCommande[0][i] = tolower((unsigned char) TabCommande[0][i]);
        }


        if (nbcommandes == 1 &&
            strcmp(TabCommande[0], "exit") == 0) {
            return 0;
        }
        if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "inscription") == 0) {
            inscription(TabCommande, TabEtudiants, &IDEtudiants);

        } else if (nbcommandes == 4 &&
                   strcmp(TabCommande[0], "absence") == 0) {
            absence(TabCommande, TabEtudiants, IDEtudiants, TabAbsence, &IDAbsence);

        } else if (nbcommandes == 2 &&
                   strcmp(TabCommande[0], "etudiants") == 0) {
            affichage_etudiant(TabCommande, TabEtudiants, IDEtudiants, TabAbsence, IDAbsence);

        } else if ((strcmp(TabCommande[0], "justificatif") == 0)) {
            depos_justf(TabCommande, TabEtudiants, TabAbsence, IDAbsence, nbcommandes);

        } else if ((nbcommandes == 1 &&
                    strcmp(TabCommande[0], "validations") == 0)) {
            validations(TabEtudiants, IDEtudiants, TabAbsence, IDAbsence);

        } else if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "validation") == 0) {
            inv_validation(TabCommande, TabEtudiants, IDEtudiants, TabAbsence, IDAbsence);

        } else if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "etudiant") == 0) {
            situ_etudiant(TabCommande, TabEtudiants, IDEtudiants, TabAbsence, IDAbsence);

        } else if (nbcommandes == 2 &&
                   strcmp(TabCommande[0], "defaillants") == 0) {
            defaillant(TabCommande, TabEtudiants, IDEtudiants, TabAbsence, IDAbsence);

        } else {
            printf("La commande est incorrect ou n'existe pas.\n");
        }
    }
}
