#include <stdio.h>
#include <stdlib.h>
#include<time.h> 
#define L 6 
#define C 7

	char grille[L][C];
	int i,j;
	int isFree = 0 ;
	char X = 'X', O = 'O' ;
	int isWinner = 0 ;
	int mode ;
	
	int max_value = 0;
	int somme_value_player = 0;
	int somme_value_opponent = 0;
	int EvaluationTable[C] ;
	
	// cette fonctiion nous permet de trouver la valeur maximal de deux nombre
 	int max(int a, int b){
 		return (a <= b) ? b: a;
	 }
	 int maxTable(int T[], int taille){
	 	// find the max 
	 	int maximum = 0;
	 	int j ;
	 
	 	for(j = 0 ; j < taille ; j++){
	 	maximum= max(maximum , T[j]);}
	 	// gettiing the index 
	 	for(j = 0 ; j < taille ; j++){		 
	 	if( T[j]== maximum) return  j;
	 }
	 }
	void creerGrille(char grilleTemporaire[L][C],char grille[L][C]) {
 	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{					
		grilleTemporaire[i][j]=grille[i][j];
		}
	}
 }
 	int maxRectifie(int max ){
 		switch(max){
 			case 0 : return 0;
 		
 			case 1 : return 100 ;
 			case 2 : return 200 ;
 			case 3 : return 300;
 			case 4 : return 10000;
	 	}
	 }
	int CurrentLine(int j){
 		int i ;
 		for(i = L-1 ; i >= 0 ; i--) {
 		if(grille[i][j] == ' ') return i;
	 }
	 
	 return -1;
 	
 }
//  cette fonction teste s'il y a un alignement vertical	
 int verticalement(char a ,int i , int j,char grille[L][C]){
  	  	int compteur =0 ;
  	  	max_value = 0;
  	  	int x;
  	  	for(x = 0 ; x < L ; x++){
  	  		if(grille[x][j] ==a)
					compteur++;			
			else    compteur =0 ;
			if( (x - compteur) <= i && x >= i  )
			max_value = max(compteur,max_value);			
				if(compteur >= 4) return 1;
			}
			 return 0 ;
		}
		
	// cette methode teste s'il y a un alignement horizontal	
  int  horizontalement(char a , int i,int j ,char grille[L][C]){
  	  	int compteur =0 ;
  	  	max_value = 0;
  	  	int x;
  	  	for(x = 0 ; x < C ; x++){
  	  		
  	  	  if(grille[i][x] ==a)
				 compteur++;
		 else    compteur =0 ;
		 if( (x - compteur) <= j && x >= j  )
		 max_value = max(compteur,max_value);
		 if(compteur >= 4) return 1;
			}
		 return 0 ;
		}	


  // cette methode teste s'il y a un alignement inclin� dans le sens  "\"
  
    int incline1(char a , int i , int j,char grille[L][C]){
    	// on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j-1,i-1) 
    	// l'equation est y = x + i - j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    	// alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    	int compteur =0 ;
    	max_value = 0;
  	  	int x;
  	  	int y ;
  	  	for(x = 0 ;( x < C ); x++ ){ 
			y  = x + i-j ;	
			if(y >= 0 && y < L){
			
  	  	  if(grille[y][x] ==a)
				 compteur++;
		 else    compteur =0 ;
		  if( (x - compteur) <= j && x >= j  )
		 max_value = max(compteur,max_value);
		 if(compteur >= 4) return 1;
			}
		}
		 return 0 ;
	}
	
	  // cette methode teste s'il y a un alignement inclin� dans le sens "/"
	  
	 int incline2(char a , int i , int j,char grille[L][C]){
	 	// on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j+1,i-1) 
    	// l'equation est y = -x + i + j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    	// alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    	int compteur =0 ;
    	max_value = 0;
  	  	int x;
  	  	int y ;
  	  	for(x = 0 ;( x < C ); x++ ){ 
  	  	 y  = -x + i +j ;
			if (y >= 0 && y < L){
			
  	  	  if(grille[y][x] ==a)
			 compteur++;		 						 				 
		 else    compteur =0 ;
		  if( (x - compteur) <= j && x >= j  )
		 max_value = max(compteur,max_value);
		 if(compteur >= 4) return 1;
			}}
    	return 0;
	} 


	// cette methode (fonction) test s'il y a une vainqueur 
  int isThere_Winner(char a , int i , int j,char grille[L][C]){
  	// pour ce faire on realise le test dans les quatres directions
  	if(verticalement(a,i,j,grille) ==1) return 1;
  	if(horizontalement(a,i,j,grille) == 1) return 1;
  	if (incline1(a,i,j,grille) == 1) return 1;
  	if (incline2(a,i,j,grille) == 1) return 1;
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
 int CalculValue(int i,int j, char a,char grilleTemporaire[L][C]){
 		int 	somme_value = 0;

 		
 		verticalement(a,i,j,grilleTemporaire);		 
		somme_value += maxRectifie(max_value);	

		horizontalement(a,i,j,grilleTemporaire);
		somme_value += maxRectifie(max_value);
		
		incline1(a,i,j,grilleTemporaire);
		somme_value += maxRectifie(max_value);

		incline2(a,i,j,grilleTemporaire);
		somme_value += maxRectifie(max_value);
	
	 
	somme_value +=( 3 - abs(j-3))*30;
 	return 	 somme_value;
   }
 int modeAgressive_Moyenne(){
 	int i , j;
	char grilleTemporaire[L][C];
 	
	for(j = 0 ; j <C ; j++){
		creerGrille(grilleTemporaire,grille);
		if((i =CurrentLine(j)) >= 0 ){
		grilleTemporaire[i][j]	= X ;
		somme_value_player = CalculValue(i,j,X,grilleTemporaire);
		creerGrille(grilleTemporaire,grille);
		grilleTemporaire[i][j]	= O ;
		somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
		EvaluationTable[j] = somme_value_player + (int) ( 0.4 *somme_value_opponent) ;
	   }
		//printf("C%d : %d	",j+1,EvaluationTable[j]);
	}
	return maxTable(EvaluationTable,C);
			
 }
 
 void computerTurn(int niveau){
 	isFree = 0;
 	int j;
 	switch(niveau){
 		case 1: {
 			srand(time(0)); 
 		  	j = rand() % 7 ;
			break;
		 }
 		case 2: j = modeAgressive_Moyenne();
 			break;
 		case 3:j =3;
 			break;
	 }
 		i= L-1;
		while(isFree == 0 && i >= 0 ){
			
			if(grille[i][j]==' ')			
			isFree = 1;			
			else
			i--;
		}
 	if( isFree == 0) {
	   computerTurn(niveau);
	}
	else 	
	grille[i][j]= 'X' ;
	// voir si ce joueur est un winner 
	if(isThere_Winner('X',i,j,grille) == 1) {
		isWinner = 1 ;
	printf(" \n   L'ordinateur a gagn� :	Le	match est perdu 	!	!	! \n");
	
}
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
	if(isThere_Winner(a,i,j,grille) == 1) {
		isWinner = 1 ;
	printf(" \n 	Le	 joueur %c 	a	 gagn� 	!	!	! \n",a);
	
}
  }
   
 void initialization(){
 	
	char entrer =' ';
	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{
			if(grille[i][j] != X  && grille[i][j] != O){			
		grille[i][j]=' ';}
		}
	}
	printf("\n\n\n\t\t		Bienvenue � Puissance4  \n\n\n ");
	printf("\n 				click Entrer  pour continuer  ");
	while ( entrer!= '\n' ){
		scanf("%c",&entrer);
	}
	do{
	
	printf( "\n\n veuillez choisir le mode du jeu :\n");
	printf("\n\n \t  1-Mode un seul joueur 					2-Mode deux joueur \n");
	scanf("%d",&mode);
	}
	while(mode != 1 && mode !=2);	
 } 

 void playWithTheComputer(int niveau){
 	printf("			Vous etes le joueur : O \n");
 	printf("\n			OK ! LET'S GET STARTED !!!!");
 		
	while(grillePleine() == 0 ) { // la boucle se r�p�te tant que la grille est pleine
	
	computerTurn(niveau);	
	affichage();
	// si le joureur l'ordinateur  a gagn� on arrete le jeu 
	if(isWinner == 1) return;
	demandeAuJoueur(O);
	affichage();
	// si le joureur O  a gagn� on arrete le jeu 
	if(isWinner == 1) return;
	}
	// si la grille est pleine on dit que le match est nul 
	if(grillePleine() == 1 )
			printf("le match est NULLLL ");
 }
 
 void modeSeulJoueur(){
 	int niveau ;
 	do{	
	printf( " veuillez choisir le niveau du jeu :\n");
	printf(" \t  1- DEBUTANT* 					2- INTERMEDIAIRE** 			 3- EXPERT *** \n");
	scanf("%d",&niveau);
	}
	while(niveau != 1 && niveau !=2 && niveau != 3);
 	playWithTheComputer(niveau);
 }
 void modeDeuxJoueur(){
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
 }
   
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	// initialisation de la grille (not affichage!)

	
	initialization ();
	if(mode == 1) modeSeulJoueur();
	else modeDeuxJoueur();

	return 0;
	// fin du jeu 
}


