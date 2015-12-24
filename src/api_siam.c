#include "api_siam.h"
#include "plateau_modification.h"
#include "coup_jeu.h"
#include "joueur.h"
#include "condition_victoire_partie.h"
#include "coup_jeu.h"
#include "poussee.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

coup_jeu api_siam_tenter_introduire_nouvelle_piece_si_possible(jeu_siam* jeu,
                                                               int x,int y,
                                                               orientation_deplacement orientation)
{
  /****
  ***algorithme
  *
  *  -initialisation de coup_jeu
  *  -si l'orientation n'est pas valide alors le coup n'est pas validé
  *  -Si le coup est valide
  *  -on invalide le coup pour initialisation
  *  -Le type de la piece correspond au joueur courant
  *  -si les conditions d'introduction d une piece est verifiée
  *  -le coup est valide
  *  -La modification est prise en compte sur le plateau
  *  -Le tour est joué et on passe au joueur suivant
  *  -Renvoi le coup
  **/
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu)==1);
    
    coup_jeu coup;
    coup_jeu_initialiser(&coup);
    coup.valide=1;
    if (orientation_etre_integre_deplacement(orientation)!=1)
    {
      printf("L orientation n est pas bonne\n");
      coup.valide=0;
    }
    if (coup.valide==1)
    {
      coup.valide=0;
      type_piece type;
      type=joueur_obtenir_animal(jeu->joueur);
      if((plateau_modification_introduire_piece_etre_possible(&(jeu->plateau),x,y,type,orientation)==1) || (poussee_etre_valide(&(jeu->plateau),x,y,orientation)==1))    
      {
	coup.valide=1;
	plateau_modification_introduire_piece(&(jeu->plateau),x,y,type,orientation);
	coup.condition_victoire.victoire=condition_victoire_etre_victorieux(&(coup.condition_victoire));
	joueur_changer(&(jeu->joueur));
      }
    }    
    return coup;
}



coup_jeu api_siam_tenter_deplacer_piece_si_possible(jeu_siam* jeu,
                                                    int x,int y,
                                                    orientation_deplacement deplacement,
                                                    orientation_deplacement orientation)
{
  /****
  ***algorithme
  *
  *  -initialisation de coup_jeu
  *  -si l'orientation n'est pas valide et si le deplacement n est pas valie alors le coup n'est pas validé
  *  -Si le coup est valide
  *  -on invalide le coup pour initialisation
  *  -Si la piece a deplacer est un animal
  *  -si les conditions de deplacement d une piece est verifiée
  *  -le coup est valide
  *  -La modification est prise en compte sur le plateau
  *  -Le tour est joué et on passe au joueur suivant
  *  -La condition de victoir est mise a jour
  *  -Renvoi le coup
  **/
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu)==1);
    
    coup_jeu coup;
    coup_jeu_initialiser(&coup);
    coup.valide=1;
    
    if (orientation_etre_integre_deplacement(orientation)!=1)
    {
      puts("L orientation n est pas bonne\n");
      coup.valide=0;
    }

    if (orientation_etre_integre_deplacement(deplacement)!=1)
    {
      puts("Le deplacement n est pas bon\n");
      coup.valide=0;
    }

    if (coup.valide==1)
    {
      coup.valide=0;
      const piece_siam* piece=plateau_obtenir_piece_info(&(jeu->plateau),x,y);
      if(type_etre_animal(piece->type)==1)
      {
	if (joueur_etre_type_animal(jeu->joueur,piece->type)==1)
	{
	  int x_verification_poussee_valide, y_verification_poussee_valide;
	  x_verification_poussee_valide=x;
	  y_verification_poussee_valide=y;
	  coordonnees_appliquer_deplacement(&x_verification_poussee_valide,&y_verification_poussee_valide,deplacement);
	  if((plateau_modification_deplacer_piece_etre_possible(&(jeu->plateau),x,y,deplacement,orientation)==1) || ((poussee_etre_valide(&(jeu->plateau),x_verification_poussee_valide,y_verification_poussee_valide,deplacement)==1) && (deplacement==orientation)))    
	  {
	    plateau_modification_deplacer_piece(&(jeu->plateau),x,y,deplacement,orientation);
	    coup.valide=1;
	    coup.condition_victoire.victoire=condition_victoire_etre_victorieux(&(coup.condition_victoire));
	    joueur_changer(&(jeu->joueur));
	  }
	}
      }
    }
    return coup;
}



coup_jeu api_siam_tenter_changer_orientation_piece_si_possible(jeu_siam* jeu,int x,int y,orientation_deplacement orientation)
{
  /****
  ***algorithme
  *
  *  -le coup est invalidé si les coordonées rentrées sont incorrectes et si l'orientation est incorrect
  *  -si le coup est validé
  *  -si la piece choisie et le joueur sont valide
  *  -la condition de modification d'orientation soit verifié
  *  -alors le piece peut changer d'orientation est possible et le coup est validé
  *  -l autre joueur peut jouer a son tour
  *  -retourne coup
  *  -
  *  -
  **/
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu)==1);
    
    coup_jeu coup;    
    coup_jeu_initialiser(&coup);
    coup.valide=1;
    
    if (coordonnees_etre_dans_plateau(x,y)!=1)
    {
      printf("Les coordonnees rentrees ne sont pas bonnes\n");
      coup.valide=0;
    }
    
    if (orientation_etre_integre_deplacement(orientation)!=1)
    {
      printf("L orientation n est pas bonne\n");
      coup.valide=0;
    }
    
    if (coup.valide==1)
    {
      coup.valide=0;
      const piece_siam* piece=plateau_obtenir_piece_info(&(jeu->plateau),x,y);
      if(type_etre_animal(piece->type)==1)
      {
	if (joueur_etre_type_animal(jeu->joueur,piece->type)==1)
	{
	  if(plateau_modification_changer_orientation_piece_etre_possible(&(jeu->plateau),x,y,orientation)==1)
	  {
	    plateau_modification_changer_orientation_piece(&(jeu->plateau),x,y,orientation);
	    coup.valide=1;
	    joueur_changer(&(jeu->joueur));
	  }
	}
      }
    }
    return coup;
}
