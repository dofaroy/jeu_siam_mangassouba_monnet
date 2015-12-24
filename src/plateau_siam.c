#include "plateau_siam.h"
#include "entree_sortie.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



void plateau_initialiser(plateau_siam* plateau)
{
    // Initialise l'ensemble des cases du plateau a piece_vide
    // sauf les 3 cases du milieu avec un rocher (1,2), (2,2) et (3,2)
    //
    // L'etat de l'echiquier initial est le suivant:
    //
    // [4] *** | *** | *** | *** | *** |
    // [3] *** | *** | *** | *** | *** |
    // [2] *** | RRR | RRR | RRR | *** |
    // [1] *** | *** | *** | *** | *** |
    // [0] *** | *** | *** | *** | *** |
    //     [0]   [1]   [2]   [3]   [4]


    int kx=0;
    for(kx=0 ; kx<NBR_CASES ; ++kx)
    {
        int ky=0;
        for(ky=0 ; ky<NBR_CASES ; ++ky)
        {
            piece_siam* piece=plateau_obtenir_piece(plateau,kx,ky);
            assert(piece!=NULL);

            if(ky==2 && (kx>=1 && kx<=3) )
                piece_definir_rocher(piece);
            else
                piece_definir_case_vide(piece);
        }
    }

    assert(plateau_etre_integre);
}

int plateau_etre_integre(const plateau_siam* plateau)
{
//Algorithme:
//
//Les boucles nous permmettent de parcourir les cases du plateau
//Si la piece est integre on passe à la case suivante
//si le nombre de rocher est inferiereur ou égale a 3
//si le nombre d'animal est inferieur ou egale a 5 et superieur ou egale à zero
//retourne 1
    assert(plateau!=NULL);
    int plateauIntegre=0;
    int kx=0;
    for(kx=0; kx<NBR_CASES; ++kx)
    {
      int ky=0;
      for(ky=0; ky<NBR_CASES; ++ky)
      {
	const piece_siam* piece=plateau_obtenir_piece_info(plateau,kx,ky);
	assert(piece!=NULL);

	  if(piece_etre_integre(piece)==1)
	  {
	    plateauIntegre++;
	  }
      }
    }
    int nbrRocher, nbrElephant, nbrRhinoceros;
    nbrRocher=plateau_denombrer_type(plateau, rocher);
    nbrElephant=plateau_denombrer_type(plateau, elephant);
    nbrRhinoceros=plateau_denombrer_type(plateau, rhinoceros);

    if (plateauIntegre==NBR_CASES*NBR_CASES && nbrRocher<=3 && nbrRocher>=0)
    {
      if(nbrRhinoceros<=5 && nbrRhinoceros>=0 && nbrElephant<=5 && nbrElephant>=0)
      {
	return 1;
      }
    }
    return 0;
}

piece_siam* plateau_obtenir_piece(plateau_siam* plateau,int x,int y)
{
//algorithme
//
//verifie que le plateau n'est pas NULL
//que les coordonnees sont bien valide
//retourne le plateau avec les coordonnees choisie
    assert(plateau!=NULL);
    assert(coordonnees_etre_dans_plateau(x,y)==1);
    return &(plateau->piece[x][y]);
}

const piece_siam* plateau_obtenir_piece_info(const plateau_siam* plateau,int x,int y)
{
//algorithme
//
//verifie que le plateau n'est pas NULL
//que les coordonnees sont bien valide
//retourne le plateau avec les coordonnees de la piece choisie
   assert(plateau!=NULL);
   assert(coordonnees_etre_dans_plateau(x,y)==1);
   return &(plateau->piece[x][y]);
}



int plateau_denombrer_type(const plateau_siam* plateau,type_piece type)
{
    assert(plateau!=NULL);
//Algorithme:
//
//Initialiser compteur<-0
//Pour toutes les cases du tableau
//Si case courante est du type souhaite
//Incremente compteur
//Renvoie compteur
  int compteur=0;
  int kx=0;
  for(kx=0; kx<NBR_CASES; ++kx)
  {
    int ky=0;
    for(ky=0; ky<NBR_CASES; ++ky)
    {
      const piece_siam* piece=plateau_obtenir_piece_info(plateau,kx,ky);
      assert(piece!=NULL);

      if(piece->type==type)
	compteur++;
    }
  }
  return compteur;
}


int plateau_exister_piece(const plateau_siam* plateau,int x,int y)
{
//Algorithme:
//
//Declaration d'un pointeur non modifiable de type piece
//Si Si la piece n'est une case vide
//Renvoie 1
    assert(plateau!=NULL);
    assert(coordonnees_etre_dans_plateau(x,y)==1);
    const piece_siam* piece=plateau_obtenir_piece_info(plateau,x,y);
    assert(piece!=NULL);
    if(piece->type!=case_vide)
    {
      return 1;
    }
    return 0;
}

void plateau_afficher(const plateau_siam* plateau)
{
    assert(plateau!=NULL);

    //utilisation d'une fonction generique d'affichage
    // le parametre stdout permet d'indiquer que l'affichage
    // est realise sur la ligne de commande par defaut.
    entree_sortie_ecrire_plateau_pointeur_fichier(stdout,plateau);

}


void test_plateau_obtenir_piece ()
{
  plateau_siam plateau;
  puts("test_plateau_obtenir_piece");
  int x,y;
  x=3;
  y=1;
   if(plateau_obtenir_piece(&plateau,x,y)==NULL)
    puts("plateau_obtenir_piece KO");
}

