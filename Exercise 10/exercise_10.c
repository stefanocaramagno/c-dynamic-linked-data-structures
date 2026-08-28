/*
Sviluppare un programma per l'analisi del transito dei viaggiatori al
controllo passaporti nelle 24 ore. Le informazioni sul transito dei
viaggiatori, monitorato da una batteria di 10 stazioni di controllo,
sono salvate in un file di testo in cui ogni riga contiene le seguenti
informazioni:

- Numero stazione (da 0 a 9)
- Orario (formato hh:mm)
- Nazionalità
- Paese di provenienza

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di transito relative alla stazione di controllo numero
'i'. La funzione restituisce il numero totale di transiti.

2) ContaProvenienze: Data una fascia oraria, ed un paese di
provenienza restituisce un array in cui l'elemento di indice 'i'
contiene il numero di viaggiatori provenienti da un certo paese di
provenienza rilevato dalla stazione di controllo numero i.

3) VisualizzaPercentualeNazionalita: Visualizza, per ogni stazione di
controllo, la percentuale di viaggiatori di una certa nazionalità sul
totale dei viaggiatori transitati da quella stazione di controllo.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // COSTANTI
#define NUM_STAZIONI 10
#define NOME_FILE "transiti.txt"

// STRUTTURA DATI
typedef struct Transito{
  char orario[16];
  char nazionalita[16];
  char paese[16];
} TTransito;

typedef struct NodoTransito{
  TTransito transito;
  struct NodoTransito *succ;
} TNodoTransito;

typedef TNodoTransito *PNodoTransito;

// Stampa L'Array di Liste
void VisualizzaArrayDiListe(PNodoTransito *transiti){
	PNodoTransito t;
	for(int i=0; i<NUM_STAZIONI; i++){
		t = transiti[i];
		while(t != NULL){
			printf("%s\t",t->transito.orario);
			printf("%s\t",t->transito.nazionalita);
			printf("%s\n",t->transito.paese);
			t = t->succ;
		}
	}
}

// Aggiunge un transito alla lista dei transiti, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiTransito(PNodoTransito *plista, TTransito transito){
  PNodoTransito p;

  p = (PNodoTransito)malloc(sizeof(TNodoTransito));
  if (p == NULL)
    return 0;

  p->transito = transito;
  p->succ = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di transito relative alla stazione di controllo numero
'i'. La funzione restituisce il numero totale di transiti.

Parametri: nome del file, array di liste di transiti 
Restituisce: il numero totale di transiti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char *nome_file, PNodoTransito *transiti){
  // Implementare il corpo della funzione
  FILE *fp;
  fp = fopen(nome_file,"r");
  
  if(fp == NULL){
  	printf("Errore! File cercato NON TROVATO!");
  	return -1;
  }
  
  TTransito transito;
  int stazione;
  int num_transiti= 0;
  int num_parametri = 0;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %s %s %s", &stazione, transito.orario, transito.nazionalita, transito.paese);
  	if(num_parametri == 4){
  		if(AggiungiTransito(&transiti[stazione], transito) == 1)
  			num_transiti++;
	    else{
	  	   printf("Errore! File NON Caricato Correttamente!");
	  	   return -1;
	    }
    }
  }
  fclose(fp);
  return num_transiti;  
}

/*
2) ContaProvenienze: Data una fascia oraria, ed un paese di
provenienza restituisce un array in cui l'elemento di indice 'i'
contiene il numero di viaggiatori provenienti da un certo paese di
provenienza rilevato dalla stazione di controllo numero i.

Parametri: fascia oraria (orario inizio e orario fine), paese di
provenienza array di liste 

Restituisce un array con il numero di viaggiatori provenienti da quel
paese di provenienza rilevati in ogni stazione di controllo
*/
int *ContaProvenienze(PNodoTransito *transiti, char *orario_inizio, char *orario_fine, char *paese){
  // Implementare il corpo della funzione
  int *VettProvenienze;
  
  VettProvenienze = (int*)malloc(NUM_STAZIONI *sizeof(int));  
  if (VettProvenienze == NULL){
  	printf("Errore! Vettore non Allocato Correttamente.");
  	return 0;
  }
  
  PNodoTransito t; 
  for(int i=0; i<NUM_STAZIONI; i++){
  	t = transiti[i];
  	VettProvenienze[i] = 0;
  	while(t != NULL){
  		if(strcmp(t->transito.orario, orario_inizio) >= 0 && strcmp(t->transito.orario, orario_fine) <= 0 && strcmp(t->transito.paese, paese) == 0){
  			VettProvenienze[i]++;
		  } 
		t = t->succ;
	    }
  }
  return VettProvenienze;
}

/*
3) VisualizzaPercentualeNazionalita: Visualizza, per ogni stazione di
controllo, la percentuale di viaggiatori di una certa nazionalità sul
totale dei viaggiatori transitati da quella stazione di controllo.

Parametri: array di liste di transiti, nazionalità
*/
void VisualizzaPercentualeNazionalita(PNodoTransito *transiti, char *nazionalita){
  // Implementare il corpo della funzione
  PNodoTransito t;
  int Cont_Transiti_Totale;
  int Cont_Transiti_Naz;
  float Percentuale;
  
  for(int i=0; i<NUM_STAZIONI; i++){
  	Cont_Transiti_Naz = 0;
  	Cont_Transiti_Totale = 0;
  	t = transiti[i];
  	while(t != NULL){
  		Cont_Transiti_Totale++;
  		if(strcmp(t->transito.nazionalita, nazionalita) == 0)
  			Cont_Transiti_Naz++;
  		t = t->succ;
	}
	Percentuale = ( (float)Cont_Transiti_Naz / (float)Cont_Transiti_Totale ) * 100;
	printf("La Percentuale di Viaggiatori di una Nazionalita' rispetto al totale alla STAZIONE n. %d e' %.2f\n", i, Percentuale);
  }
}

//  Disalloca una lista di transiti
void DisallocaTransiti(PNodoTransito transiti){
  PNodoTransito p;
  
  while (transiti != NULL){
      p = transiti;
      transiti = transiti->succ;
      free(p);
    }
}

int Menu(){
  int scelta;
  
  printf("\n\n*** MENU ***\n"
	 "1. Carica dati\n"
	 "2. Conta provenienze\n"
	 "3. Visualizza percentuale nazionalita'\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

// MAIN
int main(void){
  // Dichiarare le variabili opportune
  PNodoTransito transiti[NUM_STAZIONI];
  int num_transiti;
  int scelta;
  char ora_inizio[10];
  char ora_fine[10];
  char paese[10];
  char nazionalita[10];
  int *VettProvenienze;
  
  
  // Inizializzo l'array dei transiti
  for (int i=0; i<NUM_STAZIONI; i++)
    transiti[i] = NULL;

  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	// Invocare la funzione CaricaDati
	num_transiti = CaricaDati(NOME_FILE, transiti);
	if(num_transiti == -1){
		break;
	}
	printf("Il Numero di Transiti e': %d",num_transiti);
	printf("\nIl Vettore di Liste e': \n");
	VisualizzaArrayDiListe(transiti);
	break;

      case 2:
	// Acquisire la fascia oraria ed il paese di provenienza
	// Invocare la funzione ContaProvenienze
	// Visualizzare il totale dei transiti di ogni stazione di controllo
	printf("Inserisci una Fascia Oraria");
	printf("\nInserisci un'Ora di Inizio: ");
	scanf("%s",ora_inizio);
	printf("Inserisci un'Ora di Fine: ");
	scanf("%s",ora_fine);
	printf("Inserisci un Paese di Provenienza: ");
	scanf("%s",paese);
	VettProvenienze = ContaProvenienze(transiti, ora_inizio, ora_fine, paese);
	for(int i=0; i<NUM_STAZIONI; i++){
		printf("Il Numero di Viaggiatori di provenienza: %s alla Stazione n. %d e' %d: \n", paese, i, VettProvenienze[i]);
	}
	break;

      case 3:
	// Invocare la funzione VisualizzaPercentualeNazionalita
	printf("\nInserisci la Nazionalita': ");
	scanf("%s",nazionalita);
	VisualizzaPercentualeNazionalita(transiti, nazionalita);
	break;
      }
  } while (scelta != 0);

  // Disallocare la memoria allocata sfruttando la funzione
  // DisallocaTransiti
  
  return 0;
}
