/*
Sviluppare un programma per la gestione dei dati raccolti da una rete
di sensori di umidità del terreno e di temperatura in ambto
agricoltura di precisione. Ogni sensore trasmette periodicamente le
seguenti informazioni che sono memorizzate in un file unitamente alla
data e all'orario di ricezione.

- Codice del sensore (numero intero)
- Temperatura attuale (numero intero)
- Umidità attuale (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)
- Orario della misurazione (nel formato hh:mm:ss)

L'area monitorata è suddivisa in 10 sotto-aree ciascuna delle quali è
monitorata da al più 10 sensori. Il codice del sensore identifica
l'area. Es. Sensori con codice da 0 a 9 identificano la prima area,
quelli da 10 a 19 la seconda area, ..., quelli da 90 a 99 la
decima area.

Implementare le seguenti funzioni:

1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento i-esimo dell'array
contiene la lista delle misurazioni dei sensori relativi all'area
i-esima (sensori con codice da i*10 a i*10+10-1). La funzione
restituisce il numero totale di misurazioni caricate o -1 in caso di
errore durante il caricamento.

2) MisurazioniAnno: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di un sensore, restituisce la lista
delle misurazioni di quel sensore relativo all'anno di riferimento.

3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NUM_AREE 10
#define NOME_FILE "misurazioni.txt"

// STRUTTURA DATI
typedef struct Misurazione{
  int  codice;
  int  temperatura;
  int  umidita;
  char data[16];
  char orario[16];
} TMisurazione;

typedef struct NodoListaMisurazioni{
  TMisurazione misurazione;
  struct NodoListaMisurazioni *succ;
} TNodoListaMisurazioni;

typedef TNodoListaMisurazioni *PNodoListaMisurazioni;


// Visualizza una misurazione
void VisualizzaMisurazione(TMisurazione misurazione){
  printf("%d %d %d %s %s\n", misurazione.codice,
	 misurazione.temperatura, misurazione.umidita,
	 misurazione.data, misurazione.orario);
}


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaMisurazioni(PNodoListaMisurazioni lista){
  printf("codice temperatura umidità data orario\n");
  while (lista != NULL){
      VisualizzaMisurazione(lista->misurazione);
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
e le memorizza in un array di liste. L'array è composto da 5
elementi. L'elemento i-esimo dell'array contiene la lista delle
misturazioni dei sensori dal codice i*10 al codice i*10+10-1. La
funzione restituisce il numero totale di misurazioni caricate o -1 in
caso di errore durante il caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisurazioni(char *nome_file, PNodoListaMisurazioni *misurazioni){
  // Sviluppare il corpo della funzione
  FILE *fp;
  fp = fopen(nome_file,"r");
  if(fp == NULL){
  	printf("Errore! Il File cercato NON ESISTE!");
  	return -1;
  }
  TMisurazione misurazione;
  int misurazioni_totali = 0;
  int num_parametri = 0;
  int posizione; 
  
  for (int i=0; i<NUM_AREE; i++)
    misurazioni[i] = NULL;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %d %d %s %s", &misurazione.codice, &misurazione.temperatura, &misurazione.umidita, misurazione.data, misurazione.orario);
  	posizione = misurazione.codice / NUM_AREE;
  	if(num_parametri == 5){
  		if(AggiungiMisurazione(&misurazioni[posizione], misurazione) == 1)
  			misurazioni_totali++;
	    }else{
	    	printf("Errore! File non caricato Correttamente!");
         	return -1;
    }
  }
  return misurazioni_totali;
}

/*
2) MisurazioniAnno: Dato l'array di liste di misurazioni, un anno di
riferimento ed il codice di un sensore, restituisce la lista delle
misurazioni di quel sensore relativo all'anno di riferimento.

Parametri: array di liste di misurazioni, anno di riferimento, codice
sensore
Restituisce: Lista di misurazioni del sensore nell'anno di riferimento
*/

PNodoListaMisurazioni MisurazioniAnno(PNodoListaMisurazioni *misurazioni, char *anno, int codice){
  // Sviluppare il corpo della funzione
  PNodoListaMisurazioni lista_misurazione = NULL;
  PNodoListaMisurazioni m;
  int posizione;
  posizione = codice/10;	  
  m = misurazioni[posizione];  	
  while(m != NULL){
	if(strncmp(anno, m->misurazione.data, 4) == 0 && codice == m->misurazione.codice){
		AggiungiMisurazione(&lista_misurazione, m->misurazione);		  
        }
    m = m->succ;
    }
  return lista_misurazione;   
}


/*
3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

Parametri: array di liste di misurazioni, temperatura minima,
temperatura massima, umidità minima, umidità massima
*/

void VisualizzaMisureIntervallo(PNodoListaMisurazioni *misurazioni, int temperatura_min, int temperatura_max, int umidita_min, int umidita_max){
  // Sviluppare il corpo della funzione
  PNodoListaMisurazioni m;
  for(int i=0; i<NUM_AREE; i++){
  	m = misurazioni[i];
  	printf("\nArea n. %d\n",i);
  	
  	while(m != NULL){
  		if( m->misurazione.temperatura >= temperatura_min && 
		    m->misurazione.temperatura <= temperatura_max &&   
		    m->misurazione.umidita >= umidita_min && 
			m->misurazione.umidita <= umidita_max)	{
					VisualizzaMisurazione(m->misurazione);
		  }
		m = m->succ;
    }
  }
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

// Stampa Array di Liste di Misurazioni
void VisualizzaArrayDiListe(PNodoListaMisurazioni *misurazioni){
	PNodoListaMisurazioni m;
	for(int i=0; i<NUM_AREE; i++){
		m = misurazioni[i];
		while(m != NULL){
			printf("%d\t",m->misurazione.codice);
			printf("%d\t",m->misurazione.temperatura);
			printf("%d\t",m->misurazione.umidita);	
			printf("%s\t",m->misurazione.data);
			printf("%s\n",m->misurazione.orario);
			m = m->succ;			
		}
	}
}

// Stampa Lista di Misurazioni
void VisualizzaLista(PNodoListaMisurazioni lista_misurazioni){
	PNodoListaMisurazioni lm;
	lm = lista_misurazioni;
	while(lm != NULL){
		printf("%d\t",lm->misurazione.codice);
		printf("%d\t",lm->misurazione.temperatura);
		printf("%d\t",lm->misurazione.umidita);
		printf("%s\t",lm->misurazione.data);
		printf("%s\n",lm->misurazione.orario);
		lm = lm->succ;
	}
}

int Menu(){
  int scelta;
  
  printf("\n\n*** MENU ***\n"
	 "1. Carica misurazioni\n"
	 "2. Misurazioni anno\n"
	 "3. Misurazioni intervallo\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

// MAIN
int main(void){
  int scelta;
  // dichiarare le variabili necessarie
  PNodoListaMisurazioni misurazioni[NUM_AREE];
  int num_misurazioni; 
  int codice;
  char anno[10]; 
  PNodoListaMisurazioni lista_misurazioni;
  int temperatura_minima;
  int temperatura_massima;
  int umidita_massima;
  int umidita_minima;
  
  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	// Invocare la funzione CaricaMisurazioni e visualizzare il
	// numero di misurazioni caricate o l'eventuale messaggio di errore
	num_misurazioni = CaricaMisurazioni(NOME_FILE, misurazioni);
	if(num_misurazioni == -1){
		printf("Errore! File non caricato correttamente.");
		break;
	}
	printf("Il Numero di Misurazioni Totali e': %d",num_misurazioni);
	printf("\nIl Vettore caricato e': \n");
	VisualizzaArrayDiListe(misurazioni);	
	
	break;

      case 2:
	// Acquisire l'anno ed il codice del sensore, invocare la
	// funzione MisurazioniAnno, visualizzare la lista delle
	// misurazioni ottenuta e disallocare la lista.
	printf("Inserisci l'anno: ");
	scanf("%s",anno);
	printf("Inserisci il Codice: ");
	scanf("%d",&codice);
	lista_misurazioni = MisurazioniAnno(misurazioni, anno, codice);
	printf("\nLa Lista dellle Misurazioni e': \n");
	VisualizzaLista(lista_misurazioni);
	break;

      case 3:
	// Acquisire gli intervalli di temperatura e di umidità ed
	// invocare la funzione VisualizzaMisureIntervallo
	printf("Inserisci un Intervallo di Temperatura.");
	printf("\nInserisci una Soglia Minima di Temperatura: ");
	scanf("%d",&temperatura_minima);
	printf("Inserisci una Soglia Massima di Temperatura: ");
	scanf("%d",&temperatura_massima);	
	printf("\n\nInserisci un Intervallo di Umidita'.");
	printf("\nInserisci una Soglia Minima di Umidita': ");
	scanf("%d",&umidita_minima);
	printf("Inserisci una Soglia Massima di Umidita': ");
	scanf("%d",&umidita_massima);
	VisualizzaMisureIntervallo(misurazioni, temperatura_minima, temperatura_massima, umidita_minima, umidita_massima);		
	break;
      }
  } while (scelta != 0);

  // Disallocare le liste nel vettore delle misurazioni
  
  return 0;
}
