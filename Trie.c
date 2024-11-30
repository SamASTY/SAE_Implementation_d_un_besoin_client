#include <string.h>
#include "Etudiant.h"

int comparer_etu(const void *etudiantA, const void *etudiantB) {
    const ETUDIANTS *etuA = (const ETUDIANTS *) etudiantA;
    const ETUDIANTS *etuB = (const ETUDIANTS *) etudiantB;

    // Trie par groupe
    if (etuA->Id < etuB->Id) {
        return -1;
    } else if (etuA->Id > etuB->Id) {
        return 1;
    }
}

int comparer_abs_chrono(const void *absA, const void *absB) {
    const ABSENCE *abscenceA = (const ABSENCE *) absA;
    const ABSENCE *abscenceB = (const ABSENCE *) absB;

    // Trie par date
    if (abscenceA->Date < abscenceB->Date) {
        return -1;
    } else if (abscenceA->Date > abscenceB->Date) {
        return 1;
    }else if ((strcmp(abscenceA->DemiJournee,"am")==0
        && strcmp(abscenceB->DemiJournee,"pm")==0)) {
        return -1;
        }
    return 1;
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