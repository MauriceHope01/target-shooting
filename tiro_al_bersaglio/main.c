#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n_players 5 //definiamo i 5 players

struct lanciatore  //struct per identificare il tiratore
{
	int player;		//variabile giocatore: i 5 giocatori vanno dal numero 0 al numero 4
	int posizione;      //la variabile punteggio posizionale del bersaglio
	int punteggio;		//questa è la variabile punteggio che viene assegnato ai giocatori
};

void gioco(char a[][5], struct lanciatore tiratore[], int vet[],int n,int m); //function del gioco
void inizio( struct lanciatore tiratore[]); //procedura Inizio
void regole(); //procedura della schermata regole

void main()
{
	int n,m,i;//n = numero di righe del bersaglio, m = numero di colonne del bersaglio, i = contatore
	struct lanciatore tiratore[n_players];
    char a[7][5]={{'1','1','1','1','1'},{'1','2','2','2','1'},{'1','3','3','3','1'},{'1','3','6','3','1'},{'1','3','3','3','1'},{'1','2','2','2','1'},{'1','1','1','1','1'}};//array che permette all'utente di conoscere il valore delle celle
	int vet[5]={0,0,0,0,0}; //vettore che indica le vittorie di 50 turni
	char scelta;//variabile da inserire nello switch per permettere all'utente di selezionare le opzioni
	srand((unsigned int)time(NULL));//funzione usata per generare le 5 posizioni casuali sul bersaglio dopo ogni lancio

	//menù principale del programma dove l'utente dove l'utente seleziona l'opzione
	do
	{

    	printf("BENVENUTI AL TIRO AL BERSAGLIO\n");
    	printf("SCEGLIERE OPZIONE :\n");
    	printf("\n1     - REGOLE GIOCO \n2     - GIOCA ORA \nESC   - ESCI DAL GIOCO\n");

		printf("\n PREMI UN TASTO : ");
    	scelta=getch();
    	system("cls");//istruzione che serve per pulire lo schermo del computer
    	switch(scelta)
    	{	//con 1 vengono visualizzate le regole del gioco
    		case '1':
				system("cls");
				regole();//chiamata alla procedura regole
				system("PAUSE");//mette il sistema in pausa e continuare solo se premuto un tasto da tastiera
				system("cls");
				break;

			//con 2 si inizia il gioco controllando le varie fasi
			case'2':
				system("cls");
				inizio(tiratore);//questa è la chiamata alla procedura inizio per inizializzare a 0 la variabile punteggio e la variabile Giocatore
				gioco(a,tiratore,vet,n,m);//questa è la chiamata alla funzione gioco che ci consente di iniziare i turni e assegnare i punteggi e la vittoria al giocatore o ai giocatori
				printf("\n\n");
				for(i=0;i<5;i++)//ciclo for dove inserito il vettore ci fa capire quale o quali giocatori hanno vinto
				{
					if(vet[i]) printf("	           	VINCE IL GIOCATORE NUMERO %d \n",i);
				}
				system("PAUSE");
				system("cls");
				break;
		}
    fflush(stdin);//pulisce eventuali buff da tastiera
    }
	while(scelta!=27);//27 nel codice ASCII è il tasto ESC

	system("cls");//è un'istruzione che serve per pulire lo schermo del computer
	printf("\n IL GIOCO E' TERMINATO, GRAZIE PER AVER GIOCATO");

}

void gioco(char a[][5],struct lanciatore tiratore[], int vet[],int n,int m)
{
	int turno;//variabile che useremo in un ciclo for
	int i,j;//contatori del numero di righe e colonne del bersaglio

	int pos_max=0; //variabile che serve per assegnare il valore punteggio posizione ai giocatori
	int punt_max=0;
	int player=0; //è un indice
	for(turno=0;turno<50&&punt_max<100;turno++)//ciclo che deve terminare o dopo 50 turni o dopo che uno dei giocatori fa 100 punti
	{
		printf("\n Quando il punteggio posizione vale o 1 o 2, \nil punteggio assegnato al giocatore e' sempre 1.");
		printf("\n\n");

		for(i=0;i<7;i++)//ciclo usato per visualizzare bersaglio 7 x 5
		//Le righe vanno lette dal numero 0 al numero 6 e le colonne dal numero 0 al numero 4)
		{
			for(j=0;j<5;j++)
			{
				printf("[_%c_]",a[i][j]);
			}
			printf("\n");

		}
		//viene stabilito il valore posizionale dei punteggi
		for(player=0;player<5;player++)
		{
			tiratore[player].posizione=0;//inizializziamo a zero la variabile Punteggio_posizione della struct
			n=rand()%7;//genera posizioni casuali da 0 a 6 colonne
			m=rand()%5;//genera posizioni casuali da 0 a 4 righe
			tiratore[player].posizione=a[n][m]-48;//48 è il codice ASCII dello zero
			printf("\n GIOCATORE %d ha colpito la casella nella posizione=[%d][%d]\n",player,n,m);
			printf("GIOCATORE %d ha totalizzato il punteggio: %d\n", player,tiratore[player].posizione);

		}
		//a turni terminati, stabiliamo il vincitore assegnando il valore del "colore" al giocatore che ha buttato la freccetta piu vicina al centro
		pos_max=0;
		for(player=0;player<5;player++)
		{
			if(tiratore[player].posizione>pos_max)
				pos_max=tiratore[player].posizione; //Non conservo la posizione max perche' piu' persone potrebbero fare lo stesso punteggio
		}
		//assegniamo il punto/i ai giocatori vincitori
		for(player=0;player<5;player++)
		{
			if(tiratore[player].posizione==pos_max)
			{
				if(pos_max>=1&&pos_max<=2)tiratore[player].punteggio+=1;//come abbiamo già detto le celle che hanno il valore posizionale di 1 e 2 possono dare solo 1 punto al giocatore che vince il turno
				else tiratore[player].punteggio+=pos_max;//per il resto il valore posizionale coincide con il punteggio assegnato: valore posizionale=3 ->punteggio=3;valore posizionale=6 ->punteggio=6
			}
		}
		//controlla il punteggio massimo totale in ogni turno
		punt_max=-1;
		for(player=0;player<5;player++)
		{
			if(tiratore[player].punteggio>punt_max)
				punt_max=tiratore[player].punteggio;
		}
		printf("\nPUNTEGGIO MAX PER ORA E': %d\n\nNUMERO TURNO :%d", punt_max, turno);
		printf("\n\n------------------------------------------------------------");

	}
	//La posizione del vettore corrisponde al numero di giocatore. il contenuto della posizione del vettore corrisponderà alla vittoria.
		for(player=0;player<5;player++)
		if(tiratore[player].punteggio==punt_max) vet[player]=1;

}


void  inizio(struct lanciatore tiratore[]) //è la procedura che inizializza a zero il punteggio dei giocatori e il numero dei giocatori usando un contatore i che va da 0 a 4 visto che 5 è il numero totale dei giocatori
{
	int i;
	for(i=0;i<n_players;i++)
	{
		tiratore[i].player=i;
		tiratore[i].punteggio=0;
	}
}



void regole() //procedura che mostra le regole del gioco
{
	printf("\n RULES :\n");
	printf("\n* Max 5 giocatori ");
	printf("\n* il primo giocatore che raggiunge 100 pti vince");
	printf("\n* Il gioco finisce dopo 50 turni");
	printf("\n* I punti sono :");
	printf("\n [6 pti per la casella rossa]");
	printf("\n [3 pti per le caselle verdi]");
	printf("\n [1 pt per le caselle arancioni]\n");
	printf("\n");
	printf("\n RICORDA:CHE SE IL PUNTEGGIO E' 1 O 2, AL GIOCATORE VERRA' ASSEGNATO SEMPRE 1PT ");
	printf("\n");
	printf("\n");
	printf("\nBERSAGLIO:\n");
	printf("+-----------------------+\n");
	printf("| 1 || 1 || 1 || 1 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 2 || 2 || 2 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 3 || 3 || 3 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 3 || 6 || 3 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 3 || 3 || 3 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 2 || 2 || 2 || 1 |");
	printf("\n+-----------------------+\n");
	printf("| 1 || 1 || 1 || 1 || 1 |");
	printf("\n+-----------------------+\n");
}
