/*
Sviluppare un programma per l'analisi dei pedaggi monitorati da un
casello autostradale in 24 ore. Le informazioni sul transito delle
vetture, monitorato da una batteria di 10 caselli, sono salvate in un
file di testo in cui ogni riga contiene le seguenti informazioni:

- Numero casello (da 0 a 9)
- Orario (formato (hh:mm:ss)
- Tipo vettura (es., "autovettura", "autobus", "autocarro","autotreno", "motoveicolo")
- Località di ingresso ("messina", "roccalumera", "taormina", "giardini_naxos", "fiumefreddo", "giarre", "acireale")

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di transito relative al casello numero 'i'. 
La funzione restituisce il numero totale di transiti.

2) CalcolaPedaggi: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il costo totale dei pedaggi rilevato
dal casello numero i. Si assuma per semplicità che il costo del
pedaggio sia indipendente dal tipo di vettura. Si assumino i seguenti
costi in euro dei pedaggi:

Casello di ingresso | Costo pedaggio (Euro)
messina               4,00
roccalumera           3,00
taormina              2,00
giardini_naxos        1,50
fiumefreddo           1,20
giarre                0,70
acireale              0,50

3) VisualizzaPercentualeAuto: Visualizza, per ogni casello, la
percentuale di autovetture transitate sul totale delle vetture
transitate da quel casello.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NUM_CASELLI 10
#define NOME_FILE "transiti.txt"

// STRUTTURE DATI
typedef struct Transito{
  char orario[16];
  char tipo_vettura[16];
  char ingresso[32];
} TTransito;

typedef struct NodoTransito{
  TTransito transito;
  struct NodoTransito *succ;
} TNodoTransito;

typedef TNodoTransito *PNodoTransito;


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
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di transito relativi al casello numero 'i'. 
La funzione restituisce il numero totale di transiti.

Parametri: nome del file, array di liste di transiti 
Restituisce: il numero totale di transiti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char *nome_file, PNodoTransito *transiti){
  // Implementare il corpo della funzione
  FILE *fp;
  fp = fopen(nome_file,"r");
  if(fp == NULL){
  	printf("Errore! Il FILE cercato NON ESISTE!");
  	return -1;
  }
  TTransito transito;
  int cont_transiti = 0;
  int num_parametri = 0;
  int num_casello;
  int status;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %s %s %s", &num_casello, transito.orario, transito.tipo_vettura, transito.ingresso);
  	if(num_parametri == 4){
  		status = AggiungiTransito(&transiti[num_casello], transito);
  		if (status == 1)
  			cont_transiti++;
	  }else{
	  	printf("Errore! Il File non e' stato caricato correttamente");
	  	return -1;
	  }
  }
  fclose(fp);
  return cont_transiti;
}

/*
2) CalcolaPedaggi: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il costo totale dei pedaggi
rilevato dal casello numero i. Si assuma per semplicità che il
pedaggio sia indipendente dal tipo di vettura. Si assumino i seguenti
costi in euro dei pedaggi:

Casello di ingresso | Costo pedaggio (Euro)
messina               4,00
roccalumera           3,00
taormina              2,00
giardini_naxos        1,50
fiumefreddo           1,20
giarre                0,70
acireale              0,50

Parametri: fascia oraria (orario inizio e orario fine), array di liste
Restituisce un array con il totale dei dei costi di pedaggio rilevati
in ogni casello
*/
float *CalcolaPedaggi(PNodoTransito *transiti, char *orario_inizio, char *orario_fine){
  // Implementare il corpo della funzione
  float *vett_pedaggi;
  PNodoTransito t;
  
  vett_pedaggi = (float*)malloc(NUM_CASELLI * sizeof(float));
  
  for(int i=0; i<NUM_CASELLI; i++){
  	t = transiti[i];
  	vett_pedaggi[i] = 0.0;
  	while(t != NULL){
		  if( (strcmp(t->transito.orario, orario_inizio) >= 0) && (strcmp(t->transito.orario, orario_fine) <= 0) ){
			if( (strcmp(t->transito.ingresso, "messina")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 4.00;
  			else if( (strcmp(t->transito.ingresso, "roccolumera")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 3.00;
  			else if( (strcmp(t->transito.ingresso, "taormina")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 2.00;
  			else if( (strcmp(t->transito.ingresso, "giardini_naxos")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 1.50;
  			else if( (strcmp(t->transito.ingresso, "fiumefreddo")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 1.20;
  			else if( (strcmp(t->transito.ingresso, "giarre")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 0.70;
   			else if( (strcmp(t->transito.ingresso, "acireale")) == 0)
  				vett_pedaggi[i] = vett_pedaggi[i] + 0.50; 				
		}
	 
     t = t->succ;
	}
  }
  return vett_pedaggi;
}

/*
3) VisualizzaPercentualeAuto: Visualizza, per ogni casello, la
percentuale di autovetture transitate sul totale delle vetture
transitate da quel casello.

Parametri: array di liste di transiti
*/
void VisualizzaPercentualeAuto(PNodoTransito *transiti){
  // Implementare il corpo della funzione
  PNodoTransito t;
  int Totale_Vetture;
  int Totale_Autovetture;
  float Percentuale;
  
  for(int i=0; i<NUM_CASELLI; i++){
  	t = transiti[i];
  	Totale_Autovetture = 0;
  	Totale_Vetture = 0;
  	
  	while(t != NULL){
  		Totale_Vetture++;
  		if(strcmp(t->transito.tipo_vettura, "autovettura") == 0){
  			Totale_Autovetture++;
		  }
	    t = t->succ;   
	  }
	Percentuale =( (float)Totale_Autovetture / (float)Totale_Vetture )*100;
	printf("La Percentuale di AutoVetture transitate per il casello %d e': %.2f\n", i, Percentuale);
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

// Visualizza Vettore di Liste
void VisualizzaVettore(PNodoTransito *transiti){
  PNodoTransito t;
  for (int i = 0; i < NUM_CASELLI; i++){
  	t = transiti[i];
  	while(t != NULL){
		printf("%s\t",t->transito.orario);
  		printf("%s\t",t->transito.tipo_vettura);
  		printf("%s\n",t->transito.ingresso);
  		t = t->succ;
	  }
  }
}

int Menu(){
  int scelta;
  
  printf("\n\n*** MENU ***\n"
	 "1. Carica dati\n"
	 "2. Calcola pedaggi\n"
	 "3. Visualizza percentuale auto\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

// MAIN
int main(void){
  // Dichiarare le variabili opportune
  int cont_transiti;
  PNodoTransito vett_transiti[NUM_CASELLI];
  int scelta;
  char ora_inizio[10];
  char ora_fine[10];
  float *Vett_Pedaggi;
  
  for(int i=0; i<NUM_CASELLI; i++){
  	vett_transiti[i] = 0;
  }
   
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaDati
	cont_transiti = CaricaDati(NOME_FILE, vett_transiti);
	if(cont_transiti == -1){
		break;
	}
	printf("\nIl Numero di Transiti TOTALI e': %d",cont_transiti);
	printf("\nIl Vettore di Liste e: \n");
	VisualizzaVettore(vett_transiti);
	break;
	
      case 2:
	// Acquisire la fascia oraria
	// Invocare la funzione CalcolaPedaggi
	// Visualizzare il totale dei pedaggi per ogni casello
	printf("Inserisci la Fascia Oraria.");
	printf("\nInserisci Ora di Inizio: ");
	scanf("%s",ora_inizio);
	printf("Inserisci Ora di Fine: ");
	scanf("%s",ora_fine);
    Vett_Pedaggi = CalcolaPedaggi(vett_transiti, ora_inizio, ora_fine);
    printf("\n\nIl Vettore dei Pedaggi e' il seguente: \n");
	for(int i=0; i<NUM_CASELLI; i++)
		printf("%.2f\n",Vett_Pedaggi[i]);		
	break;

      case 3:
	// Invocare la funzione VisualizzaPercentualeAuto
	VisualizzaPercentualeAuto(vett_transiti);
	break;
      }
  } while (scelta != 0);

  // Disallocare la memoria allocata sfruttando la funzione
  // DisallocaTransiti

  
  return 0;
}
