#include "Etudiant.h"

#pragma once

void viderBuffer();

void inscription(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], int *IDEtudiants);

void absence(ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande], ABSENCE TabAbs[NBMaxAbsence],
             const unsigned int IDEtudiants, unsigned int *IDAbsence);

void affichage_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const char TabCom[][TailleMaxCommande],
                        const unsigned int IDEtudiants, const ABSENCE TabAbs[NBMaxAbsence],
                        const unsigned int IDAbsence);


void depos_justf(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDAbsence,
                 const char TabCom[][TailleMaxCommande], const int nbcommandes);

void validations(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence],
                 const unsigned int IDEtudiants,
                 const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);



void inv_validation(const ETUDIANTS Tabetu[NBEtudiantMax], ABSENCE TabAbs[NBMaxAbsence], const unsigned int IDEtudiants,
                    const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);

void situ_etudiant(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence],
                   const unsigned int IDEtudiants,
                   const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);

void defaillant(const ETUDIANTS Tabetu[NBEtudiantMax], const ABSENCE TabAbs[NBMaxAbsence],
                const unsigned int IDEtudiants,
                const unsigned int IDAbsence, const char TabCom[][TailleMaxCommande]);


void affetu(ETUDIANTS Tabetu[NBEtudiantMax],const unsigned int IDEtudiants);