/*
Gestione di galleria fotografico

Implementare un programma in ANSI C che permette la gestionme di un archivio
di immagini. Il programma carica i dati da un file in una struttura dati organizzata
per tipo in cui le immagini sono inserite in base alla data.
La struttura dati da implementare è una lista di liste ordinate
	
Il programma ha le seguenti funzioni
1. Caricamento dei dati da un file di testo
2. Estrazione delle immagini in base alla data
3. Conteggio delle foto con risoluzione data

I dettagli delle funzioni da realizzare sono descritte nel testo
Lo studente deve implementare quanto non presente senza modificare le funzioni e le
strutture dati gia' presenti. 
*/

// STRINGA VISUAL STUDIO
#define _CRT_SECURE_NO_WARNINGS
 
 // LIBRERIE
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// COSTANTI
#define MAXSTRLEN 128
#define NOME_FILE "archivio.txt"

// STRUTTURE DATI

// LISTA IMMAGINI
typedef struct immagine_s {
	char descrizione[MAXSTRLEN];
	char data[16]; // il formato della data e' AAAA-MM-GG
	int	 dpi;
} immagine_t;

typedef struct nodo_immagine_s {
	immagine_t dato;
	struct nodo_immagine_s *n;
} nodo_immagine_t;
 
typedef nodo_immagine_t *lista_immagine_t;

// LISTA ARCHIVIO 
typedef struct archivio_s {
	char tipo[MAXSTRLEN];
	lista_immagine_t radice;
} archivio_t;

typedef struct nodo_archivio_s {
	archivio_t dato;
	struct nodo_archivio_s *n;
} nodo_archivio_t;

typedef nodo_archivio_t *lista_archivio_t;


// Visualizza Lista di Liste
VisualizzaListaDiListe(lista_archivio_t archivio){
	lista_archivio_t a;
	lista_immagine_t i;
	a = archivio;
	while(a != NULL){
		i = a->dato.radice;
		while( i != NULL){
			printf("%s\t",i->dato.descrizione);
			printf("%s\t",i->dato.data);
			printf("%d\n",i->dato.dpi);
			i = i->n;
		}
		a = a->n;
	}
}

/*
Inserimento non ordinato nella lista delle immagini
Parametri:
 - lista: lista in cui inserire il nuovo elemento
 - immagine: nuova immagine da inserire
Return: 
 - lista aggiornata
*/
lista_immagine_t aggiungi_immagine(lista_immagine_t lista, immagine_t immagine) {
	nodo_immagine_t* aux = NULL;
	aux = (nodo_immagine_t*)malloc(sizeof(nodo_immagine_t));
	if (aux == NULL)
		return lista;
	aux->dato = immagine;
	aux->n = lista;
	return aux;
}

/*
Inserimento non ordinato nell'archivio
Parametri:
 - lista: lista in cui inserire il nuovo elemento
 - tipo: nuovo tipo da inserire
Return:
 - lista aggiornata
*/
lista_archivio_t aggiungi_tipo(lista_archivio_t lista, const char *tipo) {
	nodo_archivio_t* aux = NULL;
	aux = (nodo_archivio_t*)malloc(sizeof(nodo_archivio_t));
	if (aux == NULL)
		return lista;
	strcpy(aux->dato.tipo, tipo);
	aux->dato.radice = NULL;
	aux->n = lista;
	return aux;
}

/*
Inserimento ordinato rispetto alla data nella lista delle immagini
Parametri:
 - lista: lista in cui inserire il nuovo elemento
 - immagine: nuova immagine da inserire
Return:
 - lista aggiornata
*/
lista_immagine_t aggiungi_immagine_inordine(lista_immagine_t lista, immagine_t immagine) {
	// LA FUNZIONE DEVE ESSERE IMPLEMENTATA DALLO STUDENTE
	if (lista == NULL)
		return aggiungi_immagine(lista, immagine);
	if (strcmp(immagine.data, lista->dato.data) < 0)
		return aggiungi_immagine(lista, immagine);
	lista->n = aggiungi_immagine(lista->n, immagine);
	return lista;	
}

/*
Caricamento dei dati da un file
I dati devono essere caricati in base al valore di tipo nella sottolista appropriata
Parametri:
 - archivio: archivio in cui inserire il nuovo elemento
 - nome_file: file che contiene le informazioni
Return:
 - archivio aggiornato
*/

lista_archivio_t cerca(lista_archivio_t archivio, char *tipo){
	lista_archivio_t a;
	a = archivio;
	while(a != NULL){
		if(strcmp(a->dato.tipo, tipo) == 0){
			return a;
		}
		a = a->n;
	}
	return NULL;
}

lista_archivio_t carica(lista_archivio_t archivio, const char *nome_file) {
	// LA FUNZIONE DEVE ESSERE IMPLEMENTATA DALLO STUDENTE
	FILE *fp;
	fp = fopen(nome_file,"r");
	
	if(fp == NULL){
		printf("Errore! File CERCATO NON ESISTENTE!");
		return NULL; 
	}
	
	lista_archivio_t elemento_archivio;
	immagine_t immagine;
	char tipo[10];
	int num_parametri = 0;
	
	while(!feof(fp)){
		num_parametri = fscanf(fp,"%s %s %d %s", immagine.data, immagine.descrizione, &immagine.dpi, tipo);
		if(num_parametri == 4){
			elemento_archivio = cerca(archivio, tipo);
			if(elemento_archivio == NULL){
				archivio = aggiungi_tipo(archivio, tipo);
				elemento_archivio = cerca(archivio, tipo);
			}
			elemento_archivio->dato.radice = aggiungi_immagine_inordine(elemento_archivio->dato.radice, immagine);	
	    }
	}
	fclose(fp);
	return archivio;
}

/*
Funzione che estrare tutte le immagini con la stessa data
Parametro:
 - archivio: l'archivio delle immagine
 - data: data usata per filtrare le immagini
Return:
 - lista non ordinata delle immagini trovate
*/
lista_immagine_t filtro(lista_archivio_t lista, const char *data) {
	// LA FUNZIONE DEVE ESSERE IMPLEMENTATA DALLO STUDENTE
	lista_immagine_t ListaFiltrata = NULL;
	lista_archivio_t archivio;
	lista_immagine_t i;
	archivio = lista;
	while(archivio != NULL){
		i = archivio->dato.radice;
		while(i != NULL){
			if(strcmp(i->dato.data, data) == 0){
				ListaFiltrata = aggiungi_immagine(i, i->dato);
			}
			i = i->n;
		}
		archivio = archivio->n;
	}
	return ListaFiltrata;
}

/*
Conta il numero di foto la cui risoluzione (dpi) e' maggiore di un valore dato
Parametri:
 - archivio: l'archivio da visitare
 - dpi: il valore di soglia (maggiore uguale)
Return:
 - numero dei valori trovati
*/
int conta_immagini(lista_archivio_t archivio, int dpi) {
	// LA FUNZIONE DEVE ESSERE IMPLEMENTATA DALLO STUDENTE
	int num_immagini = 0;
	lista_immagine_t i;
	lista_archivio_t a;
	a = archivio;
	while(a != NULL){
		i = a->dato.radice;
		while(i != NULL){
			if(i->dato.dpi > dpi){
				num_immagini++;
			}
			i = i->n;
		}
		a = a->n;
	}
	return num_immagini;
}

/*
Stampa il contenuto della lista di immagini
*/
void stampa_immagini(lista_immagine_t l) {
	while (l != NULL) {
		printf("%s %s %d\n", l->dato.data, l->dato.descrizione, l->dato.dpi);
		l = l->n;
	}
}

// MAIN
int main(void) {
	lista_archivio_t archivio = NULL;
	lista_immagine_t ListaFiltrata = NULL;
	int scelta;
	char data[15];
	int dpi;
	int num_immagini;
	do {
		printf("\n");
		printf("1. carica i dati da file\n");
		printf("2. stampa il contenuto dell'archivio\n");
		printf("3. stampa tutte foto fatte in una data\n");
		printf("4. conta il numero di foto con vlaori di risoluzione dati\n");

		printf(">>> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 0:
			printf("Uscita\n");
			break;
		case 1: 
			if (archivio != NULL) {
				printf("Archivio gia' caricato\n");
				break;
			}
			// caricare il contenuto nell'archivio	
			archivio = carica(archivio, NOME_FILE);	
			break;
		case 2: 
			// Implementare quanto necessario a stampare il contenuto dell'archivio
			VisualizzaListaDiListe(archivio);
			break;
		case 3:
			// Implementare quanto necessario a richiedere una data, estrarre le immagini
			// con tale data e stamparle su console usando le funzioni richieste
			printf("Inserisci una Data da cercare: ");
			scanf("%s",data);
			ListaFiltrata = filtro(archivio, data);
			printf("\n\nLa Lista Filtrata e': \n");
			stampa_immagini(ListaFiltrata);	
			break;			
		case 4: 
			// Implementare quanto necessario a richiedere la risoluzione e stampare
			// il numero delle immagini maggiori o uguali a detta risoluzione usando le
			// funzioni richieste
			printf("Inserisci un Valore dpi (soglia minima): ");
			scanf("%d",&dpi);
			num_immagini = conta_immagini(archivio, dpi);
			printf("Il Numero di Immagini con dpi maggiori e': %d",num_immagini);		
			break;
		default:
			printf("scelta non valida\n");
			break;
		}
	} while (scelta != 0);
}