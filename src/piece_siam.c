#include "piece_siam.h"
#include "orientation_deplacement.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int piece_etre_integre(const piece_siam* piece)
{
  // Verifier si l'orientation donner à une pièce est possible pour cette pièce
  // On utilise un pointeur constant
  // Retourne 1 si ok (animal: haut,bas,gauche ou droite / rocher ou case_vide : aucune_orientation))
  // Retourne 0 sinon
  
  assert(piece!=NULL);
  assert(type_etre_integre(piece->type)==1);
  assert(orientation_etre_integre(piece->orientation)==1);
  if (piece->type==elephant||piece->type==rhinoceros)
  {
    if (piece->orientation>=haut && piece->orientation<=droite)
    {
      return 1;
    }
    return 0;
  }
  else
  {
    if (piece->orientation==aucune_orientation)
    {
      return 1;
    }
    return 0;
  }
}



void piece_initialiser(piece_siam* piece)
{
    assert(piece!=NULL);

    piece_definir(piece,case_vide,aucune_orientation);

    assert(piece_etre_integre(piece));
}


int piece_etre_animal(const piece_siam* piece)
{
  // Verifier si la piece pointe est un animal 
  //Retourner 1 si ok
  // Sinon on retourne 0
  
  assert(piece!=NULL);
  assert(piece_etre_integre(piece)==1);
  if (piece->type==elephant||piece->type==rhinoceros)
    return 1;
  return 0;
}



int piece_etre_rocher(const piece_siam* piece)
{
  // Verifier si la piece pointe est un rocher 
  //Retourner 1 si ok
  // Sinon on retourne 0
  
  assert(piece!=NULL);
  assert(piece_etre_integre(piece)==1);
  if (piece->type==rocher)
    return 1;
  return 0;
  
}


int piece_etre_case_vide(const piece_siam* piece)
{ 
  // Verifier si la piece pointe est une case vide
  //Retourner 1 si ok
  // Sinon on retourne 0
  
  assert(piece!=NULL);
  assert(piece_etre_integre(piece)==1);
  if (piece->type==case_vide)
    return 1;
  return 0;
}


void piece_definir(piece_siam* piece,type_piece type,orientation_deplacement orientation)
{
    // Met a jour le type d'une piece avec le type passe en parametre
    // Met a jour l'orientation d'une piece avec l'orientation passe en parametre
  
    assert(piece!=NULL);
    assert(type_etre_integre(type)==1);
    assert(orientation_etre_integre(orientation)==1);
    
    piece->type=type;
    piece->orientation=orientation;
    assert(piece_etre_integre(piece)==1);
}
  
  
void piece_definir_rocher(piece_siam* piece)
{
    // Met a jour le type et l'orientation d'un rocher
  
    assert(piece!=NULL);
    piece_definir(piece,rocher,aucune_orientation);
    assert(piece_etre_integre(piece));
}

void piece_definir_case_vide(piece_siam* piece)
{
    // Met a jour le type et l'orientation d'une case vide
  
    assert(piece!=NULL);
    piece_definir(piece,case_vide,aucune_orientation);
    assert(piece_etre_integre(piece));
}





orientation_deplacement piece_recuperer_orientation_animal(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece));
    assert(piece_etre_animal(piece));

    return piece->orientation;
}


void piece_afficher(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s,%s",type_nommer(piece->type),orientation_nommer(piece->orientation));
}

void piece_afficher_nom_cours(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s",type_nommer_nom_cours(piece->type));
    if(piece_etre_animal(piece))
        printf("-%s",orientation_nommer_nom_cours(piece->orientation));
}


piece_siam piece_correspondre_nom_cours(const char* nom_cours)
{
    assert(nom_cours!=NULL);
    assert(strlen(nom_cours)==3);

    //Possibilites:
    //
    // - nom vaut "***" -> case vide
    // - nom vaut "RRR" -> rocher
    // - nom commence par "e-" ou "r-"
    //     Alors il s'agit d'un animal.
    //     -> Recuperer le 3eme caractere
    //     -> Le convertir dans l'orientation de l'animal.
    //  - Si aucun des cas precedent, alors affiche erreur.

    piece_siam piece;
    piece_initialiser(&piece);


    if(strncmp(nom_cours,"***",3)==0)
    {
        piece_definir_case_vide(&piece);
    }
    else if(strncmp(nom_cours,"RRR",3)==0)
    {
        piece_definir_rocher(&piece);
    }
    else if((nom_cours[0]=='e' || nom_cours[0]=='r') && nom_cours[1]=='-')
    {
        const type_piece type=type_correspondre_caractere_animal(nom_cours[0]);
        const orientation_deplacement orientation=orientation_correspondre_caractere(nom_cours[2]);

        piece_definir(&piece,type,orientation);
    }
    else
    {
        printf("Erreur fonction %s\n",__FUNCTION__);
        abort();
    }

    return piece;

}


void test_piece_etre_animal()
{
  puts("Test piece_etre_animal");

  piece_siam p1, p2, p3, p4;
  p1.type=elephant;
  p1.orientation=0;
  p2.type=rhinoceros;
  p2.orientation=0;
  p3.type=rocher;
  p3.orientation=4;
  p4.type=case_vide;
  p4.orientation=4;

  if (piece_etre_animal(&p1)!=1)
    puts("elephant KO");
  if (piece_etre_animal(&p2)!=1)
    puts("rhinoceros KO");
  if (piece_etre_animal(&p3)!=0)
    puts("rocher KO");
  if (piece_etre_animal(&p4)!=0)
    puts("case_vide KO");
}

void test_piece_etre_rocher()
{
  puts("Test piece_etre_rocher");

  piece_siam p1, p2, p3, p4;
  p1.type=elephant;
  p1.orientation=0;
  p2.type=rhinoceros;
  p2.orientation=0;
  p3.type=rocher;
  p3.orientation=4;
  p4.type=case_vide;
  p4.orientation=4;


  if (piece_etre_rocher(&p1)!=0)
    puts("elephant KO");
  if (piece_etre_rocher(&p2)!=0)
    puts("rhinoceros KO");
  if (piece_etre_rocher(&p3)!=1)
    puts("rocher KO");
  if (piece_etre_rocher(&p4)!=0)
    puts("case_vide KO");
}

void test_piece_etre_case_vide()
{
  puts("Test piece_etre_case_vide");

  piece_siam p1, p2, p3, p4;
  p1.type=elephant;
  p1.orientation=0;
  p2.type=rhinoceros;
  p2.orientation=0;
  p3.type=rocher;
  p3.orientation=4;
  p4.type=case_vide;
  p4.orientation=4;

  if (piece_etre_case_vide(&p1)!=0)
    puts("elephant KO");
  if (piece_etre_case_vide(&p2)!=0)
    puts("rhinoceros KO");
  if (piece_etre_case_vide(&p3)!=0)
    puts("rocher KO");
  if (piece_etre_case_vide(&p4)!=1)
    puts("case_vide KO");

}
