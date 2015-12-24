/**
 * **************************************************
 * **************************************************
 *   _____ _____  ______   _
 *  / ____|  __ \|  ____| | |
 * | |    | |__) | |__    | |    _   _  ___  _ __
 * | |    |  ___/|  __|   | |   | | | |/ _ \| '_ \
 * | |____| |    | |____  | |___| |_| | (_) | | | |
 *  \_____|_|    |______| |______\__, |\___/|_| |_|
 *                                __/ |
 *                               |___/
 * **************************************************
 * **************************************************
 *
 * Role general de ce fichier
 * --------------------------------------------------------------
 * poussee est un fichier permettant de realise une poussee
 *  d'autres pieces lors du deplacement d'un animal
 *
 * Role des fonctions et note d'implementation
 * --------------------------------------------------------------
 * Les fonctions de ce fichier permettent de verifier si une poussee
 *  est possible et de l'effectuer.
 *
 * Notion d'abstraction
 * --------------------------------------------------------------
 * Il s'agit d'un niveau d'abstraction eleve ayant la connaissance
 *  du plateau et des caracteristiques du coup souhaite.
 *
 */


#ifndef POUSSEE_H
#define POUSSEE_H


int poussee_etre_valide_initialisation_piece (const plateau_siam* plateau, int x, int y, orientation_deplacement orientation);

/**
* Fonction poussee_etre_valide:
* *************************
*    Verifie si il est possible de realiser une poussee qui debute
*     aux coordonnees (x,y) dans l'orientation definie.
*    Note: Les coordonnees (x,y) designent la premiere piece rencontree
*     dans la poussee (et non pas les coordonnees de la piece a l'origine
*     de la poussee).
*
*    Necessite:
*     -Un pointeur non NULL vers un plateau integre non modifiable.
*     -Deux coordonnees entieres (x,y) designant une piece non
*       vide integre du plateau.
*     -Une orientation de poussee designant une direction integre.
*    Garantie:
*     -Un retour valant 1 si la poussee est possible.
*     -Un retour valant 0 sinon.
*
*/
int poussee_etre_valide (const plateau_siam* plateau, int x, int y, orientation_deplacement orientation_poussee);


/**
* Fonction poussee_realiser:
* *************************
*    Realise une poussee sur un plateau en supposant que celle-ci
*     est realisable (et non pas les coordonnees de la piece a l'origine
*     de la poussee).
*
*    Necessite:
*     -Un pointeur non NULL vers un plateau integre modifiable.
*     -Deux coordonnees entieres (x,y) designant une piece non
*       vide integre du plateau.
*     -Une orientation de poussee designant une direction integre.
*    Garantie:
*     -Un plateau integre mis a jour en ayant realise la poussee.
*
*/
void pousee_realiser (plateau_siam* plateau, int x, int y, orientation_deplacement orientation_poussee);



#endif
