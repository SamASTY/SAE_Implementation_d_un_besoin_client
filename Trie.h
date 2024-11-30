/**
* @file Trie.h
* @brief Déclare les fonctions de tri pour l'utilisation de la fonction qsort.
*/
#pragma once

/**
* @brief Cette fonction renvoie un tri d'une liste d'étudiants selon leur identifiant de façon croissante.
* @param[in] etudiantA Pointeur constant vers le premier étudiant.
* @param[in] etudiantB Pointeur constant vers le second étudiant.
* @return Un entier représentant la relation d'ordre entre les deux étudiants :
* - Retourne -1 si l'identifiant de `etudiantA` est inférieur à celui de `etudiantB`.
* - Retourne 1 si l'identifiant de `etudiantA` est supérieur à celui de `etudiantB`.
*/
int comparer_etu(const void *etudiantA, const void *etudiantB);

/**
* @brief Cette fonction renvoie un tri d'une liste d'absences de façon à ce que les dates soient triées de façon croissante.
* @param[in] absA Pointeur constant vers la première absence.
* @param[in] absB Pointeur constant vers la seconde absence.
* @return Un entier représentant la relation d'ordre entre les deux absences :
* - Retourne -1 si l'absence de `absA` est antérieure à celle de `absB`.
* - Retourne 1 si l'absence de `absA` est postérieure à celle de `absB`.
*/
int comparer_abs_chrono(const void *absA, const void *absB);

/**
* @brief Cette fonction renvoie un tri d'une liste d'étudiants selon leur groupe de façon croissante
* et par ordre alphabétique pour les étudiants du même groupe.
* @param[in] etudiantA Pointeur constant vers le premier étudiant.
* @param[in] etudiantB Pointeur constant vers le second étudiant.
* @return Un entier représentant la relation d'ordre entre les deux étudiants :
* - Retourne -1 si le groupe de `etudiantA` est inférieur à celui de `etudiantB`.
* - Retourne 1 si le groupe de `etudiantA` est supérieur à celui de `etudiantB`.
* - Retourne la valeur de la comparaison (-1, 0 ou 1) des chaînes de caractères des prénoms des deux étudiants s'ils font partie du même groupe.
*/
int comparer_etu_groupe(const void *etudiantA, const void *etudiantB);