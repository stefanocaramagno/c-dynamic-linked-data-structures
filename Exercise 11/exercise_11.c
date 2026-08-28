/*
In un file solo contenuti i dati relativi ai risultati di una gara podistica 
a cui partecipano diversi atleti suddivisi in diverse categorie.

Le categorie previste sono le seguenti
ASSOLUTI
JUNIORES
RAGAZZI

Nel file sono contenuti i seguenti dati per ciascun atleta:
numero   nome  cognome  categoria  tempo

Il numero identifica l'atleta, nome e cognome sono stringhe senza caratteri 
bianchi, categoria è una stringa che puo avere solo i valori ASSOLUTI, JUNIORES, 
RAGAZZI (altri valori sono non validi) e il tempo è espresso in secondi.

Nel file i diversi atleti sono ordinati rispetto all'ordine di arrivo, cioe 
la prima riga contiene l'atleta che ha concluso la prova nel tempo più breve 
e cosi via.

Scrivere un programma che carichi le classifiche in un vettore di code in cui 
ogni elemento del vettore contiene la classifica di una categoria.

Le funzioni da sviluppare sono le seguenti:
  1. caricamento del file in un vettore di code, in cui ciascun elemento contiene la classifica di una categoria
  2. calcolo e stampa a video del tempo medio per ciascuna categoria
  3. funzione che dato un cognome restituisce in una lista i dati degli atleti (numero , cognome, nome , tempo) con quel cognome.
  4. funzione che salva le classifiche di una categoria ricevuta in input. Il nome del file sara uguale al nome della categoria.
*/

// STRINGA VISUAL STUDIO
#define _CRT_SECURE_NO_WARNINGS

// COSTANTI
#define length 32
#define NOME_FILE "dati.txt"

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUTTURA DATI

// Definizione del Punto
typedef struct punto_c {
	int numero;
	char nome[length], cognome[length];
	int tempo;
} atleta;

// Definizione del Nodo della Coda
typedef struct nodo_atleta {
	atleta a;
	struct nodo_atleta* successivo;
} nodo_atleta;

typedef nodo_atleta *nodo_atleta_pt;

// Definizione della Coda che rappresenta la Classifica
typedef struct classifica_s {
	nodo_atleta_pt primo, ultimo;
} classifica;


// Funzioni di servizio

// Calcolo delll'indice del vettore dal nome categoria e viceversa
int categoriaToindice(char *categoria){
    //la funzione torna -1 se la categoria non è valida
    if (strcmp (categoria, "ASSOLUTI")==0) return 0;
    if (strcmp (categoria, "JUNIORES")==0) return 1;
    if (strcmp (categoria, "RAGAZZI")==0) return 2;
    return -1;
}

char *indiceToCategoria(int i){
    switch (i) {
        case 0: return "ASSOLUTI"; 
        case 1: return "JUNIORES";
        case 2: return "RAGAZZI";
    }
}

// Funzioni per la gestione delle classifiche 
nodo_atleta_pt aggiungi_atleta(classifica *pc, atleta A) {
	nodo_atleta_pt nuovo_nodo = (nodo_atleta_pt)malloc(sizeof(nodo_atleta));
	if (nuovo_nodo == 0)
		return NULL;
	nuovo_nodo->a = A;
	nuovo_nodo->successivo = NULL;
	if (pc->primo== NULL)
		pc->primo = pc->ultimo = nuovo_nodo;
	else {
		pc->ultimo->successivo = nuovo_nodo;
		pc->ultimo = nuovo_nodo;
	}
	return nuovo_nodo;
}

// Inserimento lista atleti
int inserisci_lista (nodo_atleta_pt *p, atleta A){
    nodo_atleta_pt nuovo_nodo = (nodo_atleta_pt)malloc(sizeof(nodo_atleta));
	if (nuovo_nodo == 0)
		return 0;
	nuovo_nodo->a = A;
	nuovo_nodo->successivo = *p;
	*p = nuovo_nodo;
	return 1;
}

// Stampa lista atleti
void stampaL(nodo_atleta_pt L, FILE *fp){
    while(L!=NULL) {
        fprintf(fp, "\nnome = %s, cognome = %s, tempo =%d", L->a.nome,L->a.cognome,L->a.tempo);
        L = L->successivo;
    }
}

// Lo studente definisca la struttuta dati che implementa l'archivio

/*
Questa funzione deve essere implementata dallo studente
Carica i dati dai file predefiniti nella struttura dati 
La funzione deve escludere gli atleti la cui categoria non è corretta

Return:
0 : in caso di fallimento
1 : in caso di successo
*/
int carica_classifiche(char *nomefile, classifica *C){
	FILE *fp;
	fp = fopen(nomefile,"r");
	int status = 0;
	if(fp == NULL){
		printf("Errore! Il FILE cercato NON ESISTE!");
		return status;
	}
	atleta A;
	char categoria[15];
	int num_parametri = 0;
	int indice;
	nodo_atleta_pt elemento;
	
	while(!feof(fp)){
		num_parametri = fscanf(fp,"%d %s %s %s %d",&A.numero, A.nome, A.cognome, categoria, &A.tempo);
		if(num_parametri == 5){
			indice = categoriaToindice(categoria);
			elemento = aggiungi_atleta(&C[indice], A);
		}else{
			printf("Errore! File non caricato correttamente!");
			return status;
		}
	}
	fclose(fp);
	return 1;
}

/*
la funzione calcola la media del tempo di ciascuna categoria e ritorna 
queste informazioni in un vettore passato come parametro
*/
void calcoloMedia(float *media, classifica *C){
  // Questa funzione deve essere implementata dallo studente  
  nodo_atleta_pt coda;
  int Somma;  
  float Media = 0;
  int numero_nodi;

  for(int i=0; i<3; i++){
	coda = C[i].primo;
	Somma = 0;
	numero_nodi=0;
  	while(coda != NULL){
  		Somma = Somma + coda->a.tempo;
  		numero_nodi++;
  		coda = coda->successivo;
	  }
	  Media = (float)Somma / (float)numero_nodi;
	  media[i] = Media;
  }
}

/*
Funzione che dato un cognome restituisce in una lista i dati 
(numero   nome  cognome  categoria  tempo) di tutti i concorrenti con quel cognome
*/
void inserisci(nodo_atleta_pt *l, nodo_atleta_pt pa, char *cognome){
    nodo_atleta_pt temp = pa;
    while (temp!= NULL) {
        if (strcmp(temp->a.cognome,cognome)==0) inserisci_lista(l,temp->a);
        temp = temp->successivo;
    }
}

nodo_atleta_pt cercaConcorrenti(classifica *C, char *cognome) {
	// Questa funzione deve essere implementata dallo studente
	nodo_atleta_pt ListaCognome = NULL;
	nodo_atleta_pt c;
	
	for(int i=0; i<3; i++){
		c = C[i].primo;
		while(c != NULL){
			if(strcmp(c->a.cognome, cognome) == 0){
				inserisci(&ListaCognome, c, cognome);
			}
			c = c->successivo;
		}
	}
	return ListaCognome;	
}

// Visualizza Array di Code
void VisualizzaArrayCode(classifica *C){
	nodo_atleta_pt coda;
	for(int i=0; i<3; i++){
		coda = C[i].primo;
		while(coda != NULL){
			printf("%d\t",coda->a.numero);		
			printf("%s\t",coda->a.nome);			
			printf("%s\t",coda->a.cognome);
			printf("%d\n",coda->a.tempo);
			coda= coda->successivo;
		}              
	}
}

// Questa funzione apre il file Uscita e salva la categoria richiaesta
void salva(nodo_atleta_pt l, char *nomefile){
	FILE *f;
	f = fopen(nomefile,"w");
	if(f == NULL){
		printf("Errore! File cercato NON TROVATO");
		return;
	}		
    stampaL(l,f);
    fclose(f);
}

// Stampa Lista Punto 3
void VisualizzaLista(nodo_atleta_pt lista){
	nodo_atleta_pt lis;
		lis = lista;
		while(lis != NULL){
			printf("%d\t",lis->a.numero);		
			printf("%s\t",lis->a.nome);			
			printf("%s\t",lis->a.cognome);
			printf("%d\n",lis->a.tempo);
			lis = lis->successivo;
		}              
}


// MAIN
int main(void) {
	classifica classifiche[3] =  { {NULL, NULL} };
	nodo_atleta_pt lista;
	int indice;
	int scelta;
	
	// Inserire le eventuali dichiarazioni utili al fine di implementare il programma
	int status;
	float vett_media[3];
	char cognome[10];
	nodo_atleta_pt ListaCognome = NULL;
	char categoria[10];
	
	for(int i=0; i<3; i++)
		vett_media[i] = 0;
	
	do {
		printf("\n\n\n1. carica i dati\n");
		printf("2. calcolo del tempo medio per categoria\n");
		printf("3. cerca atleti con un dato cognome\n");
		printf("4. salva la classifica di una categoria classifiche\n");
		printf("0. esci\n");
		printf(">> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 0:
			break;
		case 1:
			// Carica le classifiche sul vettore di coda e stampa le tre classifiche
		    status = carica_classifiche(NOME_FILE, classifiche);
		    if(status == 0){
		    	break;
			}
			VisualizzaArrayCode(classifiche);
			
			break;             
		case 2:		
		    //stampa i tempi medi per ciascuna categoria
		    calcoloMedia(vett_media, classifiche);
		    printf("\nLe Medie di Ogni Categoria sono le seguenti: \n");
		    for(int i=0; i<3; i++){
		    	printf("Categoria %d --> Media: %.2f\n",i+1, vett_media[i]);
			}    
		     break;
			
		case 3: 
		    // inserisci il cognome da cercare    
		    // chiamare la funzione che estrae dalle diverse classifiche i concorrenti con il cognome dato
		    // stampare la lista dei concorrenti 
		    printf("Inserisci Cognome da Cercare: ");
		    scanf("%s",cognome);
		    ListaCognome = cercaConcorrenti(classifiche, cognome);
		    printf("La Lista creata e' \n");
		    VisualizzaLista(ListaCognome);
		     break;
			
		case 4: 
		    // scegliere un categoria
		    // salvare su file la classifica per la categoria selezionata
		    printf("Inserisci una Categoria: ");
			scanf("%s",categoria);
			indice = categoriaToindice(categoria);
			salva(classifiche[indice].primo, categoria);		
		    break;	
		}
	} while (scelta != 0);
}
