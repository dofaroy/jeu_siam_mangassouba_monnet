#include "jeu_siam.h"
#include "joueur.h"

#include "entree_sortie.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int jeu_etre_integre(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //verification du joueur integre
    const int joueur=jeu->joueur;
    if(joueur_etre_integre(joueur)==0)
        return 0;

    //verification du plateau integre
    const plateau_siam* plateau=&jeu->plateau;
    if(plateau_etre_integre(plateau)==0)
        return 0;

    return 1;
}


void jeu_initialiser(jeu_siam* jeu)
{

    assert(jeu!=NULL);

    //initialise le plateau
    //initialise le joueur

    plateau_initialiser(&jeu->plateau);
    jeu->joueur=0;
}

void jeu_changer_joueur(jeu_siam* jeu)
{
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu));

    joueur_changer(&jeu->joueur);

    assert(jeu_etre_integre(jeu));

}


int jeu_verifier_type_piece_a_modifier(const jeu_siam* jeu,int x,int y)
{
    // Verifie si la piece designee par ses coordonnees correspond a un animal modifiable par le joueur jeu_obtenir_type_animal_courant
    // Renvoie 1 si:
    //		le joueur vaut 0 et l'animal est l'elephant
    //		le joueur vaut 1 et l'animal est le rhinoceros
    // Renvoie 0 sinon
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu)==1);
    assert(coordonnees_etre_dans_plateau(x,y)==1);
    
    const piece_siam* piece=plateau_obtenir_piece_info(&(jeu->plateau),x,y);
    if((jeu->joueur==0 && piece->type==elephant) || (jeu->joueur==1 && piece->type==rhinoceros))
      return 1;
    return 0;
}


void jeu_afficher(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //utilisation d'une fonction generique avec affichage sur
    //  la ligne de commande.
    entree_sortie_ecrire_jeu_pointeur_fichier(stdout,jeu);
}



type_piece jeu_obtenir_type_animal_courant(const jeu_siam* jeu)
{
    // Recupere le type d'animal designe par le joueur jeu_obtenir_type_animal_courant
    // Renvoie un type elephant si le joueur vaut 0
    // Renvoie un type rhinoceros si le joueur vaut 1
  
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu)==1);
    
    if (jeu->joueur==0)
      return elephant;
    
    else
      return rhinoceros;   
}








void test_jeu_verifier_type_piece_a_modifier()
{
  puts("Test jeu_verifier_type_piece_a_modifier");
  jeu_siam jeu0,jeu1;
  jeu_initialiser(&jeu0);
  jeu_initialiser(&jeu1);
  jeu0.joueur=0;
  jeu0.plateau.piece[1][1].type=elephant;
  jeu0.plateau.piece[1][1].orientation=0;
  jeu0.plateau.piece[2][2].type=rhinoceros;
  jeu0.plateau.piece[2][2].orientation=0;
  jeu1.joueur=1;
  jeu1.plateau.piece[1][1].type=elephant;
  jeu1.plateau.piece[1][1].orientation=0;
  jeu1.plateau.piece[2][2].type=rhinoceros;
  jeu1.plateau.piece[2][2].orientation=0;

  int x1, x2;
  x1=1;
  x2=2;

  if (jeu_verifier_type_piece_a_modifier(&jeu0,x1,x1)!=1)
    puts("joueur 0 et elephant KO");
  if (jeu_verifier_type_piece_a_modifier(&jeu0,x2,x2)!=0)
    puts("joueur 0 et rhinoceros KO");
  if (jeu_verifier_type_piece_a_modifier(&jeu1,x1,x1)!=0)
    puts("joueur 1 et elephant KO");
  if (jeu_verifier_type_piece_a_modifier(&jeu1,x2,x2)!=1)
    puts("joueur 1 et rhinoceros KO");
}


void test_jeu_obtenir_type_animal_courant()
{
  puts("Test jeu_obtenir_type_animal_courant");
  jeu_siam jeu0,jeu1;
  jeu_initialiser(&jeu0);
  jeu_initialiser(&jeu1);  
  jeu0.joueur=0;
  jeu1.joueur=1;

  if (jeu_obtenir_type_animal_courant(&jeu0)!=elephant)
    puts("joueur 0 KO");
  if (jeu_obtenir_type_animal_courant(&jeu1)!=rhinoceros)
    puts("joueur 1 KO");
}
