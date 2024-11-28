#pragma once

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
    unsigned int DateJustif;
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


