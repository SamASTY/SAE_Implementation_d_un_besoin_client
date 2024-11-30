#include <complex.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Etudiant.h"
#include "Trie.h"

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inscription(const char TabCom[][TailleMaxCommande],
                 ETUDIANTS Tabetu[NBEtudiantMax],
                 unsigned int *IDEtudiants) {
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

void absence(const char TabCom[][TailleMaxCommande],
             ETUDIANTS Tabetu[NBEtudiantMax],
             unsigned int IDEtudiants,
             ABSENCE TabAbs[NBMaxAbsence],
             unsigned int *IDAbsence) {
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
                                printf("Absence deja connue\n");
                                return;
                            }
                        }
                        // enregistrement de l'absence
                        Tabetu[i].NBAbsence = Tabetu[i].NBAbsence + 1;
                        TabAbs[*IDAbsence].Id = *IDAbsence;
                        TabAbs[*IDAbsence].IdEtudiant = atoi(TabCom[1]);
                        TabAbs[*IDAbsence].Date = atoi(TabCom[2]);
                        TabAbs[*IDAbsence].DateJustif = 0;
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
                printf("Demi-journee incorrecte\n");
            }
        } else {
            printf("Date incorrecte\n");
        }
    } else {
        printf("Identifiant incorrect\n");
    }
}

void affichage_etudiant(const char TabCom[][TailleMaxCommande],
                        ETUDIANTS Tabetu[NBEtudiantMax],
                        unsigned int IDEtudiants,
                        ABSENCE TabAbs[NBMaxAbsence],
                        unsigned int IDAbsence) {
    if (IDEtudiants == 1) {
        // on verifie qu'il y a des etudiants inscrits
        printf("Aucun inscrit\n");
        return;
    } else if (atoi(TabCom[1]) <= NumJourMin) {
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
        printf("(%d) %-8s %3d %d\n", Tabetu[i].Id, Tabetu[i].Nom, Tabetu[i].NumGroupe, nbabs);
    }
}

void depos_justf(const char TabCom[][TailleMaxCommande],
                 const ETUDIANTS Tabetu[NBEtudiantMax],
                 ABSENCE TabAbs[NBMaxAbsence],
                 unsigned int IDAbsence,
                 int nbcommandes) {
    if (atoi(TabCom[1]) < IDAbsence && atoi(TabCom[1]) > 0) {
        for (int i = 0; i <= IDAbsence; i++) {
            if ((TabAbs[i].Id == atoi(TabCom[1])) && (TabAbs[i].Date <= atoi(TabCom[2]))) {
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
                            TabAbs[i].DateJustif = atoi(TabCom[2]);
                            TabAbs[i].Etat = EnAttenteTraitement;
                        } else {
                            // enregistrement du justificatifs
                            strcpy(TabAbs[i].Justif, justificatif);
                            TabAbs[i].DateJustif = atoi(TabCom[2]);
                            TabAbs[i].Etat = NonJustif;
                        }
                        printf("Justificatif enregistre\n");
                        return;
                    } else {
                        printf("Justificatif deja connu\n");
                        return;
                    }
                } else {
                    printf("Justificatif trop long\n");
                    return;
                }
            }
        }
        printf("Date incorrecte\n");
        return;
    } else {
        printf("Identifiant incorrect\n");
    }
}

void validations(const ETUDIANTS Tabetu[NBEtudiantMax],
                 unsigned int IDEtudiants,
                 const ABSENCE TabAbs[NBMaxAbsence],
                 unsigned int IDAbsence) {
    qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu);
    // trie la table etudiants de facon croissante d'identificateur
    qsort(TabAbs, IDAbsence, sizeof(ABSENCE), comparer_abs_chrono);
    // trie la table absence de facon chronologique au dates

    int exist = 0;
    for (int i = 0; i < IDEtudiants; ++i) {
        for (int j = 0; j < IDAbsence; ++j) {
            if (Tabetu[i].Id == TabAbs[j].IdEtudiant // si l'etudiants a une absence en attente de validation
                && (TabAbs[j].Etat == EnAttenteTraitement)
                && TabAbs[j].Justifier == ENATTENTE) {
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


void inv_validation(const char TabCom[][TailleMaxCommande],
                    const ETUDIANTS Tabetu[NBEtudiantMax],
                    unsigned int IDEtudiants,
                    ABSENCE TabAbs[NBMaxAbsence],
                    unsigned int IDAbsence) {
    if (atoi(TabCom[1]) < IDAbsence && atoi(TabCom[1]) > 0) {
        for (int i = 0; i < IDEtudiants; i++) {
            for (int j = 0; j < IDAbsence; j++) {
                if (atoi(TabCom[1]) == TabAbs[j].Id)
                    if ((Tabetu[i].Id == TabAbs[j].IdEtudiant) && (TabAbs[j].Id == atoi(TabCom[1]))) {
                        if (TabAbs[j].Etat == EnAttenteTraitement && TabAbs[j].Justifier
                            == ENATTENTE) {
                            if ((strcmp(TabCom[2], "ok") == 0)) {
                                TabAbs[j].Etat = Justif;
                                TabAbs[j].Justifier = OK;
                                printf("Validation enregistree\n");
                            } else if ((strcmp(TabCom[2], "ko") == 0)) {
                                TabAbs[j].Etat = NonJustif;
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
        printf("Identifiant incorrect\n");
    }
}

void situ_etudiant(const char TabCom[][TailleMaxCommande],
                   const ETUDIANTS Tabetu[NBEtudiantMax],
                   unsigned int IDEtudiants,
                   const ABSENCE TabAbs[NBMaxAbsence],
                   unsigned int IDAbsence) {
    if (atoi(TabCom[1]) < IDEtudiants && atoi(TabCom[1]) > 0) {
        if (atoi(TabCom[2]) >= 1) {
            qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu_groupe);
            qsort(TabAbs, IDAbsence, sizeof(ABSENCE), comparer_abs_chrono);
            // trie la table absence de facon chronologique au dates
            int tabsabs[NonJustif + 1][NBMaxAbsence];
            int idetudiants = 0;
            int idabsattjustif = 0;
            int idabsatttrait = 0;
            int idabsjustif = 0;
            int idabsnonjustif = 0;
            for (int i = 0; i < IDEtudiants; i++) {
                for (int j = 0; j < IDAbsence; j++) {
                    if (TabAbs[j].IdEtudiant == Tabetu[i].Id && Tabetu[i].Id == atoi(TabCom[1]))
                        if (Tabetu[i].Id == TabAbs[j].IdEtudiant
                            && Tabetu[i].Id == atoi(TabCom[1])) {
                            idetudiants = i;
                            if (TabAbs[j].Etat == Justif
                                && TabAbs[j].Justifier == OK
                                && TabAbs[j].DateJustif <= atoi(TabCom[2])
                                && TabAbs[j].DateJustif != 0
                                && TabAbs[j].Date <= atoi(TabCom[2])) {
                                tabsabs[Justif][idabsjustif] = j;
                                idabsjustif++;
                            } else if (TabAbs[j].Etat == EnAttenteTraitement
                                       && TabAbs[j].DateJustif <= atoi(TabCom[2])
                                       && TabAbs[j].DateJustif != 0
                                       && TabAbs[j].Date <= atoi(TabCom[2])) {
                                tabsabs[EnAttenteTraitement][idabsatttrait] = j;
                                idabsatttrait++;
                            } else if (TabAbs[j].Date + NBJourJustifMax >= atoi(TabCom[2])
                                       && (TabAbs[j].DateJustif > atoi(TabCom[2])
                                           || TabAbs[j].DateJustif == 0)
                                       && TabAbs[j].Date <= atoi(TabCom[2])) {
                                tabsabs[EnAttenteJustif][idabsattjustif] = j;
                                idabsattjustif++;
                            } else if ((TabAbs[j].Etat == NonJustif
                                        || TabAbs[j].Date + NBJourJustifMax < atoi(TabCom[2])
                                        || TabAbs[j].Justifier == KO)
                                       && TabAbs[j].Date <= atoi(TabCom[2])) {
                                tabsabs[NonJustif][idabsnonjustif] = j;
                                idabsnonjustif++;
                            }
                        }
                }
            }
            int NbAbs_jour = idabsattjustif + idabsatttrait + idabsjustif + idabsnonjustif;
            printf("(%u) %-12s %3u %u\n", Tabetu[idetudiants].Id, Tabetu[idetudiants].Nom,
                   Tabetu[idetudiants].NumGroupe,
                   NbAbs_jour);
            if (idabsattjustif > 0) {
                printf("- En attente justificatif\n");
                for (int i = 0; i < idabsattjustif; i++) {
                    printf("  [%d] %4d/%s\n", TabAbs[tabsabs[EnAttenteJustif][i]].Id,
                           TabAbs[tabsabs[EnAttenteJustif][i]].Date,
                           TabAbs[tabsabs[EnAttenteJustif][i]].DemiJournee);
                }
            }
            if (idabsatttrait > 0) {
                printf("- En attente validation\n");
                for (int i = 0; i < idabsatttrait; i++) {
                    printf("  [%d] %4d/%s (%s)\n", TabAbs[tabsabs[EnAttenteTraitement][i]].Id,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Date,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].DemiJournee,
                           TabAbs[tabsabs[EnAttenteTraitement][i]].Justif);
                }
            }
            if (idabsjustif > 0) {
                printf("- Justifiees\n");
                for (int i = 0; i < idabsjustif; i++) {
                    printf("  [%d] %4d/%s (%s)\n", TabAbs[tabsabs[Justif][i]].Id,
                           TabAbs[tabsabs[Justif][i]].Date,
                           TabAbs[tabsabs[Justif][i]].DemiJournee,
                           TabAbs[tabsabs[Justif][i]].Justif);
                }
            }
            if (idabsnonjustif > 0) {
                printf("- Non-justifiees\n");
                for (int i = 0; i < idabsnonjustif; i++) {
                    if (TabAbs[tabsabs[NonJustif][i]].DateJustif != 0) {
                        printf("  [%d] %4d/%s (%s)\n", TabAbs[tabsabs[NonJustif][i]].Id,
                               TabAbs[tabsabs[NonJustif][i]].Date,
                               TabAbs[tabsabs[NonJustif][i]].DemiJournee,
                               TabAbs[tabsabs[NonJustif][i]].Justif);
                    } else {
                        printf("  [%d] %4d/%s\n", TabAbs[tabsabs[NonJustif][i]].Id,
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


void defaillant(const char TabCom[][TailleMaxCommande],
                const ETUDIANTS Tabetu[NBEtudiantMax],
                unsigned int IDEtudiants,
                const ABSENCE TabAbs[NBMaxAbsence],
                unsigned int IDAbsence) {
    qsort(Tabetu, IDEtudiants, sizeof(ETUDIANTS), comparer_etu_groupe);
    if (atoi(TabCom[1]) >= 1) {
        unsigned etu_defaillant[NBEtudiantMax], incr_etu_defaillant = 0;
        for (int i = 0; i < IDEtudiants; i++) {
            unsigned nb_abs_non_justif = 0;
            for (int j = 0; j < IDAbsence; j++) {
                if (Tabetu[i].Id == TabAbs[j].IdEtudiant
                    && TabAbs[j].Etat != EnAttenteTraitement
                    && (TabAbs[j].Etat == NonJustif
                        || TabAbs[j].Justifier == KO
                        || TabAbs[j].Justifier == ENATTENTE
                        || TabAbs[j].DateJustif > atoi(TabCom[1]))
                    && TabAbs[j].Date <= atoi(TabCom[1])
                ) {
                    nb_abs_non_justif++;
                }
            }
            if (nb_abs_non_justif >= 5) {
                etu_defaillant[incr_etu_defaillant] = Tabetu[i].Id;
                incr_etu_defaillant++;
            }
        }
        if (incr_etu_defaillant != 0) {
            for (int i = 0; i < IDEtudiants; i++) {
                for (int j = 0; j < incr_etu_defaillant; j++) {
                    if (TabAbs[i].Id == etu_defaillant[j]) {
                        unsigned int nbabs = 0;
                        for (int j = 0; j < IDAbsence; j++) {
                            if ((TabAbs[j].IdEtudiant == Tabetu[i].Id) && (TabAbs[j].Date <= atoi(TabCom[1]))) {
                                nbabs++;
                            }
                        }
                        printf("(%d) %s %d %d\n", Tabetu[i].Id, Tabetu[i].Nom, Tabetu[i].NumGroupe, nbabs);
                    }
                }
            }
        } else {
            printf("Aucun defaillant\n");
        }
    } else {
        printf("Date incorrecte\n");
    }
}