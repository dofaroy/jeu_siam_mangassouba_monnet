#include "type_piece.h"
#include <stdio.h>
#include "piece_siam.h"
#include "plateau_siam.h"
#include "mode_interactif.h"
#include "plateau_modification.h"
#include "jeu_siam.h"
#include "joueur.h"
#include "coup_jeu.h"
#include "api_siam.h"
#include "condition_victoire_partie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


void test_lancer()
{
  test_type_etre_animal();
  test_piece_etre_animal();
  test_piece_etre_rocher();
  test_piece_etre_case_vide();
  test_coordonnees_etre_bordure_plateau ();
  test_plateau_obtenir_piece ();
  test_jeu_verifier_type_piece_a_modifier();
  test_jeu_obtenir_type_animal_courant();
  test_plateau_modification_changer_orientation_piece_etre_possible();
  test_plateau_modification_changer_orientation_piece();
}




int main()
{
  test_lancer();
  mode_interactif_lancer();
  
  jeu_siam jeu;
  jeu_initialiser(&jeu);
  

  return 0;
}
