#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define KEY "Entrez le niveau de difficulte voulu : "

void Facile () ;
void Moyen () ;
void Difficile ();
void difficulte ();

int timeoutgetnb(int* remaining,const char* chaine)
{
    int timeleft;
    char cache[11] = {0};
    int curs = 0;
    time_t starttime = time(NULL);
    printf("\r%s [%d] : %s          ",chaine,*remaining,cache);
    do
    {
        time_t crt = time(NULL);
        if (difftime(crt,starttime)>=1.0)
        {
            starttime = crt;
            (*remaining)--;
            printf("\r%s [%d] : %s          ",chaine,*remaining,cache);
        }
        if (_kbhit())
        {
            char c = (char)getch();
            if (c>='0' && c<='9' && curs<10)
                cache[curs++] = c;
            if (c==0x0D)
            {
                printf("\n");
                return atoi(cache);
            }
            if (c=='\b' && curs!=0)
                cache[--curs] = '\0';
            printf("\r%s [%d] : %s          ",chaine,*remaining,cache);
        }
    } while ((*remaining)>0);
    printf("\n");
    return -1;
}

int s=0;
int puissance(int x, int y)
{
    int i, resultat;
    resultat = 1;

    for (i=1; i<= y; i++)
    {

        resultat = resultat * x;
    }

    return resultat;
}
int main()
{
    int X=1;
    int difficulty;
    difficulte();

    while(X)
    {
        printf("\n");
        printf("%s  ", KEY);

        difficulty=getche();

        switch(difficulty)
        {
        case '1':
            Facile();
            break;

        case '2':
            Moyen();
            break;

        case '3':
            Difficile();
            break;
            difficulte();
        }
    }
}

void difficulte()
{
    printf("Entrer 1 pour le niveau de difficulte Facile \n");
    printf("Entrer 2 pour le niveau de difficulte Moyen  \n");
    printf("Entrer 3 pour le niveau de difficulte Difficile \n");
}

void addition1(i) {
    int k = 1 ;
    int nb1,nb2,res,rep,delay;
    int t=20;
    printf("Bienvenu au niveau de difficulte Facile, commençons par l'addition \n");
    do {
        srand(time(NULL));
        const int MAX = 10, MIN = 0;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;

        res=nb1+nb2;
        printf("répondez à cette question : %d + %d = ?\n",nb1,nb2);
        delay = 5*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s= s+1 ;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {



            s=s;
            printf("votre réponse est fausse. votre score est %d \n",s);

        }
	k++ ;
    }
    while  (k<=3);
}


void soustraction1(i ) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la deuxième difficulté du niveau , passons à la soustraction\n");
    do {
        srand(time(NULL));
        const int MAX = 10, MIN = 0;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;
        res=nb1-nb2;
        printf("répondez à cette question : %d - %d = ?\n",nb1,nb2);
        delay = 7*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);
        }
        k++ ;
    }
    while  (k<=3);
}

void multiplication1(i ) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la dernière difficulté du niveau , passons à la multiplication \n");
    do {
        srand(time(NULL));
        const int MAX = 10, MIN = 0;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;

        res=nb1*nb2;
        printf("répondez à cette question : %d * %d = ?\n",nb1,nb2);
        delay = 7*(i+2);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);

        }

        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);

        }
		k++ ;
    }
    while  (k<=3);
}



void addition2 (i) {
    int k = 1 ;
    int nb1,nb2,res,rep,delay;
    int t=20;
    printf("Bienvenu au niveau de difficulte Moyen, commençons par l'addition \n");
    do {
        srand(time(NULL));
        const int MAX = 100, MIN = 10;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;

        res=nb1+nb2;
        printf("répondez à cette question : %d + %d = ?\n",nb1,nb2);
        delay = 5*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s= s+1 ;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {



            s=s;
            printf("votre réponse est fausse. votre score est %d \n",s);

        }

    }
    while  (k<=3);
}


void soustraction2 (i ) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la deuxième difficulté du niveau , passons à la soustraction\n");
    do {
        srand(time(NULL));
        const int MAX = 100 , MIN = 10;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;
        res=nb1-nb2;
        printf("répondez à cette question : %d - %d = ?\n",nb1,nb2);
        delay = 7*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);
        }
    }
    while  (k<=3);
}

void multiplication2 ( i) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la dernière difficulté du niveau , passons à la multiplication \n");
    do {
        srand(time(NULL));
        const int MAX =100 , MIN = 10;
        const int max = 10 , min = 1 ;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(max - min + 1)) + min;

        res=nb1*nb2;
        printf("répondez à cette question : %d * %d = ?\n",nb1,nb2);
        delay = 7*(i+2);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);

        }

        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);

        }

    }
    while  (k<=3);
}

void addition3(i) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    int t=20;
    printf("Bienvenu au niveau de difficulte Difficile, commençons par l'addition \n");
    do {
        srand(time(NULL));
        const int MAX = 1000, MIN = 100;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;

        res=nb1+nb2;
        printf("répondez à cette question : %d + %d = ?\n",nb1,nb2);
        delay = 5*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s= s+1 ;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {



            s=s;
            printf("votre réponse est fausse. votre score est %d \n",s);

        }

    }
    while  (k<=3);
}


void soustraction3(i ) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la deuxième difficulté du niveau , passons à la soustraction\n");
    do {
        srand(time(NULL));
        const int MAX = 1000, MIN = 100;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;
        res=nb1-nb2;
        printf("répondez à cette question : %d - %d = ?\n",nb1,nb2);
        delay = 7*(i+1);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);
        }
        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);
        }
    }
    while  (k<=3);
}

void multiplication3( i) {
    int k=1 ;
    int nb1,nb2,res,rep,delay;
    printf("maintenant c'est la dernière difficulté du niveau , passons à la multiplication \n");
    do {
        srand(time(NULL));
        const int MAX = 100, MIN = 10;
        nb1=(rand()%(MAX - MIN + 1)) + MIN;
        nb2=(rand()%(MAX - MIN + 1)) + MIN;

        res=nb1*nb2;
        printf("répondez à cette question : %d * %d = ?\n",nb1,nb2);
        delay = 7*(i+2);  // 20 secondes
        rep = timeoutgetnb(&delay,"Entrez votre réponse");
        if (res==rep) {
            s=s+1;
            printf("BRAVO, votre score est %d passons à la question suivante\n",s);

        }

        else {
            s==s;
            printf("votre réponse est fausse. votre score est %d on vous propose une autre question avec la même difficulté\n",s);

        }

    }
    while  (k<=3);
}

void Facile ()
{
    int i ;
    addition1 (i) ;
    soustraction1 (i);
    multiplication1 (i);
    printf ("Felicitations ! Vous etes arrives a la fin du niveau Facile avec un score de %d \n", s);
}

void Moyen ()
{
    int i ;
    addition2 (i) ;
    soustraction2 (i);
    multiplication2 (i);
    printf ("Felicitations ! Vous etes arrives a la fin du niveau Moyen avec un score de %d \n", s);
}

void Difficile ()
{
    int i ;
    addition3 (i) ;
    soustraction3 (i);
    multiplication3 (i);
    printf ("Felicitations ! Vous etes arrives a la fin du niveau Difficile avec un score de %d \n", s);
}
