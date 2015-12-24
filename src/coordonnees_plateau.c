#include "coordonnees_plateau.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int coordonnees_etre_dans_plateau(int x,int y)
{
    if((x>=0 && x<NBR_CASES) && (y>=0 && y<NBR_CASES))
        return 1;
    return 0;
}

int coordonnees_etre_bordure_plateau(int x,int y)
{
  //x et y varient de l'indice 0 à 4 dans les conditions pour verifier qu'on est bien sur la bordure
  // retourne 1 si les coordonnés correspondent bien aux bordures et 0 sinnon
  if((x==0||x==NBR_CASES-1) && (y<NBR_CASES && y>=0))
    return 1;

  else if ((y==0||y==NBR_CASES-1) && (x<NBR_CASES && x>=0))
    return 1;

  return 0;
}

void coordonnees_appliquer_deplacement(int* x,int* y,orientation_deplacement orientation)
{
    assert(x!=NULL);
    assert(y!=NULL);
    assert(orientation_etre_integre_deplacement(orientation));

    // Table de correspondance:
    //  haut   -> (x,y+1)
    //  bas    -> (x,y-1)
    //  gauche -> (x-1,y)
    //  droite -> (x+1,y)

    switch(orientation)
    {
    case haut:
        *y+=1;
        break;
    case bas:
        *y-=1;
        break;
    case gauche:
        *x-=1;
        break;
    case droite:
        *x+=1;
        break;
    default:
        printf("Probleme fonction %s\n",__FUNCTION__);
    }
}


void test_coordonnees_etre_bordure_plateau()
{
  puts("Test coordonnees_etre_bordure_plateau");
  int x, y;
  x=3;
  y=0;
   if( coordonnees_etre_bordure_plateau(x,y)!=1)
    puts("coordonnees_etre_bordure_plateau KO");
}


