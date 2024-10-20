#include <complex.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const enum {
    NBDemiJourneabsMax = 5,
    NBJourJustifMax = 3,
    TailleNomMax = 31,
    NumJourMax = 40,
    NumJourMin = 0,
    TailleMaxJustif = 51,
    NBEtudiantMax = 100,
    NBMaxCommande = 15,
    NBMaxAbsence = 100,
    TailleDemiJourneeTexte = 2,
    TailleMaxCommande = 100,
};

typedef enum {
    NonJustif = 3,
    Justif = 2,
    EnAttenteJustif = 0,
    EnAttenteTraitement = 1,
} ETAT;

typedef enum { AM, PM } Demijournee;

typedef enum { OK, KO, ENATTENTE } CodeValidation;

typedef struct {
    unsigned int Id;
    unsigned int IdEtudiant;
    unsigned int Date;
    Demijournee DemiJournee[TailleDemiJourneeTexte];
    ETAT Etat;
    char Justif[TailleMaxJustif];
    CodeValidation Justifier;
} ABSENCE;

typedef struct {
    unsigned int Id;
    char Nom[TailleNomMax];
    unsigned int NumGroupe;
    int NBAbsence;
} ETUDIANTS;

void viderBuffer();

void inscription(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], int *IDEtudiants);

void absence(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], ABSENCE TabAbs[NBMaxAbsence],
             const unsigned int IDEtudiants, unsigned int *IDAbsence);

void affichage_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande],
                        const unsigned int IDEtudiants, const ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDAbsence);

int comparer_etu_groupe(const void *etudiantA, const void *etudiantB);

void depos_justf(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence],const unsigned int IDAbsence,
                 const char TabCom[][TailleMaxCommande], const int nbcommandes);

void validations(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDEtudiants,
                 const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);

int comparer_etu(const void *etudiantA, const void *etudiantB);

int comparer_abs_chrono(const void *absA, const void *absB);

void inv_validation(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDEtudiants,
                    const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);

void situ_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence],
                   const unsigned int IDEtudiants,
                   const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);

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
            printf("Sortie du programme.\n");
            return 0;
        } else if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "inscription") == 0) {
            inscription(TabEtudiants, TabCommande, &IDEtudiants);
        } else if (nbcommandes == 4 &&
                   strcmp(TabCommande[0], "absence") == 0) {
            absence(TabEtudiants, TabCommande, TabAbsence, IDEtudiants, &IDAbsence);
        } else if (nbcommandes == 2 &&
                   strcmp(TabCommande[0], "etudiants") == 0) {
            affichage_etudiant(TabEtudiants, TabCommande, IDEtudiants, TabAbsence, IDAbsence);
        } else if ((strcmp(TabCommande[0], "justificatif") == 0)) {
            depos_justf(TabEtudiants, TabAbsence, IDAbsence, TabCommande, nbcommandes);
        } else if ((nbcommandes == 1 &&
                    strcmp(TabCommande[0], "validations") == 0)) {
            validations(TabEtudiants, TabAbsence, IDEtudiants, IDAbsence, TabCommande);
        } else if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "validation") == 0) {
            inv_validation(TabCommande, TabAbsence, IDEtudiants,IDAbsence,TabCommande);
        } else if (nbcommandes == 3 &&
                   strcmp(TabCommande[0], "etudiant") == 0) {
            situ_etudiant(TabEtudiants, TabAbsence,IDEtudiants,IDAbsence, TabCommande);
        }else {
            printf("La commande est incorrect ou n'existe pas.\n");
        }
    }
}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inscription(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], unsigned int *IDEtudiants) {
    if (*IDEtudiants >= NBEtudiantMax) {
        // on verifie qu'on a encore de la place dans le tableau d'etudiants
        printf("Erreur, le nombre maximal d'etudiants a ete atteinds\n");
        return;
    }

    if (atoi(TabCom[2]) > 0) {
        // verification que le numero de groupe est un entier
        for (int i = 0; i < *IDEtudiants; ++i) {
            // verifications qu'il n'y a pas deja un etudiants au meme nom dans le meme groupe
            if (((strcmp(Tabetu[i].Nom, TabCom[1]) == 0) && (Tabetu[i].NumGroupe == atoi(TabCom[2])))) {
                printf("Nom incorrect\n");
                return;
            }
        }
        //enregistrement de l'etudiants
        Tabetu[*IDEtudiants].Id = *IDEtudiants;
        strcpy(Tabetu[*IDEtudiants].Nom, TabCom[1]);
        Tabetu[*IDEtudiants].NumGroupe = atoi(TabCom[2]);
        Tabetu[*IDEtudiants].NBAbsence = 0;
        printf("Inscription enregistree (%u)\n", Tabetu[*IDEtudiants].Id);
        *IDEtudiants = *IDEtudiants + 1;
    } else {
        printf("Groupe incorrect\n");
    }
}

void absence(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], ABSENCE TabAbs[NBMaxAbsence],
             const unsigned int IDEtudiants, unsigned int *IDAbsence) {
    if (atoi(TabCom[1]) <= IDEtudiants && atoi(TabCom[1]) > 0) {
        if (atoi(TabCom[2]) > NumJourMin && atoi(TabCom[2]) <= NumJourMax) {
            // verification que l'absence est comprise dans le semestre
            if (strcmp(TabCom[3], "am") == 0 || strcmp(TabCom[3], "pm") == 0) {
                // verification que la demi journee est correcte
                for (int i = 0; i <= IDEtudiants; ++i) {
                    if (Tabetu[i].Id == atoi(TabCom[1])) {
                        for (int j = 0; j < *IDAbsence; ++j) {
                            // verification que l'absence n'est pas deja connu
                            if ((TabAbs[j].Date == atoi(TabCom[2]) && (strcmp(TabAbs[j].DemiJournee, TabCom[3])) == 0)
                                && (TabAbs[j].IdEtudiant == Tabetu[i].Id)) {
                                printf("absence deja connu\n");
                                return;
                            }
                        }
                        // enregistrement de l'absence
                        Tabetu[i].NBAbsence = Tabetu[i].NBAbsence + 1;
                        TabAbs[*IDAbsence].Id = *IDAbsence;
                        TabAbs[*IDAbsence].IdEtudiant = atoi(TabCom[1]);
                        TabAbs[*IDAbsence].Date = atoi(TabCom[2]);
                        strcpy(TabAbs[*IDAbsence].DemiJournee, TabCom[3]);
                        TabAbs[*IDAbsence].Etat = EnAttenteJustif;
                        TabAbs[*IDAbsence].Justif[0] = '\0';
                        TabAbs[*IDAbsence].Justifier = ENATTENTE;
                        printf("Absence enregistree [%d]\n", TabAbs[*IDAbsence].Id);
                        *IDAbsence = *IDAbsence + 1;
                        return;
                    }
                }
            } else {
                printf("demi-journee incorrecte\n");
            }
        } else {
            printf("Date incorrect\n");
        }
    } else {
        printf("Identifiant incorrect\n");
    }
}

void affichage_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande],
                        const unsigned int IDEtudiants, const ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDAbsence) {
    if (IDEtudiants == 0) {
        // on verifie qu'il y a des etudiants inscrits
        printf("Aucun inscrit\n");
        return;
    } else if (atoi(TabCom[1]) <= NumJourMin || atoi(TabCom[1]) >= NumJourMax) {
        printf("Date incorrecte\n");
        return;
    }

    //trie des etudiants par groupe puis par ordre alphabetique avec qsort dans la bibliotheque standard
    qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu_groupe);
    int date = atoi(TabCom[1]);
    // affichage des etudiants et de leurs nombre d'absences a la date donnee
    for (int i = 0; i < IDEtudiants - 1; i++) {
        int nbabs = 0;
        for (int j = 0; j < IDAbsence; j++) {
            if ((TabAbs[j].IdEtudiant == Tabetu[i].Id) && (TabAbs[j].Date <= date)) {
                nbabs++;
            }
        }
        printf("(%d) %s %d %d\n", Tabetu[i].Id, Tabetu[i].Nom, Tabetu[i].NumGroupe, nbabs);
    }
}

int comparer_etu_groupe(const void *etudiantA, const void *etudiantB) {
    const ETUDIANTS *etuA = (const ETUDIANTS *) etudiantA;
    const ETUDIANTS *etuB = (const ETUDIANTS *) etudiantB;

    // Comparer d'abord les groupes
    if (etuA->NumGroupe < etuB->NumGroupe) {
        return -1;
    } else if (etuA->NumGroupe > etuB->NumGroupe) {
        return 1;
    }

    // Si les groupes sont égaux, comparer les noms (ordre alphabétique)
    return strcmp(etuA->Nom, etuB->Nom);
}

void depos_justf(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence],const unsigned int IDAbsence,
                 const char TabCom[][TailleMaxCommande], const int nbcommandes) {
    if (atoi(TabCom[1]) < IDAbsence && atoi(TabCom[1]) > 0) {
        for (int i = 0; i < IDAbsence; i++) {
            if ((TabAbs[i].Id == atoi(TabCom[1])) && (TabAbs[i].Date < atoi(TabCom[2]))) {
                char justificatif[TailleMaxJustif] = "";
                for (unsigned int k = 3; k < nbcommandes; ++k) {
                    //on vérifie que le justificatif ne dépasse pas la taille maximale d'un justificatif,
                    //et le cas échéant on ajoute chaque argument à partir du troisième à la chaîne justificatif à l'aide de la fonction de concaténation de string.h en les séparant par un espace
                    //(sauf pour le dernier mot qui n'aura pas d'espaces derrière lui)
                    if (strlen(justificatif) + strlen(TabCom[k]) + 1 < TailleMaxJustif) {
                        strcat(justificatif, TabCom[k]);
                        if (k != nbcommandes - 1)
                            strcat(justificatif, " ");
                    }
                }
                if (strlen(justificatif) <= TailleMaxJustif && strlen(justificatif) > 0) {
                    if ((strcmp(justificatif, TabAbs[i].Justif) != 0) && (
                            TabAbs[i].Etat == EnAttenteJustif)) {
                        // enregistrement du justificatifs
                        if (atoi(TabCom[2]) <= TabAbs[i].Date + NBJourJustifMax) {
                            strcpy(TabAbs[i].Justif, justificatif);
                            TabAbs[i].Etat = EnAttenteTraitement;
                        }
                        else {
                            // enregistrement du justificatifs
                            strcpy(TabAbs[i].Justif, justificatif);
                            TabAbs[i].Etat = NonJustif;
                        }
                        printf("Justificatif enregistrer\n");
                        return;
                    } else {
                        printf("Justificatif deja connu\n");
                        return;
                    }
                } else {
                    printf("Justificatif trop long\n");
                    return;
                }
            } else {
                printf("Date incorrecte\n");
                return;
            }
        }
    } else {
        printf("Identifiants incorrecte\n");
    }
}

void validations(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDEtudiants,
                 const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]) {
    qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu);
    // trie la table etudiants de facon croissante d'identificateur
    qsort(TabAbs, IDAbsence, sizeof(ABSENCE), comparer_abs_chrono); // trie la table absence de facon chronologique au dates

    int exist = 0;
    for (int i = 0; i < IDEtudiants; ++i) {
        for (int j = 0; j < IDAbsence; ++j) {
            if (Tabetu[i].Id == TabAbs[j].IdEtudiant // si l'etudiants a une absence en attente de validation
                && (TabAbs[j].Etat == EnAttenteTraitement) && TabAbs[j].Justifier == ENATTENTE) {
                printf("[%u] (%u) %s %u %u/%s (%s)\n", TabAbs[j].Id, Tabetu[i].Id, Tabetu[i].Nom,
                       Tabetu[i].NumGroupe,
                       TabAbs[j].Date, TabAbs[j].DemiJournee, TabAbs[j].Justif);
                exist++;
            }
        }
    }
    if (exist == 0) {
        printf("Aucune validation en attente\n");
    }
}

int comparer_etu(const void *etudiantA, const void *etudiantB) {
    const ETUDIANTS *etuA = (const ETUDIANTS *) etudiantA;
    const ETUDIANTS *etuB = (const ETUDIANTS *) etudiantB;

    // Trie par groupe
    if (etuA->Id < etuB->Id) {
        return -1;
    } else if (etuA->Id > etuB->Id) {
        return 1;
    }
    return 0;
}

int comparer_abs_chrono(const void *absA, const void *absB) {
    const ABSENCE *abscenceA = (const ABSENCE *) absA;
    const ABSENCE *abscenceB = (const ABSENCE *) absB;

    // Trie par date
    if (abscenceA->Date < abscenceB->Date) {
        return -1;
    } else if (abscenceA->Date > abscenceB->Date) {
        return 1;
    }
    return 0;
}

void inv_validation(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDEtudiants,
                    const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]) {
    if (atoi(TabCom[1]) < IDAbsence && atoi(TabCom[1]) > 0) {
        for (int i = 0; i <= IDEtudiants; i++) {
            for (int j = 0; j < IDAbsence; j++) {
                if ((TabAbs[i].Id == TabAbs[j].IdEtudiant) && (TabAbs[j].Id == atoi(TabCom[1]))) {
                    if (TabAbs[j].Etat == EnAttenteTraitement && TabAbs[j].Justifier
                    == ENATTENTE) {
                        if ((strcmp(TabCom[2], "ok") == 0)) {
                            TabAbs[j].Etat == Justif;
                            TabAbs[j].Justifier = OK;
                            printf("Validation enregistree\n");
                        } else if ((strcmp(TabCom[2], "ok") == 0)) {
                            TabAbs[j].Etat == NonJustif;
                            TabAbs[j].Justifier = KO;
                            printf("Validation enregistree\n");
                        } else {
                            printf("Code incorrecte\n");
                        }
                    } else {
                        printf("Validation deja connue\n");
                    }
                }
            }
        }
    } else {
        printf("Identifiants incorrect\n");
    }
}

void situ_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence],
                   const unsigned int IDEtudiants,
                   const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]) {
    if (atoi(TabCom[1]) <= IDAbsence && atoi(TabCom[1]) > 0) {
        if (atoi(TabCom[2]) >= 1 && atoi(TabCom[2]) <= NumJourMax) {
            qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu_groupe);
            qsort(TabAbs, IDAbsence, sizeof(ABSENCE), comparer_abs_chrono);
            // trie la table absence de facon chronologique au dates
            int tabsabs[NonJustif+1][NBMaxAbsence];
            int idetudiants = 0;
            int idabsattjustif = 0;
            int idabsatttrait = 0;
            int idabsjustif = 0;
            int idabsnonjustif = 0;
            for (int i = 0; i <= IDEtudiants; i++) {
                if (atoi(TabCom[1]) == TabAbs[i].Id)
                    idetudiants = i;
            }
            for (int j = 0; j < IDAbsence; j++) {
                if (Tabetu[idetudiants].Id == TabAbs[j].IdEtudiant
                    && TabAbs[j].IdEtudiant == atoi(TabCom[1])) {

                    if (TabAbs[j].Etat == EnAttenteJustif && TabAbs[j].Date + NBMaxAbsence <= atoi(TabCom[2])) {
                        tabsabs[EnAttenteJustif][idabsattjustif] = j;
                        idabsattjustif++;
                    } else if (TabAbs[j].Etat == EnAttenteTraitement) {
                        tabsabs[EnAttenteTraitement][idabsatttrait] = j;
                        idabsatttrait++;
                    } else if (TabAbs[j].Etat == Justif) {
                        tabsabs[Justif][idabsjustif] = j;
                        idabsjustif++;
                    } else if (TabAbs[j].Etat == NonJustif || TabAbs[j].Date + NBMaxAbsence > atoi(TabCom[2])) {
                        tabsabs[NonJustif][idabsnonjustif] = j;
                        idabsnonjustif++;
                    }
                }
            }

            printf("(%u) %s %u %u\n", Tabetu[idetudiants].Id, Tabetu[idetudiants].Nom,
                   Tabetu[idetudiants].NumGroupe,
                   Tabetu[idetudiants].NBAbsence);
            if (idabsattjustif > 0) {
                printf("- En attente justificatif\n");
                for (int i = 0; i <= strlen(tabsabs[EnAttenteJustif]); i++) {
                    printf("[%d] %d/%s\n", TabAbs[tabsabs[EnAttenteJustif][i]].Id,
                           TabAbs[tabsabs[EnAttenteJustif][i]].Date,
                           TabAbs[tabsabs[EnAttenteJustif][i]].DemiJournee);
                }
            }
            if (idabsatttrait > 0) {
                printf("- En attente validation\n");
                for (int i = 0; i <= strlen(tabsabs[EnAttenteTraitement]); i++) {
                    printf("[%d] %d/%s (%s)\n", TabAbs[tabsabs[EnAttenteTraitement][i]].Id,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Date,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].DemiJournee,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Justif);
                }
            }
            if (idabsjustif > 0) {
                printf("- Justifiees\n");
                for (int i = 0; i <= strlen(tabsabs[Justif]); i++) {
                    printf("[%d] %d/%s (%s)\n", TabAbs[tabsabs[EnAttenteTraitement][i]].Id,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Date,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].DemiJournee,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Justif);
                }
            }
            if (idabsnonjustif > 0) {
                printf("- Non-justifiees\n");
                for (int i = 0; i <= strlen(tabsabs[NonJustif]); i++) {
                    if ((TabAbs[tabsabs[NonJustif][i]].Justif == OK) ||
                        (TabAbs[tabsabs[NonJustif][i]].Justif == KO) ) {
                        printf("[%d] %d/%s (%s)\n", TabAbs[tabsabs[EnAttenteTraitement][i]].Id,
                               TabAbs[tabsabs[EnAttenteTraitement][i]].Date,
                               TabAbs[tabsabs[EnAttenteTraitement][i]].DemiJournee,
                               TabAbs[tabsabs[EnAttenteTraitement][i]].Justif);
                    }
                    else {
                        printf("[%d] %d/%s\n", TabAbs[tabsabs[NonJustif][i]].Id,
                            TabAbs[tabsabs[NonJustif][i]].Date,
                            TabAbs[tabsabs[NonJustif][i]].DemiJournee);
                    }
                }
            }
        } else {
            printf("Date incorrecte\n");
        }
    } else {
        printf("Identifiant incorrect\n");
    }
}




//// sp3 j'ai un truc qui est justif qui sort pas justif