#include <stdio.h>
#include <stdlib.h>
#include<time.h> 
#define L 6 
#define C 7


	struct Player {
 		int id ; 
 		char name[50];
 		int score ; 
 		int niveau ;
		char grille[L][C];
 	};
 	
 	FILE* file;
	struct Player currentPlayer ;
	int isBeginingOfGame = 1;
	int niveau ;
	char grille[L][C];
	int i,j;
	int isFree = 0 ;
	char X = 'X', O = 'O' ;
	int isWinner = 0 ;
	int mode ;
	int count = 0;
	int max_value = 0;
	int somme_value_player = 0;
	int somme_value_opponent = 0;
	int EvaluationTable[C] ,TableOfOppositeScenario[C];
    
    void red () {
  		printf("\033[1;31m");
	}

	void yellow (){
  		printf("\033[1;33m");
	}

	void reset () {
  		printf("\033[0m");
	}

 	void creerGrille(char grilleTemporaire[L][C],char grille[L][C]) {
 	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{					
		grilleTemporaire[i][j]=grille[i][j];
		}
	}
 }
  
  	void createNewPlayer(){
  		printf("creating new player : On va créer un neauvou compte pour vous \n");	
  		printf("Veuillez entrer votre nom s'il vous plait \n");
  		scanf("%s", currentPlayer.name);
  		file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "r");
  		char str[200] ;
  		int nextId = 1 ;
  		if(file != NULL){
   			while( fgets (str, 200, file)!=NULL )  nextId++ ;
  		}
   		fclose(file);
   		currentPlayer.id = nextId;
   		currentPlayer.score = 0 ;
   		printf("Votre Id est %d\n", currentPlayer.id);
   		delay(1000);
	}

	void loadPlayer(){
		printf("Entrez votre Id \n");
		scanf("%d", &currentPlayer.id);
		loadPlayerData();
		niveau = currentPlayer.niveau;
		
	}
	void savePlayer(){
	struct Player loadedPlayer , savedPlayer;
	FILE* fileTemp = fopen("D:\\Elearning\\info\\Puissance4\\TemporaryFile.txt", "w");
	file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "r"); 
	int isNewPlayer = 1 ;
	char readChar , writtenChar ;
	char grilleTemporaire[L][C] ;
	if(file!=NULL && fileTemp != NULL) {
		
		while(fscanf(file, "\n%d\t%s\t%d\t%d\t", &loadedPlayer.id ,&loadedPlayer.name , &loadedPlayer.score, &loadedPlayer.niveau ) !=EOF ){    				
		int i,j;  
     	for(i=0;i<L;i++) {
      	for(j=0;j<C;j++) {
        	fscanf(file,"%c",&readChar);
        	if(readChar == '|') readChar = ' ';
        	loadedPlayer.grille[i][j] = readChar ;
            }
    	}
		if(loadedPlayer.id != currentPlayer.id) savedPlayer = loadedPlayer;
		else{
		 isNewPlayer = 0 ;
		 savedPlayer = currentPlayer;
		}
		fprintf(fileTemp, "\n%d\t%s\t%d\t%d\t", savedPlayer.id ,savedPlayer.name , savedPlayer.score, savedPlayer.niveau );
	 	int i2,j2;
     	for(i2=0;i2<L;i2++) {
      	for(j2=0;j2<C;j2++)  {
      		writtenChar = savedPlayer.grille[i2][j2];
      		if(writtenChar ==' ') writtenChar = '|';
       		fprintf(fileTemp, "%c", writtenChar);
   		 }
   	  }
	 }
	   if(isNewPlayer == 1){
	   	 fprintf(fileTemp, "\n%d\t%s\t%d\t%d\t", currentPlayer.id ,currentPlayer.name , currentPlayer.score, currentPlayer.niveau );
	 	int i2,j2;
     	for(i2=0;i2<L;i2++) {
      	for(j2=0;j2<C;j2++)  {
       		fprintf(fileTemp, "%c", '|');
   		 }
   	  } isNewPlayer = 0 ;
	   }	 
	}	
	else 	printf("null");
  fclose(fileTemp);	
  fclose(file);	
    fileTemp = fopen("D:\\Elearning\\info\\Puissance4\\TemporaryFile.txt", "r");
	file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "w");
	 if(file!=NULL && fileTemp != NULL) {
		while(fscanf(fileTemp, "\n%d\t%s\t%d\t%d\t", &loadedPlayer.id ,&loadedPlayer.name , &loadedPlayer.score, &loadedPlayer.niveau ) != EOF ){    				
    	int i,j;  
     	for(i=0;i<L;i++) {
      	for(j=0;j<C;j++) {
      	fscanf(fileTemp,"%c",&readChar);
        if(readChar == '|') readChar = ' ';
        loadedPlayer.grille[i][j] = readChar ;	
        //fscanf(fileTemp,"%c",&loadedPlayer.grille[i][j]);
        //printf("\n%d\t%s\t%d\t%d\tnew char %c\n",loadedPlayer.id ,loadedPlayer.name , loadedPlayer.score, loadedPlayer.niveau,  loadedPlayer.grille[i][j]);
            }
    	}
		fprintf(file, "\n%d\t%s\t%d\t%d\t", loadedPlayer.id ,loadedPlayer.name , loadedPlayer.score, loadedPlayer.niveau );
	 	int i2,j2;
     	for(i2=0;i2<L;i2++) {
      	for(j2=0;j2<C;j2++)  {  		
       		//fprintf(file, "%c", loadedPlayer.grille[i2][j2]);
       		writtenChar = loadedPlayer.grille[i2][j2];
      		if(writtenChar ==' ') writtenChar = '|';
       		fprintf(file, "%c", writtenChar);
   		 }
   	  }
	 }	 
	}
	fclose(fileTemp);	
  fclose(file);
}
void loadPlayerData(){
	 file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "a+");
	 int playerId = currentPlayer.id;
	 char readChar ;
    if(file!=NULL) { 
    while(fscanf(file, "\n%d\t%s\t%d\t%d\t", &currentPlayer.id ,&currentPlayer.name , &currentPlayer.score, &currentPlayer.niveau ) != EOF){   
	   printf("loading all player data \n"); 	 				
    	int i,j;  
     	for(i=0;i<L;i++) {
      	for(j=0;j<C;j++) {
       		 fscanf(file,"%c",&readChar);
       		 if(readChar =='|') readChar = ' ';
       		 currentPlayer.grille[i][j] = readChar;
            }
    	}
		if(playerId == currentPlayer.id) {
		printf("Ce joueur est enregistré dans la base de donnees \n");
		return ; 
		}
	  }
	  printf("Ce joueur n'est pas enregistré dans la base de donnees ! \n");
	  printf("On vous demande de vérifier votre Identifiant ! \n");
	  loadPlayerWithAllData();	
    }
    fclose(file);    	
}
		
	void saveAllPlayerData(int newScore , int niveau,char grille[L][C]){
		printf("saving all player data\n");
		currentPlayer.score += newScore;
		currentPlayer.niveau = niveau;
		creerGrille(currentPlayer.grille, grille);	
		savePlayer();
	}
	void savePlayerData(int newScore){
		saveAllPlayerData(newScore, niveau , currentPlayer.grille);
	}
	void loadPlayerWithAllData(){
		printf("Entrez votre Id \n");
		scanf("%d", &currentPlayer.id);
		loadPlayerData();
		creerGrille(grille , currentPlayer.grille);
		niveau = currentPlayer.niveau;
		printf("Bonjour %s vous au niveau %d   votre score est %d , c'est le tour de l'ordi \n", currentPlayer.name, currentPlayer.niveau, currentPlayer.score );		
	}
	void playerState(int stateNumber ){
		char state[20] ;
		if(stateNumber ==0) strcpy( state , "eu un match null");
		if(stateNumber ==-1) strcpy( state , "perdu le match");
		if(stateNumber ==1) strcpy( state , "gagne le match");
		printf(" \nle joueur : %s a %s ,   son score maitenant est : %d \n", currentPlayer.name , state, currentPlayer.score);
	}
	void delay(int milli_seconds) 
{ 
    
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
	// cette fonctiion nous permet de trouver la valeur maximal de deux nombre
 	int max(int a, int b){
 		return (a <= b) ? b: a;
	 }
	 int min(int a, int b){
 		return !(a <= b) ? b: a;
	 }
	 int maxTable(int T[], int taille){
	 	// find the max 
	 	int maximum = T[0];
	 	int j ;
	 
	 	for(j = 0 ; j < taille ; j++){
	 	maximum= max(maximum , T[j]);}
	 	// gettiing the index 
	 	for(j = 0 ; j < taille ; j++){		 
	 	if( T[j]== maximum) return  j;
	 }
	 }
	 int nextMaxTable(int T[], int taille){
		int T1[taille];
		int j ;
		for(j = 0 ; j < taille ; j++){
			if(T[j] != 0) T1[j] =T[j];
			else T1[j] = -10000;
			
		}
		return maxTable(T1, taille);
	 }
	 int minTable(int T[], int taille){
	 	// find the min 
	 	int minimum = T[0];
	 	int j ;
	 
	 	for(j = 0 ; j < taille ; j++){
	 	minimum= min(minimum , T[j]);}
	 	// gettiing the index 
	 	for(j = 0 ; j < taille ; j++){		 
	 	if( T[j]== minimum) return  j;
	 }
	 }
	 int maxValueOfTable(int T[], int taille){
	 	// find the max 
	 	int maximum = T[0];
	 	int j ;
	 
	 	for(j = 0 ; j < taille ; j++){
	 	maximum= max(maximum , T[j]);}
	 	return maximum ;
	 }
	 int minValueOfTable(int T[], int taille){
	 	// find the min 
	 	int minimum = T[0];
	 	int j ;
	 
	 	for(j = 0 ; j < taille ; j++){
	 	minimum= min(minimum , T[j]);}
	 	return minimum;
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
	int CurrentLine(int j,char grille[L][C]){
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
		 
		 if(compteur >= 4) {
		 	
		 return 1;
		}	}
		
		 return 0 ;
		}	


  // cette methode teste s'il y a un alignement incliné dans le sens  "\"
  
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
	  // cette methode teste s'il y a un alignement incliné dans le sens "/"	  
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
  void affichage2(char grille[L][C]){
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
 int modeDefensive_Moyenne(){
 	somme_value_player = 0 ;
 	somme_value_opponent = 0;
 		int i , j;
	char grilleTemporaire[L][C];
 		for(j = 0 ; j <C ; j++){
 	 	EvaluationTable[j] = 0;
	 }
	for(j = 0 ; j <C ; j++){
		creerGrille(grilleTemporaire,grille);
		if((i =CurrentLine(j,grilleTemporaire)) >= 0 ){
		grilleTemporaire[i][j]	= X ;
		somme_value_player = CalculValue(i,j,X,grilleTemporaire);
		creerGrille(grilleTemporaire,grille);
		grilleTemporaire[i][j]	= O ;
		somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
		EvaluationTable[j] = (int) ( 0.4 *somme_value_player )+  somme_value_opponent ;
	   }
	   	}
	return maxTable(EvaluationTable,C);
		
 }
 int modeOffensive_Moyenne(){
 	somme_value_player = 0 ;
 	somme_value_opponent = 0;
 	int i , j;
	char grilleTemporaire[L][C]; 	
 	for(j = 0 ; j <C ; j++){
 	 	EvaluationTable[j] = 0;
	 }
	for(j = 0 ; j <C ; j++){
		creerGrille(grilleTemporaire,grille);
		if((i =CurrentLine(j,grilleTemporaire)) >= 0 ){
		grilleTemporaire[i][j]	= X ;
		somme_value_player = CalculValue(i,j,X,grilleTemporaire);
		creerGrille(grilleTemporaire,grille);
		grilleTemporaire[i][j]	= O ;
		somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
		EvaluationTable[j] = somme_value_player + (int) ( 0.4 *somme_value_opponent) - (int) ( 0.1 * oppositeScenario(grilleTemporaire) );
	   }		
	}	
	return maxTable(EvaluationTable,C);			
 }
 int oppositeScenario(char grille[L][C]){
 	somme_value_player = 0 ;
 	somme_value_opponent = 0;
 	int i , j;
	char grilleTemporaire[L][C]; 	
 	for(j = 0 ; j <C ; j++){
 	 	TableOfOppositeScenario[j] = 0;
	 }
	 creerGrille(grilleTemporaire,grille);
	for(j = 0 ; j <C ; j++){		
		if((i =CurrentLine(j,grilleTemporaire)) >= 0 ){		
		grilleTemporaire[i][j]	= O ;
		somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
		grilleTemporaire[i][j]	= ' ';
		TableOfOppositeScenario[j] =  somme_value_opponent ;
	   }
	   else TableOfOppositeScenario[j] =0 ;
		
	}
	
	
	return  maxValueOfTable(TableOfOppositeScenario,C);
	
 }
  
    int finalDepth(char grille[L][C]){
 	char grilleTemporaire[L][C]; 
 	int EvaluationTable[C] ;
 	for(j = 0 ; j <C ; j++){
 	 	EvaluationTable[j] = 0;
	 }
	creerGrille(grilleTemporaire,grille);
 	int i , j ;
 		for(j = 0 ; j <C ; j++)	{
			if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {						
					    grilleTemporaire[i][j]	= X ;
					    
						EvaluationTable[j] = CalculValue(i,j,X,grilleTemporaire) - oppositeScenario(grilleTemporaire) ;	
						grilleTemporaire[i][j]	= ' ' ;											
						}
						else EvaluationTable[j] = 0;					
						}
						
						return maxValueOfTable(EvaluationTable,C);
						
 }
 int firstDepth(char grille[L][C], int depth){	
 	int i , j ;
 	char grilleTemporaire[L][C]; 
 	int EvaluationTable[C] ;
 	for(j = 0 ; j <C ; j++){
 	 	EvaluationTable[j] = 0;
	 }
	creerGrille(grilleTemporaire,grille);
		for(j = 0 ; j <C ; j++)	{
		if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {
		grilleTemporaire[i][j]	= X ;		 
		EvaluationTable[j] = futurDeGrille(grilleTemporaire, depth+1);	
		grilleTemporaire[i][j]	= ' ' ;
 }		else EvaluationTable[j] = 0; 
 			
}    	
		// on verifie bien que le coup issu de minmax est signifiant qqc
		int probableColumn = 	nextMaxTable(EvaluationTable,C) ;
		int a = CurrentLine(probableColumn,grilleTemporaire);
		grilleTemporaire[a][probableColumn]	= X ;
		if(oppositeScenario(grilleTemporaire) > 5000	){		
		probableColumn = modeOffensive_Moyenne();
		}
		return  probableColumn ;
 }
 int intermediaiteDepth(char grille[L][C], int depth){ 	 	
 	char a = (depth%2 != 0) ? X : O;
 	int i , j ;
 	char grilleTemporaire[L][C]; 
 	int EvaluationTable[C] ;
 	for(j = 0 ; j <C ; j++){
 	 	EvaluationTable[j] = 0;
	 }
	creerGrille(grilleTemporaire,grille);
	for(j = 0 ; j <C ; j++)	{
		if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {
		grilleTemporaire[i][j]	= a ;
		
		EvaluationTable[j] = futurDeGrille(grilleTemporaire, depth+1);	
		grilleTemporaire[i][j]	= ' ' ;	
 }		else EvaluationTable[j] = 0;
}	
      return (depth%2 != 0) ? maxValueOfTable(EvaluationTable,C) : minValueOfTable(EvaluationTable,C);
 }
 int futurDeGrille(char grille[L][C], int depth){
		if(1<depth && depth < 3)
		return 	intermediaiteDepth(grille, depth);		
		else if(depth == 3)
		return finalDepth(grille);
		else 
		return	firstDepth(grille, depth);	

}
 int modeExpert(){
 	// premierement on voit si le mode intermediaire peut nous faire gagner afin de ne pas perdre nos efforts
 	if(EvaluationTable[modeOffensive_Moyenne()] > 5000) return modeOffensive_Moyenne();
 	if(EvaluationTable[modeDefensive_Moyenne()] > 5000) return modeDefensive_Moyenne();
 	return futurDeGrille(grille, 1);
 }
 void computerTurn(int niveau){
 	isFree = 0;
 	int j;
 	switch(niveau){
 		case 1: {
 			srand(time(0)); 
 		  	j = rand() % 7 ;
 		  	oppositeScenario(grille);
			break;
		 }
 		case 2: j = modeDefensive_Moyenne();
 			break;
 		case 3:j =modeOffensive_Moyenne();
 			break;
 		case 4:j =modeExpert();
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
	printf(" \n   L'ordinateur a gagné :	Le	match est perdu 	!	!	! \n");
	
}
 }
 void demandeAuJoueur(char a){
 	isFree = 0;
 		printf("joueur %c entrez le numero de la colonne \n",a);
	scanf("%d",&j);
	//system("cls");
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
	printf(" \n 	Le	 joueur %c 	a	 gagné 	!	!	! \n",a);
	
}
  }   
 void initialization(){
 	
	char entrer =' ';
	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{
					
		grille[i][j]=' ';}
		
	}
	char answer = 'N';
	int loadType ;
	if( isBeginingOfGame == 1){
	printf("\n\n\n\t\t		Bienvenue à Puissance4  \n\n\n ");
	printf("\n 				click Entrer  pour continuer  ");
	while ( entrer!= '\n' ){
		scanf("%c",&entrer);
	}	
	do{	
	printf("Est ce que vous avez déjà enregistrer une version du jeu 'O'/'N'\n");
	scanf("%c", &answer);
	}while(answer != 'O' && answer != 'N');
	if(answer == 'O'){
	do{		
	system("cls");
	printf( "\n\n veuillez choisir le type de chargement  :\n");
	printf("\n\n \t  1-Charger tous les données( le point ou je me suis arrété) 					2-Charger seulement les infos importantes (id , name et score) \n");
	scanf("%d", &loadType);
	}while(loadType != 1 && loadType != 2);
	}	
	}
	if(answer == 'N' || loadType == 2){	
	if(isBeginingOfGame == 1){			
	if(answer =='N') createNewPlayer();
	else loadPlayer();
	}
	do{
	system("cls");
	printf( "\n\n veuillez choisir le mode du jeu :\n");
	printf("\n\n \t  1-Mode un seul joueur 					2-Mode deux joueur \n");
	scanf("%d",&mode);
	}
	while(mode != 1 && mode !=2);	
	}
	else {
		loadPlayerWithAllData();			
	}
	isBeginingOfGame = 0 ;
	printf("is beginin g of game : %d ", isBeginingOfGame);
	//system("cls");	
 } 
 void playWithTheComputer(int niveau){
 	printf("			Vous etes le joueur : O \n");
 	printf("\n			OK ! LET'S GET STARTED !!!!");
 	delay(1000);	
	while(grillePleine() == 0 ) { // la boucle se répète tant que la grille est pleine	
	computerTurn(niveau);	
	affichage();
	//
	// si le joureur l'ordinateur  a gagné on arrete le jeu 
	if(isWinner == 1){
	 playerState(-1);
	 return;
	 }
	delay(500);
	demandeAuJoueur(O);	
	affichage();
	// on enregistre le jeu avant le prochain coup du joueur 
	saveAllPlayerData(0, niveau , grille);
	// si le joureur O  a gag	né on arrete le jeu 
	if(isWinner == 1){
	 saveAllPlayerData(10 * niveau, niveau , grille);
	 playerState(1);
	 return;
	 }
	delay(500);
	//system("cls");
	}
	// si la grille est pleine on dit que le match est nul 
	if(grillePleine() == 1 ){
			saveAllPlayerData(10, niveau , grille);
			printf("le match est NULLLL ");
			playerState(0);
	}
 }
 void modeSeulJoueur(){ 	
 	do{	
 	system("cls");
	printf( " veuillez choisir le niveau du jeu :\n");
	printf("\n\t\t\t\t\t\t 1- DEBUTANT\t\t    * \n\n				\t	2- INTERMEDIAIRE_DEFENSIVE  **\n\n	\t				3- INTERMEDIAIRE_OFFENSIVE  ***\n\n\t	\t\t\t	 4- EXPERT    \t\t**** \n");
	scanf("%d",&niveau);
	}
	while(niveau != 1 && niveau !=2 && niveau != 3 &&niveau != 4);
	system("cls");
 	playWithTheComputer(niveau);
 }
 void modeDeuxJoueur(){
 	printf("joueur1 : X \n");
	printf("joueur2 : O \n");
	affichage();
	delay(400);
	while(grillePleine() == 0 ) { // la boucle se répète tant que la grille n'est pas pleine
	demandeAuJoueur(X);	
	
	affichage();
	// si le joureur X  a gagné on arrete le jeu 
	if(isWinner == 1){
	 savePlayerData(20);
	 playerState(1);
	 return;
	 }
	delay(400);
	demandeAuJoueur(O);
	
	affichage();
	// si le joureur O  a gagné on arrete le jeu 
	if(isWinner == 1){
	 savePlayerData(0);
	 playerState(-1);
	 return;
	 }
	delay(400);
	}
	// si la grille est pleine on dit que le match est nul 
	if(grillePleine() == 1 ){	
			printf("le match est NULLLL ");
			savePlayerData(10);
			playerState(0);
	}
 }  
 void setPlayer(){
 /*	printf("\n\n\n\t\t		Bienvenue à Puissance4  \n\n\n ");
	printf("\n 				click Entrer  pour continuer  ");
	while ( entrer!= '\n' ){
		scanf("%c",&entrer);
	}
*/	
 }
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	//setPlayer();
	// initialisation de la grille (not affichage!)	
	char tryAgain = 'O';
	do{
	isWinner = 0 ;
	initialization ();
	if(mode == 1) modeSeulJoueur();
	else if(mode == 2) modeDeuxJoueur();
	else playWithTheComputer(currentPlayer.niveau);
	do{
	scanf("%c",&tryAgain);
	printf("\n\nVoulez-vous jouer encore une fois 'O'/'N'\n");
	scanf("%c",&tryAgain);
	}while(tryAgain != 'O' && tryAgain != 'N');
	}
	while(tryAgain == 'O');
	printf(" fin du jeu ");
	return 0;
	// fin du jeu 
}


