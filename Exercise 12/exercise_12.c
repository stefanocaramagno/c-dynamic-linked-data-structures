/*
Sviluppare un programma per l'analisi delle spese effettuate dai
clienti di una farmacia in una giornata. Le informazioni delle
spese effettuate dai clienti, monitorate da una batteria di 5 casse,
sono salvate in un file di testo in cui ogni riga contiene le seguenti
informazioni:

- Numero cassa (da 0 a 4)
- Orario (formato (hh:mm)
- Ricetta medica (si/no)
- Scarico fiscale (si/no)
- Totale spesa

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

2) ContaRicette: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il numero di clienti che presentano
la ricetta medica rilevato dalla cassa numero i.

3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti che effettuano lo scarico fiscale sul totale
dei clienti transitati da quella cassa.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NUM_CASSE 5
#define NOME_FILE "acquisti.txt"

// STRUTTURE DATI
typedef struct Acquisto{
  char  orario[16];
  int   ricetta_medica; // 1 = si, 0 = no
  int   scarico_fiscale; // 1 = si, 0 = no
  float totale;
} TAcquisto;

typedef struct NodoAcquisto{
  TAcquisto            acquisto;
  struct NodoAcquisto* succ;
} TNodoAcquisto;

typedef TNodoAcquisto* PNodoAcquisto;


// Aggiunge un acquisto alla lista degli acquisti, restituisce 1 se
// l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiAcquisto(PNodoAcquisto *plista, TAcquisto acquisto){
  PNodoAcquisto p;

  p = (PNodoAcquisto)malloc(sizeof(TNodoAcquisto));
  if (p == NULL)
    return 0;

  p->acquisto = acquisto;
  p->succ = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

Parametri: nome del file, array di liste di acquisti in cassa 
Restituisce: il numero totale di clienti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char *nome_file, PNodoAcquisto *acquisti){
  // Implementare il corpo della funzione
  FILE *fp;
  
  fp = fopen(nome_file,"r");
  if(fp == NULL){
  	printf("Errore! Il File cercato NON ESISTE!");
  	return -1;
  }
  
  TAcquisto acquisto; 
  int num_cassa; 
  int num_clienti = 0;
  int num_parametri = 0;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %s %d %d %f",&num_cassa, acquisto.orario, &acquisto.ricetta_medica, &acquisto.scarico_fiscale, &acquisto.totale);
  	if(num_parametri == 5){
  		if(AggiungiAcquisto(&acquisti[num_cassa], acquisto)!=0){
  			num_clienti++;
		  } else return -1;
  		
	  }else
	  	return -1;
  }
  fclose(fp);
  return num_clienti;
}

/*
2) ContaRicette: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il numero di clienti che presentano
la ricetta medica rilevato dalla cassa numero i.

Parametri: fascia oraria (orario inizio e orario fine), array di liste

Restituisce un array con il numero di clienti che presentano la
ricetta medica rilevati in ogni cassa
*/
int *ContaRicette(PNodoAcquisto *acquisti, char *orario_inizio, char *orario_fine){
  // Implementare il corpo della funzione
  int *vettPunto2;
  vettPunto2 = (int*)malloc(NUM_CASSE * sizeof(int));
  PNodoAcquisto a;
  
  for(int i=0; i<NUM_CASSE; i++){
  	vettPunto2[i] = 0;
  	a = acquisti[i];
  	while(a != NULL){
  		if( strcmp(a->acquisto.orario, orario_inizio) >= 0 && 
		    strcmp(a->acquisto.orario, orario_fine) <= 0 && 
		    a->acquisto.ricetta_medica == 1){	
  			vettPunto2[i]++;
		  }
	    a = a->succ;
	  }
  }
  return vettPunto2;
}

/*
3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti che effettuano lo scarico fiscale sul totale
dei clienti transitati da quella cassa.
*/
void VisualizzaPercentualeClienti(PNodoAcquisto *acquisti){	
  // Implementare il corpo della funzione
  PNodoAcquisto a;
  int cont_persone_scarico_fiscale = 0;
  int cont_persone_totali = 0;
  for(int i=0; i<NUM_CASSE; i++){
  	a = acquisti[i];
    cont_persone_scarico_fiscale = 0;
    cont_persone_totali = 0;
  	while(a != NULL){
  		cont_persone_totali++;
  		if(a->acquisto.scarico_fiscale == 1){
  			cont_persone_scarico_fiscale++;
		  }
		a = a->succ;
	  }	
	printf("Perc delle Persone che eff. lo S. Fiscale in cassa n.:  %d  e' %.2f\n", i, (cont_persone_scarico_fiscale/(float)cont_persone_totali)*100);
  } 
}

//  Disalloca una lista di acquisti
void DisallocaAcquisti(PNodoAcquisto acquisti){
  PNodoAcquisto p;
  while (acquisti != NULL){
      p = acquisti;
      acquisti = acquisti->succ;
      free(p);
    }
}


// Stampa Array di Liste
void VisualizzaVettore(PNodoAcquisto *acquisti){
  PNodoAcquisto a;
  for (int i = 0; i < NUM_CASSE; i++){
  	a = acquisti[i];
  	while(a != NULL){
  		printf("%d\t",i);
		printf("%s\t",a->acquisto.orario);
  		printf("%d\t",a->acquisto.ricetta_medica);
  		printf("%d\t",a->acquisto.scarico_fiscale);
  		printf("%.2f\n",a->acquisto.totale);
  		a = a->succ;
	  }
  }
}
 
int Menu(){
  int scelta;
  
  printf("\n\n*** MENU ***\n"
	 "1. Carica dati\n"
	 "2. Conta ricette\n"
	 "3. Visualizza percentuale clienti\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

// MAIN
int main(void){
  int           scelta, n;
  PNodoAcquisto acquisti[NUM_CASSE];
  int          *totale_ricette;
  char          ora_inizio[16], ora_fine[16];
  
  int num_tot_clienti;
  
  for (int i=0; i<NUM_CASSE; i++)
    acquisti[i] = NULL;

  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	// Invocare la funzione CaricaDati e visualizzare il numero di
	// acquisti effettuati o gli eventuali errori
	num_tot_clienti = CaricaDati(NOME_FILE, acquisti);
	if(num_tot_clienti == -1){
		printf("Errore! File NON Caricato Correttamente!");
		break;
	}
	printf("Il Numero Totale di Clienti e': %d", num_tot_clienti);
	printf("\nIl Vettore caricato e': \n");
	VisualizzaVettore(acquisti);
	break;

      case 2:
	// Acquisire la fascia oraria
	// Invocare la funzione ContaRicette
	// Visualizzare il numeri di acquisti con ricetta medica
	printf("\nInserisci una Fascia Oraria.");
    printf("\nInserisci un'ora di inizio: ");
    scanf("%s",ora_inizio);
    printf("Inserisci un'ora di fine: ");
    scanf("%s",ora_fine);
    totale_ricette = ContaRicette(acquisti, ora_inizio, ora_fine);  
	printf("Il Vettore con il totale degli acquisti con Ricetta Medica e': \n");
	for(int i=0; i<NUM_CASSE; i++){
		printf("%d\n",totale_ricette[i]);
	}
	
	break;

      case 3:
	// Invocare la funzione VisualizzaPercentualeClienti
	VisualizzaPercentualeClienti(acquisti);
	break;
      }
  } while (scelta != 0);

  // Disallocare la memoria
 // DisallocaAcquisti(acquisti);
  return 0;
}
