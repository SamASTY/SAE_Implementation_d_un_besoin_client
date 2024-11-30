/**
* @file Etudiant.h
* @brief Déclare les structures des étudiants et des absences.
*/

#pragma once

/**
* @brief Constantes nécessaires au fonctionnement du programme.
*/
const enum {
    NBDemiJourneeAbsMax = 5,
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

/**
* @brief Définition d'un type énumérant les différents états possibles d'une absence.
*/
typedef enum {
    NonJustif = 3,
    Justif = 2,
    EnAttenteJustif = 0,
    EnAttenteTraitement = 1,
} ETAT;

/**
* @brief Définition d'un type pouvant référer à la demi-journée correspondante de l'absence.
*/
typedef enum { AM, PM } Demijournee;

/**
* @brief Définition d'un type énumérant le statut de la validation de la justification de l'absence.
*/
typedef enum { OK, KO, ENATTENTE } CodeValidation;

/**
* @brief Définition d'une structure décrivant une absence et ses caractéristiques.
*/
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

/**
* @brief Définition d'une structure décrivant un étudiant et ses caractéristiques.
*/
typedef struct {
    unsigned int Id;
    char Nom[TailleNomMax];
    unsigned int NumGroupe;
    int NBAbsence;
} ETUDIANTS;
