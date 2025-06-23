# Projet académique – Jeu OctoVerso en C
2024 - Projet de première année de BUT informatique en C.

## 🎯 Objectif du projet

Développer une application en **langage C** permettant de **gérer les absences** d’étudiants d’un BUT via un **interpréteur de commandes en ligne de commande**.  
L'application permet :
- L’inscription d’étudiants,
- L’enregistrement d’absences,
- La gestion de justificatifs,
- L’affichage des états d’absences,
- Et la détection des étudiants défaillants.

Le tout dans le respect de **règles de gestion strictes** définies par le cahier des charges
## Prérequis
Utiliser le compilateur gcc ou mscv pour lancer le fichier main.c.

## 💻 Fonctionnalités (commandes disponibles)

L’application comprend **9 commandes principales**, à saisir ligne par ligne dans le terminal. Chaque commande respecte un format strict et permet d’interagir avec le système de gestion d’absences.

### `inscription <nom> <groupe>`
Inscrit un nouvel étudiant.
- 🔹 Exemple : `inscription Lea 101`
- ✅ Réponse attendue : `Inscription enregistree (1)`
- ⚠️ Erreur possible : `Nom incorrect` (si nom déjà existant dans le groupe)

---

### `absence <id_etudiant> <jour> <am|pm>`
Enregistre une absence pour un étudiant inscrit.
- 🔹 Exemple : `absence 1 5 am`
- ✅ Réponse attendue : `Absence enregistree [1]`
- ⚠️ Erreurs possibles : `Identifiant incorrect`, `Date incorrecte`, `Demi-journee incorrecte`, `Absence deja connue`

---

### `etudiants <jour>`
Affiche la liste des étudiants et le nombre d’absences jusqu’à ce jour.
- 🔹 Exemple : `etudiants 10`
- ✅ Résultat : liste triée par groupe puis par nom, avec identifiant, nom, groupe, nombre d’absences
- ⚠️ Erreurs possibles : `Date incorrecte`, `Aucun inscrit`

---

### `justificatif <id_absence> <jour> <texte>`
Dépose un justificatif pour une absence.
- 🔹 Exemple : `justificatif 1 6 j’étais malade`
- ✅ Réponse attendue : `Justificatif enregistre`
- ⚠️ Erreurs possibles : `Identifiant incorrect`, `Date incorrecte`, `Justificatif deja connu`

---

### `validations`
Liste des justificatifs en attente de validation.
- ✅ Réponse attendue : liste avec identifiants des absences et infos associées
- ⚠️ Erreur possible : `Aucune validation en attente`

---

### `validation <id_absence> <ok|ko>`
Permet de valider ou invalider un justificatif.
- 🔹 Exemple : `validation 2 ok`
- ✅ Réponse attendue : `Validation enregistree`
- ⚠️ Erreurs possibles : `Identifiant incorrect`, `Code incorrect`, `Validation deja connue`

---

### `etudiant <id_etudiant> <jour>`
Affiche l’état détaillé d’un étudiant à une date donnée.
- ✅ Réponse attendue : nom, groupe, total d’absences, puis liste triée par type d’absence :
  - En attente justificatif
  - En attente validation
  - Justifiees
  - Non-justifiees
- ⚠️ Erreurs possibles : `Identifiant incorrect`, `Date incorrecte`

---

### `defaillants <jour>`
Liste les étudiants ayant **5 absences non justifiées ou plus**.
- ✅ Résultat : liste similaire à `etudiants`
- ⚠️ Erreurs possibles : `Date incorrecte`, `Aucun defaillant`

---

### `exit`
Commande de fin. Termine proprement l’exécution du programme.
