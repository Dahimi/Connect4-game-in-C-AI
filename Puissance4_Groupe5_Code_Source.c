#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define L 6
#define C 7
// ******* Veuillez changer l'emplacement des fichiers txt (file, fileTemp)  ou' vous allez enregistrer les donn�es
// creating a structure 
struct Player {
    int id ;
    char name[50];
    int score ;
    int niveau ;
    char grille[L][C];
};
// d�claration des variables globales
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


//  **************   Helper functions  **********************

// fonctions pour modifier la coleur du texte de la console

void red () {
    printf("\033[1;31m");
}

void yellow () {
    printf("\033[1;33m");
}
void blue() {
    printf("\033[0;34m");
}
void green() {
    printf("\033[0;32m");
}
void reset () {
    printf("\033[0m");
}

// creer une graille � partir d'une autre grille
void creerGrille(char grilleTemporaire[L][C],char grille[L][C]) {
    for(i=0; i<L; i++) {
        for(j=0; j<C; j++)
        {
            grilleTemporaire[i][j]=grille[i][j];
        }
    }
}
void clearGrid(){
	for(i=0; i<L; i++) {
        for(j=0; j<C; j++)
        {
            grille[i][j] = ' ';
        }
    }
}
void createNewPlayer() {
	system("cls");
    green();
    printf("		creating new player : On va cr�er un neauvou compte pour vous \n \n");
    blue();
    printf("Veuillez entrer votre nom s'il vous plait \n");
    reset();
    scanf("%s", currentPlayer.name);
    file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "r");
    char str[200] ;
    int nextId = 1 ;
    if(file != NULL) {
        while( fgets (str, 200, file)!=NULL )  nextId++ ;
    }
    fclose(file);
    currentPlayer.id = nextId;
    currentPlayer.score = 0 ;
    printf("Votre Id est %d\n", currentPlayer.id);
    delay(1000);
}
// le chargement des donn�es : score , nom , id du joueur 
void loadPlayer() {
	system("cls");
    blue();
    printf("\n\n		Entrez votre Id \n");
    reset();
    scanf("%d", &currentPlayer.id);
    loadPlayerData();
    niveau = currentPlayer.niveau;

}
//  Helper method pour le sauvegarde des donn�es
void savePlayer() {
	// variable locaux
    struct Player loadedPlayer , savedPlayer;
    // Output stream for temporary file 
    FILE* fileTemp = fopen("D:\\Elearning\\info\\Puissance4\\TemporaryFile.txt", "w");
    // input stream for the original file 
    file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "r");
    int isNewPlayer = 1 ;
    char readChar , writtenChar ;
    char grilleTemporaire[L][C] ;
    // coupier les donn�es de file dans fileTemp , sauf pour les donn�es du joueur qui seront mises � jour
    if(file!=NULL && fileTemp != NULL) {

        while(fscanf(file, "\n%d\t%s\t%d\t%d\t", &loadedPlayer.id ,&loadedPlayer.name , &loadedPlayer.score, &loadedPlayer.niveau ) !=EOF ) {
            int i,j;
            for(i=0; i<L; i++) {
                for(j=0; j<C; j++) {
                    fscanf(file,"%c",&readChar);
                    if(readChar == '|') readChar = ' ';
                    loadedPlayer.grille[i][j] = readChar ;
                }
            }
            if(loadedPlayer.id != currentPlayer.id) savedPlayer = loadedPlayer;
            else {
                isNewPlayer = 0 ;
                savedPlayer = currentPlayer;
            }
            fprintf(fileTemp, "\n%d\t%s\t%d\t%d\t", savedPlayer.id ,savedPlayer.name , savedPlayer.score, savedPlayer.niveau );
            int i2,j2;
            for(i2=0; i2<L; i2++) {
                for(j2=0; j2<C; j2++)  {
                    writtenChar = savedPlayer.grille[i2][j2];
                    if(writtenChar ==' ') writtenChar = '|';
                    fprintf(fileTemp, "%c", writtenChar);
                }
            }
        }
        if(isNewPlayer == 1) {
            fprintf(fileTemp, "\n%d\t%s\t%d\t%d\t", currentPlayer.id ,currentPlayer.name , currentPlayer.score, currentPlayer.niveau );
            int i2,j2;
            for(i2=0; i2<L; i2++) {
                for(j2=0; j2<C; j2++)  {
                    fprintf(fileTemp, "%c", '|');
                }
            }
            isNewPlayer = 0 ;
        }
    }
    else 	printf("null");
    fclose(fileTemp);
    fclose(file);
    // input stream from fileTemp
    fileTemp = fopen("D:\\Elearning\\info\\Puissance4\\TemporaryFile.txt", "r");
    // output stream to the original file
    file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "w");
    // coupier les donn�es de fileTemp dans file
    if(file!=NULL && fileTemp != NULL) {
        while(fscanf(fileTemp, "\n%d\t%s\t%d\t%d\t", &loadedPlayer.id ,&loadedPlayer.name , &loadedPlayer.score, &loadedPlayer.niveau ) != EOF ) {
            int i,j;
            for(i=0; i<L; i++) {
                for(j=0; j<C; j++) {
                    fscanf(fileTemp,"%c",&readChar);
                    if(readChar == '|') readChar = ' ';
                    loadedPlayer.grille[i][j] = readChar ;
                }
            }
            fprintf(file, "\n%d\t%s\t%d\t%d\t", loadedPlayer.id ,loadedPlayer.name , loadedPlayer.score, loadedPlayer.niveau );
            int i2,j2;
            for(i2=0; i2<L; i2++) {
                for(j2=0; j2<C; j2++)  {
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
// Helper method pour  chargement des donn�es 
void loadPlayerData() {
    file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "a+");
    int playerId = currentPlayer.id;
    char readChar ;
    if(file!=NULL) {
    	// On charges les donn�es les plus importantes : id , nom score et aussi le niveau 
        while(fscanf(file, "\n%d\t%s\t%d\t%d\t", &currentPlayer.id ,&currentPlayer.name , &currentPlayer.score, &currentPlayer.niveau ) != EOF) {
            green();
            int count = 0 ;
            for(count = 0 ; count <3 ; count++){
            	system("cls");
            	printf(" \n \tloading  player data  .\n");
            	delay(300);
            	system("cls");
            	printf(" \n \tloading  player data  ..\n");
            	delay(300);
            	system("cls");
            	printf(" \n \tloading  player data  ...\n");
            	delay(300);
       		 }
       		 // On charge la grille 
            int i,j;
            for(i=0; i<L; i++) {
                for(j=0; j<C; j++) {
                    fscanf(file,"%c",&readChar);
                    if(readChar =='|') readChar = ' ';
                    currentPlayer.grille[i][j] = readChar;
                }
            }
            if(playerId == currentPlayer.id) {
                printf("\nCe joueur est enregistr� dans la base de donnees \n");
                return ;
            }
        }
        // le cas ou le joueur n'est pas dans BD , on envoie un avertissement , et on r�p�te le processus
        printf("\033[1;31m");
        printf("Ce joueur n'est pas enregistr� dans la base de donnees ! \n");
        printf("On vous demande de v�rifier votre Identifiant ! \n");
        delay(1000);
        loadPlayerWithAllData();
    }
    fclose(file);
}
// le sauvegarde de tous les donn�es pass�es dans param�tres
void saveAllPlayerData(int newScore , int niveau,char grille[L][C]) {
    currentPlayer.score += newScore;
    currentPlayer.niveau = niveau;
    creerGrille(currentPlayer.grille, grille);
    savePlayer();
}
// le sauvegarde du score 
void savePlayerData(int newScore) {
    saveAllPlayerData(newScore, niveau , currentPlayer.grille);
}
//le chargement de toutes les donn�es
void loadPlayerWithAllData() {
	system("cls");
    blue();
    printf("\n\n		Entrez votre Id \n");
    reset();
    scanf("%d", &currentPlayer.id);
    loadPlayerData();
    creerGrille(grille , currentPlayer.grille);
    niveau = currentPlayer.niveau;
    green();
    printf("Bonjour %s vous au niveau %d   votre score est %d , c'est le tour de l'ordi \n", currentPlayer.name, currentPlayer.niveau, currentPlayer.score );
    reset();
}
void playerState(int stateNumber ) {
    char state[20] ;
    green();
    if(stateNumber ==0) strcpy( state , "eu un match null");
    if(stateNumber ==-1) strcpy( state , "perdu le match");
    if(stateNumber ==1) strcpy( state , "gagne le match");
    printf(" \nle joueur : %s a %s ,   son score maitenant est : %d \n", currentPlayer.name , state, currentPlayer.score);
    reset();
}
// helper method for delay 
void delay(int milli_seconds)
{

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

// ********* helper methods for dealing with arrays ***********************

// cette fonctiion nous permet de trouver la valeur maximal de deux nombre
int max(int a, int b) {
    return (a <= b) ? b: a;
}
int min(int a, int b) {
    return !(a <= b) ? b: a;
}
int maxTable(int T[], int taille) {
    // find the max
    int maximum = T[0];
    int j ;
    for(j = 0 ; j < taille ; j++) {
        maximum= max(maximum , T[j]);
    }
    // gettiing the index
    for(j = 0 ; j < taille ; j++) {
        if( T[j]== maximum) return  j;
    }
}
int nextMaxTable(int T[], int taille) {
    int T1[taille];
    int j ;
    for(j = 0 ; j < taille ; j++) {
        if(T[j] != 0) T1[j] =T[j];
        else T1[j] = -10000;

    }
    return maxTable(T1, taille);
}
int minTable(int T[], int taille) {
    // find the min
    int minimum = T[0];
    int j ;

    for(j = 0 ; j < taille ; j++) {
        minimum= min(minimum , T[j]);
    }
    // gettiing the index
    for(j = 0 ; j < taille ; j++) {
        if( T[j]== minimum) return  j;
    }
}
int maxValueOfTable(int T[], int taille) {
    // find the max
    int maximum = T[0];
    int j ;

    for(j = 0 ; j < taille ; j++) {
        maximum= max(maximum , T[j]);
    }
    return maximum ;
}
int minValueOfTable(int T[], int taille) {
    // find the min
    int minimum = T[0];
    int j ;

    for(j = 0 ; j < taille ; j++) {
        minimum= min(minimum , T[j]);
    }
    return minimum;
}

//************ helper functions for finding the winner , knowing the grid state , displaying the grid and much more ... ********************

// Un peu d'amplification de la valeur max !!!!!!!!!!!!!
int maxRectifie(int max ) {
    switch(max) {
    case 0 :
        return 0;
    case 1 :
        return 100 ;
    case 2 :
        return 200 ;
    case 3 :
        return 300;
    case 4 :
        return 10000;
    }
}
// retourner le num�ro de la ligne disponible correspondate � la colonne j dans la grille grille[L][C], et -1 dans le cas �ch�ant 
int CurrentLine(int j,char grille[L][C]) {
    int i ;
    for(i = L-1 ; i >= 0 ; i--) {
        if(grille[i][j] == ' ') return i;
    }

    return -1;

}
//  cette fonction teste s'il y a un alignement vertical
int verticalement(char a ,int i , int j,char grille[L][C]) {
    int compteur =0 ;
    max_value = 0;
    int x;
    for(x = 0 ; x < L ; x++) {
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
int  horizontalement(char a , int i,int j ,char grille[L][C]) {
    int compteur =0 ;
    max_value = 0;
    int x;
    for(x = 0 ; x < C ; x++) {

        if(grille[i][x] ==a)
            compteur++;
        else    compteur =0 ;
        if( (x - compteur) <= j && x >= j  )
            max_value = max(compteur,max_value);

        if(compteur >= 4) {

            return 1;
        }
    }

    return 0 ;
}


// cette methode teste s'il y a un alignement inclin� dans le sens  "\"

int incline1(char a , int i , int j,char grille[L][C]) {
    // on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j-1,i-1)
    // l'equation est y = x + i - j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    // alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    int compteur =0 ;
    max_value = 0;
    int x;
    int y ;
    for(x = 0 ; ( x < C ); x++ ) {
        y  = x + i-j ;
        if(y >= 0 && y < L) {

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
int incline2(char a , int i , int j,char grille[L][C]) {
    // on va essayer de trouver l'equation de la droite qui passe par M(j,i) et M'(j+1,i-1)
    // l'equation est y = -x + i + j avec y est ordonne (les lignes ) et x l abscisse (colonne)
    // alors au lieu de parcourir une droite hor ou verti on va parcourir cette droite que nous venons de trouver son equation
    int compteur =0 ;
    max_value = 0;
    int x;
    int y ;
    for(x = 0 ; ( x < C ); x++ ) {
        y  = -x + i +j ;
        if (y >= 0 && y < L) {

            if(grille[y][x] ==a)
                compteur++;
            else    compteur =0 ;
            if( (x - compteur) <= j && x >= j  )
                max_value = max(compteur,max_value);
            if(compteur >= 4) return 1;
        }
    }
    return 0;
}

// cette methode (fonction) test s'il y a une vainqueur
int isThere_Winner(char a , int i , int j,char grille[L][C]) {
    // pour ce faire on realise le test dans les quatres directions
    if(verticalement(a,i,j,grille) ==1) return 1;
    if(horizontalement(a,i,j,grille) == 1) return 1;
    if (incline1(a,i,j,grille) == 1) return 1;
    if (incline2(a,i,j,grille) == 1) return 1;
    return 0;
}
//  On teste si la grille est pleine
int grillePleine() {
    int j = 0;
    for( j = 0 ; j < C ; j++ ) {

        if(grille[0][j] ==' ') return 0;
    }
    return 1 ;
}
// affichage de la grille principale du jeu 
void affichage() {
    printf("\n");
    for(i=0; i<L; i++) {
        printf("\t");
        for(j=0; j<C; j++) {
            printf("|");
            char nextChar = grille[i][j]	;
            if(nextChar == 'X') red();
            else if (nextChar == 'O') yellow();
            printf("%c",nextChar);
            reset();
        }
        printf("|\n");
    }
    printf("\t 1 2 3 4 5 6 7 \n");
}

//**************** Helper functions when the computer turn comes *******************************

// retourner l'�tat de la grille (valeur) pass�e en param�tre apr�s avoir fait le coup (i,j) 
// c'est l'�quivalent de la fonction d'�valuation en AI 
// cependant , c'est nous qui l'a con�ue nous m�me !!!!!!!
int CalculValue(int i,int j, char a,char grilleTemporaire[L][C]) {
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
// retourner les meilleur coup de point de vue d'un joueur d�fensive 
int modeDefensive_Moyenne() {
    somme_value_player = 0 ;
    somme_value_opponent = 0;
    int i , j;
    char grilleTemporaire[L][C];
    for(j = 0 ; j <C ; j++) {
        EvaluationTable[j] = 0;
    }
    for(j = 0 ; j <C ; j++) {
    	// coupie 
        creerGrille(grilleTemporaire,grille);
        // s'il y une ligne disponible pour la colonne j 
        if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {
        	// on suppose on a fait ce  coup 
            grilleTemporaire[i][j]	= X ;
            // on note l'�tat de la grille apr�s le coup ( le gain) 
            somme_value_player = CalculValue(i,j,X,grilleTemporaire);
            // coupie encore une fois
            creerGrille(grilleTemporaire,grille);
            // on suppose que l'adversaire a fait ce coup 
            grilleTemporaire[i][j]	= O ;
            // on note l'�tat de la grille apr�s le coup ( la perte) 
            somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
            // apr�s plusieur essai avec plusieurs proportions  on a trouv� que c'est la meilleure formmule avec un mode d�fensive (r�sultat empirique)
            EvaluationTable[j] = (int) ( 0.4 *somme_value_player )+  somme_value_opponent ;
        }
    }
    // On retourne les meilleur coup qui va nous �chappe l'�chec
    return maxTable(EvaluationTable,C);

}
// la m�me d�marche que le mode d�fensive , sauf au niveau de la formule ou on favorise le gain du match plus que le fait de s'�chapper � la perte 
int modeOffensive_Moyenne() {
    somme_value_player = 0 ;
    somme_value_opponent = 0;
    int i , j;
    char grilleTemporaire[L][C];
    for(j = 0 ; j <C ; j++) {
        EvaluationTable[j] = 0;
    }
    for(j = 0 ; j <C ; j++) {
        creerGrille(grilleTemporaire,grille);
        if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {
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
// cette fonction nous permettra de savoir l'�tat de la grille apr�s que l'oppos� fasse le meilleur coup (the worst situation) 
int oppositeScenario(char grille[L][C]) {
    somme_value_player = 0 ;
    somme_value_opponent = 0;
    int i , j;
    char grilleTemporaire[L][C];
    for(j = 0 ; j <C ; j++) {
        TableOfOppositeScenario[j] = 0;
    }
    creerGrille(grilleTemporaire,grille);
    for(j = 0 ; j <C ; j++) {
        if((i =CurrentLine(j,grilleTemporaire)) >= 0 ) {
            grilleTemporaire[i][j]	= O ;
            somme_value_opponent = CalculValue(i,j,O,grilleTemporaire);
            grilleTemporaire[i][j]	= ' ';
            TableOfOppositeScenario[j] =  somme_value_opponent ;
        }
        else TableOfOppositeScenario[j] =0 ;

    }
    return  maxValueOfTable(TableOfOppositeScenario,C);

}
// ***********methods more related to AI : minamx algorithm **********************
// On a fait toutes ces fonctions nous m�me , apr�s avoir lit des articles vraiment abstraites (qui parlent de l'utilisation g�n�rale de l'algorithme parfois dans le cas de puissance4) sur comment fonctionne l'algorithme minmax 
//Aucune ligne n'est copi� d'une autre source
int finalDepth(char grille[L][C]) {
    char grilleTemporaire[L][C];
    int EvaluationTable[C] ;
    for(j = 0 ; j <C ; j++) {
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
int firstDepth(char grille[L][C], int depth) {
    int i , j ;
    char grilleTemporaire[L][C];
    int EvaluationTable[C] ;
    for(j = 0 ; j <C ; j++) {
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
    // s'il y a une foulie de la part de minmax , on revient au mode offensive 
    if(oppositeScenario(grilleTemporaire) > 5000	) {
        probableColumn = modeOffensive_Moyenne();
    }
    return  probableColumn ;
}
int intermediaiteDepth(char grille[L][C], int depth) {
    char a = (depth%2 != 0) ? X : O;
    int i , j ;
    char grilleTemporaire[L][C];
    int EvaluationTable[C] ;
    for(j = 0 ; j <C ; j++) {
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
int futurDeGrille(char grille[L][C], int depth) {
    if(1<depth && depth < 3)
        return 	intermediaiteDepth(grille, depth);
    else if(depth == 3)
        return finalDepth(grille);
    else
        return	firstDepth(grille, depth);

}
int modeExpert() {
    // premierement on voit si le mode intermediaire peut nous faire gagner ou �viter un �chec afin de ne pas perdre nos efforts
    if(EvaluationTable[modeOffensive_Moyenne()] > 5000) return modeOffensive_Moyenne();
    if(EvaluationTable[modeDefensive_Moyenne()] > 5000) return modeDefensive_Moyenne();
    // apr�s on passe � AI 
    return futurDeGrille(grille, 1);
}
// l'ordinateur fait un coup selon le niveau pass� en param�tre 
void computerTurn(int niveau) {
    isFree = 0;
    int j;
    switch(niveau) {
    case 1: {
        srand(time(0));
        j = rand() % 7 ;
        oppositeScenario(grille);
        break;
    }
    case 2:
        j = modeDefensive_Moyenne();
        break;
    case 3:
        j =modeOffensive_Moyenne();
        break;
    case 4:
        j =modeExpert();
        break;
    }

    i= L-1;
    while(isFree == 0 && i >= 0 ) {

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
// On demande au joueur de saisir une colonne disponible et valide
void demandeAuJoueur(char a) {
    blue();
    isFree = 0;
    printf("joueur %c entrez le numero de la colonne \n",a);
    scanf("%d",&j);
    system("cls");
    j--;
    if(j>=0 && j<C) {
        i= L-1;
        while(isFree == 0 && i >= 0 ) {

            if(grille[i][j]==' ')
                isFree = 1;
            else
                i--;
        }

    }
    if( isFree == 0) {
    	// la colonne n'est pas valide
        printf("\033[1;31m");
        printf("Ce coup n'est pas valide !!! \n");
        reset();
        demandeAuJoueur(a);
    }
    else
        grille[i][j]= a ;
    reset();
    // voir si ce joueur est un winner
    if(isThere_Winner(a,i,j,grille) == 1) {
        isWinner = 1 ;
        printf("\033[1;32m");
        printf(" \n 	Le	 joueur %c 	a	 gagn� 	!	!	! \n",a);
        reset();

    }
}
void initialization() {
    //red();
    char entrer =' ';
    clearGrid();
    char answer = 'N';
    int loadType ;
    system("cls");
    if( isBeginingOfGame == 1) {
        red();
        printf("\n\n\n\t\t		Bienvenue � Puissance4  \n\n\n ");
        printf("\n 				click Entrer  pour continuer  ");

        while ( entrer!= '\n' ) {
            scanf("%c",&entrer);
        }
        system("cls");
        do {
            red();
            printf("\n\n\n			Est ce que vous avez d�j� enregistrer une version du jeu 'O'/'N'\n");
            reset();
            scanf("%c", &answer);
        } while(answer != 'O' && answer != 'N');
        if(answer == 'O') {
            do {
                system("cls");
                green();
                printf( "\n\n veuillez choisir le type de chargement  :\n");
                printf("\n\n \t  1-Charger tous les donn�es( le point ou je me suis arr�t�) 					2-Charger seulement les infos importantes (id , name et score) \n");
                reset();
                scanf("%d", &loadType);
            } while(loadType != 1 && loadType != 2);
        }
    }
    if(answer == 'N' || loadType == 2) {
        if(isBeginingOfGame == 1) {
            if(answer =='N') createNewPlayer();
            else loadPlayer();
        }
        do {
            system("cls");
            blue();
            printf("\n		Bonjour %s     votre score est %d , Pret  a commancer un nouveau jeu !! \n\n", currentPlayer.name, currentPlayer.score );
            delay(500);
            green();
            printf( "\n\n veuillez choisir le mode du jeu :\n");
            printf("\n\n \t  1-Mode un seul joueur 					2-Mode deux joueur \n");
            reset();
            scanf("%d",&mode);
        }
        while(mode != 1 && mode !=2);
    }
    else {
        loadPlayerWithAllData();
    }
    isBeginingOfGame = 0 ;
    //system("cls");
}
void playWithTheComputer(int niveau) {
    green();
    printf("			Vous etes le joueur : O \n");
    printf("\n			OK ! LET'S GET STARTED !!!!");
    reset();
    delay(1000);
    while(grillePleine() == 0 ) { // la boucle se r�p�te tant que la grille est pleine
        computerTurn(niveau);
        affichage();
        //
        // si le joureur l'ordinateur  a gagn� on arrete le jeu
        if(isWinner == 1) {
        	clearGrid();
        	saveAllPlayerData(0, niveau , grille);
            playerState(-1);
            return;
        }
        delay(500);
        demandeAuJoueur(O);
        affichage();
        // on enregistre le jeu avant le prochain coup du joueur
        saveAllPlayerData(0, niveau , grille);
        // si le joureur O  a gag	n� on arrete le jeu
        if(isWinner == 1) {
        	clearGrid();
            saveAllPlayerData(10 * niveau, niveau , grille);
            playerState(1);
            return;
        }
        delay(500);
        system("cls");
    }
    // si la grille est pleine on dit que le match est nul
    if(grillePleine() == 1 ) {
    	clearGrid();
        saveAllPlayerData(10, niveau , grille);
        printf("le match est NULLLL ");
        playerState(0);
    }
}
void modeSeulJoueur() {
    do {
        system("cls");
        green();
        printf( " veuillez choisir le niveau du jeu :\n");
        printf("\n\t\t\t\t\t\t 1- DEBUTANT\t\t    * \n\n				\t	2- INTERMEDIAIRE_DEFENSIVE  **\n\n	\t				3- INTERMEDIAIRE_OFFENSIVE  ***\n\n\t	\t\t\t	 4- EXPERT    \t\t**** \n");
        reset();
        scanf("%d",&niveau);
    }
    while(niveau != 1 && niveau !=2 && niveau != 3 &&niveau != 4);
    system("cls");
    playWithTheComputer(niveau);
}
void modeDeuxJoueur() {
    green();
    printf("%s : X \n", currentPlayer.name);
    printf("joueur2 : O \n");
    reset();
    affichage();
    delay(400);
    while(grillePleine() == 0 ) { // la boucle se r�p�te tant que la grille n'est pas pleine
        demandeAuJoueur(X);

        affichage();
        // si le joureur X  a gagn� on arrete le jeu
        if(isWinner == 1) {
            savePlayerData(20);
            playerState(1);
            return;
        }
        delay(400);
        demandeAuJoueur(O);

        affichage();
        // si le joureur O  a gagn� on arrete le jeu
        if(isWinner == 1) {
            savePlayerData(0);
            playerState(-1);
            return;
        }
        delay(400);
    }
    // si la grille est pleine on dit que le match est nul
    if(grillePleine() == 1 ) {
        green();
        printf("le match est NULLLL ");
        savePlayerData(10);
        playerState(0);
        reset();
    }
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	// creating files if they don't exist
	FILE* fileTemp = fopen("D:\\Elearning\\info\\Puissance4\\TemporaryFile.txt", "a+");
    file = fopen("D:\\Elearning\\info\\Puissance4\\fichier.txt", "a+");
    fclose(fileTemp);
    fclose(file);
    // initialisation de la grille (not affichage!)
    char tryAgain = 'O';
    do {
        isWinner = 0 ;
        initialization ();
        if(mode == 1) modeSeulJoueur();
        else if(mode == 2) modeDeuxJoueur();
        else playWithTheComputer(currentPlayer.niveau);
        do {
            scanf("%c",&tryAgain);
            printf("\n\nVoulez-vous jouer encore une fois 'O'/'N'\n");
            scanf("%c",&tryAgain);
        } while(tryAgain != 'O' && tryAgain != 'N');
    }
    while(tryAgain == 'O');
    printf(" fin du jeu ");
    return 0;
    // fin du jeu
}
