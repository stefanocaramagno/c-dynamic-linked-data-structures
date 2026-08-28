/*
Sviluppare un programma per la gestione dei dati raccolti da 10
stazioni meteorologiche. Ogni stazione è identificata da un codice
numerico (un numero intero compreso tra 0 e 9) e fornisce ad un
concentratore i dati meteo acquisiti. Il concentratore memorizza su un
file di testo le informazioni ricevute dalle stazioni (una riga per
ogni misurazione ricevuta) come di seguito:

- Codice della stazione (numero intero)
- Temperatura giornaliera media (numero intero)
- Temperatura giornaliera massima (numero intero)
- Temperatura giornaliera minima (numero intero)
- Umidità giornaliera media (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)

Implementare le seguenti funzioni:

1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento di indice 'i'
dell'array contiene il puntatore alla lista delle misurazioni
trasmesse dalla stazione di codice 'i'. La funzione restituisce il
numero di misurazioni caricate o -1 in caso di errore durante il
caricamento.

2) MisurazioniStazioneMese: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di una stazione, restituisce la ista
delle misurazioni di quella stazione relative all'anno di riferimento.

3) EscursioneTermica: Dato l'array di liste di misurazioni, ed un anno
di riferimento, restituisce un array in cui l'elemento di posizione
'i' rappresenta l'escursione massima di temperatura giornaliera
rilevata dalla stazione di codice 'i' nell'anno di riferimento. Se una
generica stazione non ha effettuato misurazioni nell'anno di
riferimento, restituisce -1.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NUM_STAZIONI 10
#define NOME_FILE "misurazioni.txt"

// STRUTTURE DATI
typedef struct Misurazione{
  int  temp_media;
  int  temp_min;
  int  temp_max;
  int  umidita;
  char data[16];
} TMisurazione;

typedef struct NodoListaMisurazioni{
  TMisurazione misurazione;
  struct NodoListaMisurazioni *succ;
} TNodoListaMisurazioni;

typedef TNodoListaMisurazioni *PNodoListaMisurazioni;


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaMisurazioni(PNodoListaMisurazioni lista){
  printf("temp_media temp_min temp_max umidita data\n");
  while (lista != NULL){
      printf("%d %d %d %d %s\n", lista->misurazione.temp_media,
	     lista->misurazione.temp_max, lista->misurazione.temp_min,
	     lista->misurazione.umidita, lista->misurazione.data);
      lista = lista->succ;
    }
}

// Aggiunge una misurazione alla lista di misurazioni, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiMisurazione(PNodoListaMisurazioni *plista, TMisurazione misurazione){
  
  PNodoListaMisurazioni p;

  p = (PNodoListaMisurazioni)malloc(sizeof(TNodoListaMisurazioni));
  if (p == NULL)
    return 0;

  p->misurazione = misurazione;
  p->succ = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento di indice 'i'
dell'array contiene il puntatore alla lista delle misurazioni
trasmesse dalla stazione di codice 'i'. La funzione restituisce il
numero di misurazioni caricate o -1 in caso di errore durante il
caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisurazioni(char *nome_file, PNodoListaMisurazioni *stazioni){
  // implementazione a cura dello studente
  FILE *fp;
  fp = fopen(nome_file,"r");
  if(fp == NULL){
  	printf("Errore! File cercato NON TROVATO");
  	return -1;
  }
  
  TMisurazione misurazione;
  int num_parametri = 0;
  int codice;
  int num_misurazioni = 0;

  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %d %d %d %d %s",&codice, &misurazione.temp_media, &misurazione.temp_max, &misurazione.temp_min, &misurazione.umidita, misurazione.data);
  	if(num_parametri == 6){
  		if(AggiungiMisurazione(&stazioni[codice], misurazione) == 1)
  			num_misurazioni++;
	    else{
	  		printf("Errore! File NON Caricato Correttamente!");
	  		return -1;
	    }
    }
  }
  fclose(fp);
  return num_misurazioni;
}

/*
2) MisurazioniStazioneMese: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di una stazione, restituisce la lista
delle misurazioni di quella stazione relative all'anno di riferimento.

Parametri: array di liste di misurazioni, anno di riferimento, numerostazione 
Restituisce: Lista di misurazioni della stazione nell'anno di riferimento
*/
PNodoListaMisurazioni MisurazioniStazioneMese(PNodoListaMisurazioni *stazioni, char *anno, int num_stazione){
  // implementazione a cura dello studente
  PNodoListaMisurazioni listaPunto2 = NULL;
  PNodoListaMisurazioni st;
  
  st = stazioni[num_stazione];
  while(st != NULL){
  	if(strncmp(anno, st->misurazione.data, 4) == 0){
  		AggiungiMisurazione(&listaPunto2, st->misurazione);
	  }
  	st = st->succ;
  }
  return listaPunto2;
}

/*
3) EscursioneTermica: Dato l'array di liste di misurazioni, ed un anno
di riferimento, restituisce un array in cui l'elemento di posizione
'i' rappresenta l'escursione massima di temperatura giornaliera
rilevata dalla stazione di codice 'i' nell'anno di riferimento. Se una
generica stazione non ha effettuato misurazioni nell'anno di
riferimento, restituisce -1.

Parametri: array di liste di misurazioni, anno di riferimento
Restituisce: array delle escursioni termiche per ogni stazione
nell'anno di riferimento
*/
int *EscursioneTermica(PNodoListaMisurazioni *stazioni, char *anno){
  // implementazione a cura dello studente
  PNodoListaMisurazioni st;
  
  int *vettPunto3;
  
  vettPunto3 = (int*)malloc(NUM_STAZIONI * sizeof(int));
  if(vettPunto3 == NULL){
  	printf("Errore! Vettore non Allocato Correttamente.");
  	return 0;
  }
  
  int esc;
  for(int i=0; i<NUM_STAZIONI; i++){
  	st = stazioni[i];
  	int escursione = 0;
  	while(st != NULL){
  		if(strncmp(anno, st->misurazione.data, 4) == 0){
  			esc = st->misurazione.temp_max - st->misurazione.temp_min;
  			if(esc > escursione)
  				escursione = esc;  
		  }
		st = st->succ;
	}
	vettPunto3[i] = escursione;
  }
  return vettPunto3;
  
}

//  Disalloca una lista di misurazioni
void DisallocaMisurazioni(PNodoListaMisurazioni misurazioni){
  PNodoListaMisurazioni p;
  
  while (misurazioni != NULL){
      p = misurazioni;
      misurazioni = misurazioni->succ;
      free(p);
    }
}

// Disalloca le liste nell'array di liste
void DisallocaStazioni(PNodoListaMisurazioni *stazioni){
  // implementazione a cura dello studente (suggerimento: sfruttare la
  // funzione DisallocaMisurazioni)
}


// Visualizza L'Array di Liste delle Stazioni
VisualizzaArrayDiStazioni(PNodoListaMisurazioni *stazioni){
	PNodoListaMisurazioni st;
	for(int i=0; i<NUM_STAZIONI; i++){
		st = stazioni[i];
		while(st != NULL){
			printf("%d\t",st->misurazione.temp_media);
			printf("%d\t",st->misurazione.temp_max);
			printf("%d\t",st->misurazione.temp_min);
			printf("%d\t",st->misurazione.umidita);
		    printf("%s\n",st->misurazione.data);
		    st = st->succ;
		}
	}
}

int Menu(){
  int scelta;
  
  printf("\n\n*** MENU ***\n"
	 "1. Carica misurazioni\n"
	 "2. Misurazioni stazione mese\n"
	 "3. Escursione termica\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

// MAIN
int main(void){
  int scelta;
  
  /* dichiarare le altre variabili necessarie */
  PNodoListaMisurazioni stazioni[10];
  int num_misurazioni;
  char anno[10];
  int num_stazione;
  PNodoListaMisurazioni listaPunto2 = NULL;
  int *vettPunto3;
  
  for(int i=0; i<NUM_STAZIONI; i++){
  	stazioni[i] = 0;
  }
  
  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	// Invocare la funzione CaricaMisurazioni e visualizzare il
	// numero totale di misurazioni acquisite od un messaggio di
	// errore in caso di errore durante il caricamento
	num_misurazioni = CaricaMisurazioni(NOME_FILE, stazioni);
	if(num_misurazioni == -1)
		break;
	printf("\nIl Numero Totale d Misurazione e': %d", num_misurazioni);
	printf("\nL'Array di Liste di Misurazioni e' \n");
	VisualizzaArrayDiStazioni(stazioni);	
	break;

      case 2:
	// Acquisire l'anno ed il numero della stazione, invocare la
	// funzione MisurazioniStazioneMese e visualizzare la lista
	// delle misurazioni restituita dalla funzione
	printf("Inserisci un Anno: ");
	scanf("%s",anno);
	printf("Inserisci un Numero della Stazione: ");
	scanf("%d",&num_stazione);
	listaPunto2 = MisurazioniStazioneMese(stazioni, anno, num_stazione);
	printf("La Lista degli Elementi trovati con questi dati e': \n");
	VisualizzaMisurazioni(listaPunto2);	
	break;

      case 3:
	// Acquisire l'anno, invocare la funzione EscursioneTermica e
	// visualizzare l'array delle escursioni massime restituito
	// dalla funzione
	printf("Inserisci un Anno: ");
	scanf("%s",anno);	
	vettPunto3 = EscursioneTermica(stazioni, anno);
	for(int i=0; i<NUM_STAZIONI; i++){
		printf("L'escursione massima di temperatura giornaliera rilevata dalla stazione n. %d e': %d\n",i, vettPunto3[i]);
	}
	break;
      }
  } while (scelta != 0);

  // DisallocaStazioni(/* parametri */);
  
  return 0;
}
