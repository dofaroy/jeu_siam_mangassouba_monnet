All : jeu_siam

jeu_siam : jeu_siam.o api_siam.o condition_victoire_partie.o coordonnees_plateau.o coup_jeu.o entree_sortie.o joueur.o main.o mode_interactif.o orientation_deplacement.o parseur_mode_interactif.o piece_siam.o plateau_modification.o plateau_siam.o type_piece.o poussee.o
	gcc -o jeu_siam jeu_siam.o api_siam.o condition_victoire_partie.o coordonnees_plateau.o coup_jeu.o entree_sortie.o joueur.o main.o mode_interactif.o orientation_deplacement.o parseur_mode_interactif.o piece_siam.o plateau_modification.o plateau_siam.o type_piece.o poussee.o
jeu_siam.o : jeu_siam.c jeu_siam.h
	gcc -c jeu_siam.c -Wall -Wextra
api_siam.o : api_siam.c api_siam.h
	gcc -c api_siam.c -Wall -Wextra	
condition_victoire_partie.o : condition_victoire_partie.c condition_victoire_partie.h
	gcc -c condition_victoire_partie.c -Wall -Wextra		
coordonnees_plateau.o : coordonnees_plateau.c coordonnees_plateau.h
	gcc -c coordonnees_plateau.c -Wall -Wextra	
coup_jeu.o : coup_jeu.c coup_jeu.h
	gcc -c coup_jeu.c -Wall -Wextra	
entree_sortie.o : entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c -Wall -Wextra	
joueur.o : joueur.c joueur.h
	gcc -c joueur.c -Wall -Wextra	
main.o : main.c
	gcc -c main.c -Wall -Wextra	
mode_interactif.o : mode_interactif.c mode_interactif.h
	gcc -c mode_interactif.c -Wall -Wextra	
orientation_deplacement.o : orientation_deplacement.c orientation_deplacement.h
	gcc -c orientation_deplacement.c -Wall -Wextra	
parseur_mode_interactif.o : parseur_mode_interactif.c parseur_mode_interactif.h
	gcc -c parseur_mode_interactif.c -Wall -Wextra	
piece_siam.o : piece_siam.c piece_siam.h
	gcc -c piece_siam.c -Wall -Wextra	
plateau_modification.o : plateau_modification.c plateau_modification.h
	gcc -c plateau_modification.c -Wall -Wextra	
plateau_siam.o  : plateau_siam.c plateau_siam.h
	gcc -c plateau_siam.c -Wall -Wextra	
type_piece.o : type_piece.c type_piece.h
	gcc -c type_piece.c -Wall -Wextra	
poussee.o : poussee.c poussee.h
	gcc -c poussee.c -Wall -Wextra	

clean :
	@rm -f *.o *~ jeu_siam 

