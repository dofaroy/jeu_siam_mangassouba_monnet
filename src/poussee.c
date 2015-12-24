#include "condition_victoire_partie.h"
#include "orientation_deplacement.h"
#include "type_piece.h"
#include "plateau_siam.h"
#include "poussee.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int poussee_etre_valide_initialisation_piece (const plateau_siam* plateau, int x, int y, orientation_deplacement orientation)
{
  assert(coordonnees_etre_bordure_plateau(x,y)==1);
  if (x==0 && orientation==droite)
  {
    return 1;
  }
  if (x==NBR_CASES-1 && orientation==gauche)
  {
    return 1;
  }
  if (y==0 && orientation==haut)
  {
    return 1;
  }
  if (y==NBR_CASES-1 && orientation==bas)
  {
    return 1;
  }
  return 0;
}

int poussee_etre_valide (const plateau_siam* plateau, int x, int y, orientation_deplacement orientation_poussee)
{
    // Verifie si la pousse de piece est valide
    // Si la piece devant provoque la pousse est deja sur le plateau
    //    -- Si le joueur veut pousse une piece de son type dans la meme direction que son orientation
    // Si la piece n'est pas encore surle plateau
    //    -- Si le sens de la pousse est autorisee selon le bord par ou est introduit la piece
    //
    //ALORS DANS CHACUN DE CES CAS:
    // Si la balance des forces respecte les bonnes conditions de pousse: 
    //         --> de la piece qui pousse a la premiere case vide rencontre, ou a la sortie du plateau: 
    //                -- on augmente la balance des forces de 1 a chaque animal oriente dans la meme direction, 
    //                -- on diminue la balance des forces de 1 a chaque animal oriente dans la direction oppose, 
    //                -- on regarde le nombre de rocher a pousse,
    //                -- Si le nombre de rocher est superieur ou egal a 1: la balance des forces doit etre superieure ou egale au nombre de rocher.
    //                -- OU Si il n'y a pas de rocher: la balance doit etre superieur a 0
    // ALORS on renvoie 1
    // Sinon on renvoie 0
 
  assert(plateau!=NULL);
  assert(plateau_etre_integre(plateau)==1);
  assert(orientation_etre_integre_deplacement(orientation_poussee)==1);
  const piece_siam* piece = plateau_obtenir_piece_info(plateau,x,y); 
  assert(coordonnees_etre_dans_plateau(x,y)==1);
  if (piece_etre_case_vide(piece)==0)
  {
    int Bilan_Force, nbr_rocher;
    nbr_rocher=0;
    Bilan_Force=1;
    
    if((coordonnees_etre_bordure_plateau(x,y)==1) && (poussee_etre_valide_initialisation_piece (plateau,x,y,orientation_poussee)==0))
    {
      return 0;
    }
    
    
    orientation_deplacement orientation_inverse;
    orientation_inverse=orientation_inverser(orientation_poussee);
    int x_verif, y_verif;
    x_verif=x;
    y_verif=y;
    coordonnees_appliquer_deplacement(&x_verif,&y_verif,orientation_inverse);
      if (orientation_poussee!=plateau->piece[x_verif][y_verif].orientation)
      {
	return 0;
      }
      
      
    puts ("p1");
    while ((coordonnees_etre_dans_plateau(x,y)==1) && (piece_etre_case_vide(&(plateau->piece[x][y]))==0))
    {
      if (piece_etre_rocher(&(plateau->piece[x][y]))==1)
      {
	nbr_rocher++;
	if (Bilan_Force<nbr_rocher)
	{
	  return 0;
	} 
      }
      else
      {
	if (plateau->piece[x][y].orientation==orientation_poussee)
	{
	  Bilan_Force++;
	}
	if (plateau->piece[x][y].orientation==orientation_inverser(orientation_poussee))
	{
	  Bilan_Force--;
	  if (Bilan_Force<=0)
	  {
	    return 0;
	  }
	}
      }
    coordonnees_appliquer_deplacement(&x,&y,orientation_poussee);
    }
    puts ("p2");
    if (nbr_rocher==0 && Bilan_Force>0)
    {
      return 1;
    }
    if (nbr_rocher>=1 && Bilan_Force>=nbr_rocher)
    {
      return 1;
    } 
  }
  
  
  return 0;
}


void pousee_realiser (plateau_siam* plateau, int x, int y,orientation_deplacement orientation_poussee)
{
    // Realise une pousse
    // Si la piece devant provoque la pousse de la piece n'est pas deja sur le plateau:
    //   Si il y a une case vide entre la piece qui provoque la pousse et le bord du plateau:
    //       -- On deplace toutes les pieces situes dans cet intervalle (piece provoquant la poussee comprise) d'une case dans le sens du deplacement
    //   Sinon:
    //       -- On remplace la piece situe au bord du plateau par une case_vide
    //       -- On deplace toutes les pieces situes dans cet intervalle (piece provoquant la poussee comprise) d'une case dans le sens du deplacement
    //
    // Sinon :
    //   Si il y a une case vide entre la piece qui provoque la pousse et le bord du plateau:
    //       -- On deplace toutes les pieces situes dans cet intervalle (piece provoquant la poussee comprise) d'une case dans le sens du deplacement
    //   Sinon:
    //       -- On remplace la piece situe au bord du plateau par une case_vide
    //       -- On deplace toutes les pieces situes dans cet intervalle (peice provoquant la poussee comprise) d'une case dans le sens du deplacement
    //   On met une case_vide a l'ancienne place de la piece ayant provoque la poussee
  
  assert(plateau!=NULL);
  assert(plateau_etre_integre(plateau)==1);
  
  orientation_deplacement orientation_inverse=orientation_inverser(orientation_poussee);
  
  int Poussee_possible, compteur,i,x_memoire,y_memoire;
  Poussee_possible=0;
  compteur=0;
  
  piece_siam* piece = plateau_obtenir_piece(plateau,x,y); 
  if (coordonnees_etre_dans_plateau(x,y)==1)
  {
    if (piece_etre_case_vide(piece)==0)
    {
      Poussee_possible=poussee_etre_valide (plateau,x,y,orientation_poussee);
    }
  }
  
  if(Poussee_possible==1)
  {
    
    while ((coordonnees_etre_dans_plateau(x,y)==1) && (piece_etre_case_vide(&(plateau->piece[x][y]))==0))
    {
      coordonnees_appliquer_deplacement(&x,&y,orientation_poussee);
      if (coordonnees_etre_dans_plateau(x,y)==1)
      {
	piece = plateau_obtenir_piece(plateau,x,y);
      }
      
      compteur++;
    }
    if (coordonnees_etre_dans_plateau(x,y)==0)
    {
      coordonnees_appliquer_deplacement(&x,&y,orientation_inverse);
      piece = plateau_obtenir_piece(plateau,x,y);
      piece_definir_case_vide(piece);
      compteur--;
    }
    
    for (i=0;i<compteur;i++)
    {
      x_memoire=x;
      y_memoire=y;
      coordonnees_appliquer_deplacement(&x,&y,orientation_inverse);
      piece_definir(&(plateau->piece[x_memoire][y_memoire]),plateau->piece[x][y].type,plateau->piece[x][y].orientation);
    }
      piece = plateau_obtenir_piece(plateau,x,y);
      piece_definir_case_vide(piece);
  }

  assert(plateau_etre_integre(plateau)==1);
 
}