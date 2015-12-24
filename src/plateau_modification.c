#include "plateau_modification.h"
#include "coordonnees_plateau.h"
#include "type_piece.h"
#include "poussee.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



int plateau_modification_introduire_piece_etre_possible(const plateau_siam* plateau,
                                                        int x,int y,
                                                        type_piece type,
                                                        orientation_deplacement orientation)
{
  /****
  ***algorithme
  *
  *  -verifie qu'on a un platau,qu'il est integre 
  *  -que le type d'animal et l'orientation sont bonnes
  *  -si les coordonées enrées sont ceux du bord du plateau
  *  -et que la case soit vide(condition de poussée non pris en charge)
  *  -alors retourne 1
  *  -
  *  -
  **/
  assert(plateau!=NULL);  
  assert(plateau_etre_integre(plateau)==1);
  assert(orientation_etre_integre_deplacement(orientation)==1);
  assert(type_etre_animal(type)==1);
  if(plateau_denombrer_type(plateau, type)<5)
  {
    if(coordonnees_etre_bordure_plateau(x,y)==1)
    {
      const piece_siam* piece=plateau_obtenir_piece_info(plateau,x,y);
      if(piece->type==case_vide)
      {
	return 1;
      }
    }
  }
  
  return 0;
}


void plateau_modification_introduire_piece(plateau_siam* plateau,
                                           int x,int y,
                                           type_piece type,
                                           orientation_deplacement orientation)
{
  /****
  ***algorithme  int x_memoire, y_memoire;
  x_memoire=x0;
  y_memoire=y0;

  if (direction_deplacement==piece->orientation)
  {
    coordonnees_appliquer_deplacement(&x0,&y0,direction_deplacement);
    if (poussee_etre_valide (plateau,x0,y0,direction_deplacement)==1)
    {
      pousee_realiser (plateau,x0,y0, direction_deplacement); 
      
    }
  }
  
  *
  *  -verifie qu'on a un platau,qu'il est integre 
  *  -verifie que l'introduction d une nouvelle piece est possible
  *  -la piece prend les coordonees, le type et l orientation entree en parametre
  *  -verifie que la piece est bien de type animal
  *  -et que le plateau est a nouveau integre
  **/
  assert(plateau!=NULL);  
  assert(plateau_etre_integre(plateau)==1);
  assert(orientation_etre_integre_deplacement(orientation)==1);
  
  int x_memoire, y_memoire;
  x_memoire=x;
  y_memoire=y;

  if (poussee_etre_valide (plateau,x,y,orientation)==1)
  {
    pousee_realiser (plateau,x,y, orientation); 
  }
  
  assert(plateau_modification_introduire_piece_etre_possible(plateau,x_memoire,y_memoire,type,orientation)==1);
  
  piece_siam* piece=plateau_obtenir_piece(plateau,x_memoire,y_memoire);
  piece->type=type;
  piece->orientation=orientation;
  
  assert(piece_etre_animal(piece)==1);
  assert(plateau_etre_integre(plateau)==1);
}


int plateau_modification_changer_orientation_piece_etre_possible(const plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
  // Verifie si il est possible de changer l'orientation d'une piece sur le plateau
  // Si la piece designee par les coordonnees rentres en parametre est de type animal (elephant ou rhinoceros)
  // Et si la nouvelle orientation choisie est differente de l'ancienne
  // Alors on renvoie 1
  // Sinon on renvoie 0
  
  assert(plateau!=NULL);  
  assert(plateau_etre_integre(plateau)==1);
  assert(coordonnees_etre_dans_plateau(x0,y0)==1);
  assert(orientation_etre_integre(orientation)==1);
  
  const piece_siam* piece=plateau_obtenir_piece_info(plateau,x0,y0);
  assert(piece!=NULL);
  if(piece_etre_animal(piece)==1)
  {
    if (orientation!=piece->orientation)
    {
      return 1;
    }
  }
  return 0;
}



void plateau_modification_changer_orientation_piece(plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
    // Realise la modification de l'orientation d'une piece du jeu en supposant que celle ci soit possible
    // Attribue la nouvelleorientation a la piece
  
    assert(plateau_modification_changer_orientation_piece_etre_possible(plateau,x0,y0,orientation)==1);
    piece_siam* piece=plateau_obtenir_piece(plateau,x0,y0);
    assert(piece_etre_animal(piece)==1);
    
    piece->orientation=orientation;
    
    assert(piece_etre_integre(piece)==1);
    assert(plateau_etre_integre(plateau)==1);
}







int plateau_modification_deplacer_piece_etre_possible(const plateau_siam* plateau,
                                                      int x0,int y0,
                                                      orientation_deplacement direction_deplacement,
                                                      orientation_deplacement orientation)
{
  /****
  ***algorithme
  *
  *  -verifie qu'on a un platau,qu'il est integre 
  *  -verifie que l'orientation et le deplacement sont valide
  *  -si la piece est de type animal
  *  -elle prend les coordonees de la nouvelle case
  *  -si cette case est vide 
  *  -retourne 1
  **/

  assert(plateau!=NULL);  
  assert(plateau_etre_integre(plateau)==1);
  assert(orientation_etre_integre_deplacement(orientation)==1);
  assert(orientation_etre_integre_deplacement(direction_deplacement)==1);
  
  const piece_siam* piece=plateau_obtenir_piece_info(plateau,x0,y0);
  
  if(piece_etre_animal(piece)==1)
  {
    coordonnees_appliquer_deplacement(&x0,&y0,direction_deplacement);
    if(coordonnees_etre_dans_plateau(x0,y0)==0)
    {
      return 1;
    }
    const piece_siam* piece1=plateau_obtenir_piece_info(plateau,x0,y0);
    if(piece1->type==case_vide)
    {
      return 1;
    }
  }
  return 0;
}


void plateau_modification_deplacer_piece(plateau_siam* plateau,
                                         int x0,int y0,
                                         orientation_deplacement direction_deplacement,
                                         orientation_deplacement orientation_final)
{
  /****
  ***algorithme
  *
  *  -verifie qu'on a un platau,qu'il est integre 
  *  -verifie que l'orientation et le deplacement final sont valide
  *  -que la piece est de type animal soit de type animal
  *  -verifie aussi que le deplacement soit possible
  *  -la piece prend ses coodonnees et une nouvelle orientation et est place dans la case suivante
  *  -le case vaccante laisse par le piece
  *  -est initialisee a zero(case vide et aucune orientation)
  *  -verifie que le plateau est de nouveau integre
  **/
  assert(plateau!=NULL);  
  assert(plateau_etre_integre(plateau)==1);
  piece_siam* piece=plateau_obtenir_piece(plateau,x0,y0);
  assert(type_etre_animal(piece->type)==1);
  assert(orientation_etre_integre_deplacement(orientation_final)==1);
  assert(orientation_etre_integre_deplacement(direction_deplacement)==1);
  
  int x_memoire, y_memoire;
  x_memoire=x0;
  y_memoire=y0;

  if (direction_deplacement==piece->orientation)
  {
    coordonnees_appliquer_deplacement(&x0,&y0,direction_deplacement);
    if (poussee_etre_valide (plateau,x0,y0,direction_deplacement)==1)
    {
      pousee_realiser (plateau,x0,y0, direction_deplacement); 
      
    }
  }
  
  
  assert(plateau_modification_deplacer_piece_etre_possible(plateau,x_memoire,y_memoire,direction_deplacement,orientation_final)==1);
  
  coordonnees_appliquer_deplacement(&x_memoire,&y_memoire,direction_deplacement);
  if (coordonnees_etre_dans_plateau(x_memoire,y_memoire)==0)
  {
    direction_deplacement=orientation_inverser(direction_deplacement);
    coordonnees_appliquer_deplacement(&x_memoire,&y_memoire,direction_deplacement);
    piece_siam* piece2=plateau_obtenir_piece(plateau,x_memoire,y_memoire);
    piece_definir_case_vide(piece2);
  } 
    
  else
  {
    piece_siam* piece1=plateau_obtenir_piece(plateau,x_memoire,y_memoire);
    piece1->type=piece->type;
    piece1->orientation=orientation_final;
      
    piece->type=case_vide;
    piece->orientation=aucune_orientation;
  }

    
  assert(plateau_etre_integre(plateau)==1);
 
}














void test_plateau_modification_changer_orientation_piece_etre_possible()
{
  puts("Test jeu_plateau_modification_changer_orientation_piece_etre_possible");
  plateau_siam plateau;
  plateau_initialiser(&plateau);
  plateau.piece[0][0].type=elephant;
  plateau.piece[0][0].orientation=0;
  plateau.piece[1][1].type=rhinoceros;
  plateau.piece[1][1].orientation=0;
  plateau.piece[2][2].type=rocher;
  plateau.piece[2][2].orientation=4;
  plateau.piece[3][3].type=case_vide;
  plateau.piece[3][3].orientation=4;
  
  int k;
  
  for (k=1;k<5;k++)
  {
    if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,0,0,k)!=1)
    {
      puts("elephant: orientation differente KO");
    }
  }
  if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,0,0,0)!=0)
    puts("elephant: meme orientation KO");
  
  for (k=1;k<5;k++)
  {
    if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,1,1,k)!=1)
    {
      puts("rhinoceros: orientation differente KO");
    }
  } 
  if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,1,1,0)!=0)
    puts("rhinoceros: meme orientation KO");
  
  for (k=0;k<5;k++)
  {
    if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,2,2,k)!=0)
    {
      puts("rocher KO");
    }
  }
  
  for (k=0;k<5;k++)
  {
    if (plateau_modification_changer_orientation_piece_etre_possible(&plateau,3,3,k)!=0)
    {
      puts("case_vide KO");
    }
  }
}


void test_plateau_modification_changer_orientation_piece()
{
  puts("Test jeu_plateau_modification_changer_orientation_piece");
  plateau_siam plateau;
  plateau_initialiser(&plateau);
  plateau.piece[0][0].type=elephant;
  plateau.piece[0][0].orientation=0;
  plateau.piece[1][1].type=rhinoceros;
  plateau.piece[1][1].orientation=0;
  
  unsigned int k;
  
  for (k=1;k<4;k++)
  {
    plateau_modification_changer_orientation_piece(&plateau,0,0,k);
    if (plateau.piece[0][0].orientation!=k)
    {
      puts("elephant: orientation differente KO");
    }
  }
  for (k=1;k<4;k++)
  {
    plateau_modification_changer_orientation_piece(&plateau,1,1,k);
    if (plateau.piece[1][1].orientation!=k)
    {
      puts("rhinoceros: orientation differente KO");
    }
  } 
}