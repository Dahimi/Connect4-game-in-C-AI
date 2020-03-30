#include <stdio.h>
#include <stdlib.h>
#define L 6 
#define C 7

	char grille[L][C];
	int i,j;
	int isFree = 0 ;
	char X = 'X', O = 'O' ;
	int isWinner = 0 ;
//  cette fonction teste s'il y a un alignement vertical	
 int verticalement(char a , int j){
  	  	int compteur =0 ;
  	  	int x;
  	  	for(x = 0 ; x < L ; x++){
  	  		if(grille[x][j] ==a)
					compteur++;			
			else    compteur =0 ;
				if(compteur >= 4) return 1;
			}
			 return 0 ;
		}
		
	// cette methode teste s'il y a un alignement horizontal	
  int  horizontalement(char a , int i){
  	  	int compteur =0 ;
  	  	int x;
  	  	for(x = 0 ; x < C ; x++){
  	  		
  	  	  if(grille[i][x] ==a)
				 compteur++;
		 else    compteur =0 ;
		 if(compteur >= 4) return 1;
			}
		 return 0 ;
		}	


  // cette methode teste s'il y a un alignement inclin� dans le sens  "/"
  
    int incline1(char a , int i , int j){
    	// on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j-1,i-1) 
    	// l'equation est y = x + i - j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    	// alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    	int compteur =0 ;
  	  	int x;
  	  	int y ;
  	  	for(x = 0 ;( x < C && x + i -j < L); x++ ){ 
			y  = x + i-j ;	
  	  	  if(grille[y][x] ==a)
				 compteur++;
		 else    compteur =0 ;
		 if(compteur >= 4) return 1;
			}
		 return 0 ;
	}
	
	  // cette methode teste s'il y a un alignement inclin� dans le sens "\"
	  
	 int incline2(char a , int i , int j){
	 	// on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j+1,i-1) 
    	// l'equation est y = -x + i + j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    	// alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    	int compteur =0 ;
  	  	int x;
  	  	int y ;
  	  	for(x = 0 ;( x < C && -x + i +j < L); x++ ){ 
  	  	 y  = -x + i +j ;
			if (y >= 0){
			
  	  	  if(grille[y][x] ==a)
			{
					 compteur++;		 						 
				 }
		 else    compteur =0 ;
		 if(compteur >= 4) return 1;
			}}
    	return 0;
	} 


	// cette methode (fonction) test s'il y a une vainqueur 
  int isThere_Winner(char a , int i , int j){
  	// pour ce faire on realise le test dans les quatres directions
  	if(verticalement(a,j) ==1) return 1;
  	if(horizontalement(a,i) == 1) return 1;
  	if (incline1(a,i,j) == 1) return 1;
  	if (incline2(a,i,j) == 1) return 1;
  	return 0;	
  }
  
  
 //  On teste si la grille est pleine 
 int grillePleine(){
 	int j = 0;
 	for( j = 0 ; j < C ; j++ ){
 
 		if(grille[0][j] ==' ') return 0;
	 }
	 return 1 ;
 }	
 
 
  // affichage de la grille 
 void affichage(){
 		printf("\n");
	for(i=0;i<L;i++){
		printf("\t");
		for(j=0;j<C;j++){
		printf("|%c",grille[i][j]);
			
		}
		printf("|\n");
	}
	printf("\t 1 2 3 4 5 6 7 \n");
 }
 
 
 
 void demandeAuJoueur(char a){
 	isFree = 0;
 		printf("joueur %c entrez le numero de la colonne \n",a);
	scanf("%d",&j);
	j--;
	if(j>=0 && j<C){
		i= L-1;
		while(isFree == 0 && i >= 0 ){
			
			if(grille[i][j]==' ')			
			isFree = 1;			
			else
			i--;
		}
		
	}
	if( isFree == 0) {
		printf("Ce coup n'est pas valide !!! \n");
	   demandeAuJoueur(a);
	}
	else 	
	grille[i][j]= a ;
	// voir si ce joueur est un winner 
	if(isThere_Winner(a,i,j) == 1) {
		isWinner = 1 ;
	printf(" \n 	Le	 joueur %c 	a	 gagn� 	!	!	! \n",a);
	
}
  }
  
   
  
  
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{
			if(grille[i][j] != X  && grille[i][j] != O){			
		grille[i][j]=' ';}
		}
	}
	printf("\n");
	printf("joueur1 : X \n");
	printf("joueur2 : O \n");
	affichage();
	
	while(grillePleine() == 0 ) { // la boucle se r�p�te tant que la grille est pleine
	
	demandeAuJoueur(X);	
	affichage();
	// si le joureur X  a gagn� on arrete le jeu 
	if(isWinner == 1) return;
	demandeAuJoueur(O);
	affichage();
	// si le joureur O  a gagn� on arrete le jeu 
	if(isWinner == 1) return;
	}
	// si la grille est pleine on dit que le match est nul 
	if(grillePleine() == 1 )
			printf("le match est NULLLL ");
	return 0;
	// fin du jeu 
}

