/**
* @file Actions.h
 * @brief Déclare les fonctions utilisées dans le gestionnaire d'absences.
*/
#pragma once
#include "Etudiant.h"

/**
* @brief Vide le tampon d'entrée standard en ignorant tous les caractères dans `stdin` jusqu'à `'\n'` ou `EOF`.
* @note Utile après une lecture avec `fgets` si la ligne est partiellement lue.
*/
void viderBuffer();

/**
* @brief Cette fonction permet l'inscription d'un étudiant.
* @param[in] TabCom Tableau stockant les informations de l'étudiant à inscrire.
* @param[in,out] Tabetu Tableau contenant tous les étudiants.
* @param[in,out] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
*/
void inscription(const char TabCom[][TailleMaxCommande],
                 ETUDIANTS Tabetu[NBEtudiantMax],
                 unsigned int *IDEtudiants);

/**
* @brief Cette fonction permet d'enregistrer l'absence d'un étudiant.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in,out] TabAbs Tableau contenant toutes les absences.
* @param[in,out] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void absence(const char TabCom[][TailleMaxCommande],
             ETUDIANTS Tabetu[NBEtudiantMax],
             unsigned int IDEtudiants,
             ABSENCE TabAbs[NBMaxAbsence],
             unsigned int *IDAbsence);

/**
* @brief Cette fonction permet d'afficher le nombre d'étudiants enregistrés, ainsi que le détail de chaque étudiant avec son identifiant, son nom,
* son groupe et son nombre d'absences dans l'ordre croissant des groupes, puis par ordre alphabétique dans les mêmes groupes.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void affichage_etudiant(const char TabCom[][TailleMaxCommande],
                        ETUDIANTS Tabetu[NBEtudiantMax],
                        unsigned int IDEtudiants,
                        ABSENCE TabAbs[NBMaxAbsence],
                        unsigned int IDAbsence);

/**
* @brief Cette fonction permet de déposer le justificatif d'une absence à une certaine date.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in,out] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
* @param[in] nbcommandes Nombre de commandes contenues dans le tableau des commandes pour pouvoir enregistrer la justification en totalité.
*/
void depos_justf(const char TabCom[][TailleMaxCommande],
                 const ETUDIANTS Tabetu[NBEtudiantMax],
                 ABSENCE TabAbs[NBMaxAbsence],
                 unsigned int IDAbsence,
                 int nbcommandes);

/**
* @brief Cette fonction permet d'afficher les absences ayant été justifiées et étant en attente de validation ou d'invalidation. 
* L'affichage suit l'ordre suivant : identifiant de l'absence, identifiant de l'étudiant correspondant, date de l'absence
* avec le numéro de jour et la demi-journée, et texte de la justification. Le tout est trié par ordre croissant de date.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void validations(const ETUDIANTS Tabetu[NBEtudiantMax],
                 unsigned int IDEtudiants,
                 const ABSENCE TabAbs[NBMaxAbsence],
                 unsigned int IDAbsence);

/**
* @brief Cette fonction permet de valider ou d'invalider l'absence d'un étudiant.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void inv_validation(const char TabCom[][TailleMaxCommande],
                    const ETUDIANTS Tabetu[NBEtudiantMax],
                    unsigned int IDEtudiants,
                    ABSENCE TabAbs[NBMaxAbsence],
                    unsigned int IDAbsence);

/**
* @brief Cette fonction permet d'afficher les absences d'un étudiant, triées par état (en attente de justificatif, en attente de validation, justifiées, non justifiées).
* L'affichage inclut l'identifiant de l'étudiant, son nom, son groupe, son nombre d'absences, et les détails des absences selon leur catégorie 
* (identifiant, date, demi-journée et justificatif si présent). Le tout est trié dans l'ordre croissant des groupes, puis par ordre alphabétique dans les mêmes groupes.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void situ_etudiant(const char TabCom[][TailleMaxCommande],
                   const ETUDIANTS Tabetu[NBEtudiantMax],
                   unsigned int IDEtudiants,
                   const ABSENCE TabAbs[NBMaxAbsence],
                   unsigned int IDAbsence);

/**
* @brief Cette fonction permet d'afficher le nombre d'étudiants défaillants et le détail de ces étudiants avec leur identifiant,
* leur nom, leur groupe et leur nombre total d'absences. Le tout est trié dans l'ordre croissant des groupes, 
* puis par ordre alphabétique dans les mêmes groupes.
* @param[in] TabCom Tableau stockant les informations de l'étudiant concerné.
* @param[in] Tabetu Tableau contenant tous les étudiants.
* @param[in] IDEtudiants Indice des étudiants déjà inscrits et utilisé pour les identifiants.
* @param[in] TabAbs Tableau contenant toutes les absences.
* @param[in] IDAbsence Indice des absences déjà enregistrées et utilisé pour les identifiants.
*/
void defaillant(const char TabCom[][TailleMaxCommande],
                const ETUDIANTS Tabetu[NBEtudiantMax],
                unsigned int IDEtudiants,
                const ABSENCE TabAbs[NBMaxAbsence],
                unsigned int IDAbsence);
