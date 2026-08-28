/*
  Sviluppo di applicazione in ANSI C per gestire un sistema di
  un termostato che opera come di seguito.

  Su un archivio (allegato all'attività 'termostato.txt') è
  memorizzato l'elenco delle fasce orarie in cui attivare il
  riscaldamento nelle diversa stanze di un edificio. Ogni rga del file
  contiene le seguenti informazioni: ora_attivazione,
  ora_disattivazione, id_stanza.

  Implementare le seguenti funzioni:

  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una
  lista di fasce orarie.

  2. CreaListaStanze: a partire dalla lista delle fasce orarie,
  costruisce una lista di stanze in cui, per ogni area stanza, ci sia
  il numero di fasce orarie e la lista delle fasce orarie per quella
  specifica stanza.

  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze che a quell'orario hanno il
  riscaldamento attivato.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NOME_FILE "termostato.txt"

// STRUTTURE DATI (Lista Fascie Orarie)
typedef struct FasciaOraria{
  int  id_stanza;
  char ora_inizio[6]; // formato hh:mm
  char ora_fine[6];   // formato hh:mm
} TFasciaOraria;

typedef struct NodoListaFasceOrarie{
  TFasciaOraria fascia_oraria;
  struct NodoListaFasceOrarie *succ;
} TNodoListaFasceOrarie;

typedef TNodoListaFasceOrarie *PNodoListaFasceOrarie;

// STRUTTURE DATI (Lista Stanze)
typedef struct NodoListaStanze{
  int id_stanza;
  int num_fasce_orarie;
  PNodoListaFasceOrarie lista_fasce_orarie;
  struct NodoListaStanze *succ;
} TNodoListaStanze;

typedef TNodoListaStanze *PNodoListaStanze;


/* AggiungiFasciaOraria inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiFasciaOraria(PNodoListaFasceOrarie *fasce_orarie, TFasciaOraria fascia_oraria){
  PNodoListaFasceOrarie aux;

  aux = (PNodoListaFasceOrarie)malloc(sizeof(TNodoListaFasceOrarie));

  if (aux == 0)
    return 0;
  
  aux->fascia_oraria = fascia_oraria;
  aux->succ = *fasce_orarie;

  *fasce_orarie = aux;
  
  return 1;
}

/*
  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una lista
  di fasce orarie.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle fasce orarie (PNodoListaFasceOrarie)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaFasceOrarie(char *nome_file, PNodoListaFasceOrarie *fasce_orarie){
  // ...a cura dello studente...
  FILE *fp;
  fp = fopen(nome_file,"r");
  int status = 0;
  if(fp == NULL){
  	printf("Errore! Il File caricato NON E' STATO TROVATO!");
  	return status;
  }
  
  TFasciaOraria fascia_oraria;
  int num_parametri = 0;
  *fasce_orarie = NULL;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%d %s %s", &fascia_oraria.id_stanza, fascia_oraria.ora_inizio, fascia_oraria.ora_fine);
  	if(num_parametri == 3){
  		status = AggiungiFasciaOraria(fasce_orarie, fascia_oraria);
	  }else{
	  	printf("Errore! Il File non e' stato caricato correttamente.");
	  	return status;
	  }
  }
  fclose(fp);
  return status;
}

/* 
   AggiungiStanza inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaStanze AggiungiStanza(PNodoListaStanze stanze, int id_stanza){
  PNodoListaStanze aux;

  aux = (PNodoListaStanze)malloc(sizeof(TNodoListaStanze));
  
  aux->id_stanza = id_stanza;
  aux->num_fasce_orarie = 0;
  aux->lista_fasce_orarie = NULL;
  aux->succ = stanze;
  
  return aux;
}

/*
  CercaStanza restituisce il puntatore al nodo della lista delle stanze
  per una specifica stanza. Restituisce NULL se quella stanza non è
  presente nella lista delle stanze.
 */
PNodoListaStanze CercaStanza(PNodoListaStanze stanze, int id_stanza){
  while (stanze != NULL){
      if (stanze->id_stanza == id_stanza)
	return stanze;

      stanze = stanze->succ;
    }

  return NULL;
}

/*
  AggiungiFascia_OrariaInStanza aggiunge una fascia_oraria nella lista delle
  fasce_orarie relative alla specifica stanza.
 */
void AggiungiFasciaOrariaInStanza(PNodoListaStanze *plista_stanze, TFasciaOraria fascia_oraria){
  PNodoListaStanze p;
  
  p = CercaStanza(*plista_stanze, fascia_oraria.id_stanza);
  if (p == NULL)
    {
      p = AggiungiStanza(*plista_stanze, fascia_oraria.id_stanza);
      *plista_stanze = p;
    }

  if (AggiungiFasciaOraria(&p->lista_fasce_orarie, fascia_oraria))
    (p->num_fasce_orarie)++;
}

/* 
   2. CreaStanze: a partire dalla lista delle fasce_orarie, costruisce una
   lista di stanze in cui, per ogni stanza, ci sia il numero e
   la lista delle fasce_orarie per quella specifica stanza.

   Parametri di ingresso: lista delle fasce_orarie
   Parametri di uscita: lista delle stanze
*/
PNodoListaStanze CreaStanze(PNodoListaFasceOrarie fasce_orarie){
  // ...a cura dello studente...
  PNodoListaFasceOrarie f;
  PNodoListaStanze stanze = NULL;
  f = fasce_orarie;
  while(f != NULL){
  	AggiungiFasciaOrariaInStanza(&stanze, f->fascia_oraria);
  	f = f->succ;
  }
  return stanze;
}

// Restituisce 1 se orario è all'interno della fascia oraria da
// ora_inizio a ora_fine. Restituise 0 altrimenti
int OrarioInFasciaOraria(char *orario, char *ora_inizio, char *ora_fine){
  // ...a cura dello studente ...
  return (strcmp(orario, ora_inizio ) > 0  && strcmp(orario, ora_fine) < 0);
}


/*
  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze in cui è attivo il riscaldamento a
  quell'ora.

  Parametri di ingresso: lista delle stanze, orario
  Parametri di uscita: array delle stanze
*/
int *RiscaldamentoAttivo(PNodoListaStanze stanze, char *orario, int *n){
  // ...a cura dello studente...
  PNodoListaStanze st; 
  PNodoListaFasceOrarie lfo;
  int *id_stanze;
   
   // Si Calcola la Dimensione del Vettore in base a quanti elementi soddisfanno i prerequisiti
  st = stanze;
  while(st != NULL){
  	lfo = st->lista_fasce_orarie;  	
  	while(lfo != NULL){
   		if( OrarioInFasciaOraria(orario, lfo->fascia_oraria.ora_inizio, lfo->fascia_oraria.ora_fine) ){
  			(*n)++;
	  	}
	  	lfo = lfo->succ;
  	} 	
	st = st->succ;	
  }

  // Allocazione del Vettore
  id_stanze = (int*)malloc((*n) * sizeof(int));
  if(id_stanze == NULL){
  	printf("Errore! Vettore NON ALLOCATO CORRETTAMENTE!");
  	return 1;
  }
  
  // Si Copia l'Id delle Stanze nel Vettore
  int i=0;
  st = stanze;
  while(st != NULL){
  	lfo = st->lista_fasce_orarie;  	
  	while(lfo != NULL){
   		if( OrarioInFasciaOraria(orario, lfo->fascia_oraria.ora_inizio, lfo->fascia_oraria.ora_fine) ){
  			id_stanze[i] = lfo->fascia_oraria.id_stanza;
  			i++;
	  	}
	  	lfo = lfo->succ;
  	} 	
	st = st->succ;	
  }
  
  return id_stanze;
}

int Menu(){
  int scelta;
  
  printf("\n\n*** M E N U ***\n"
	 "1 - Carica dati termostato\n"
	 "2 - Crea stanze\n"
	 "3 - Stanze riscaldate\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaListaFasceOrarie(PNodoListaFasceOrarie lista){
  PNodoListaFasceOrarie p;

  while (lista != NULL){
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

void DisallocaListaStanze(PNodoListaStanze lista){
  // ...a cura dello studente...
}

void VisualizzaLista_FasceOrarie(PNodoListaFasceOrarie lista){	
    PNodoListaFasceOrarie lis;
    lis = lista;
	while(lis != NULL){
		printf("%d\t",lis->fascia_oraria.id_stanza);
		printf("%s\t",lis->fascia_oraria.ora_inizio);
		printf("%s\n",lis->fascia_oraria.ora_fine);
		lis = lis->succ;
	}
}

void VisualizzaLista_Stanze(PNodoListaStanze stanze){	
    PNodoListaStanze st;
    PNodoListaFasceOrarie fasce;
    st = stanze;
	while(st != NULL){
		printf("\nSTANZA) %d\n",st->id_stanza);
		printf("Fascia n.%d\n",st->num_fasce_orarie);
		
		fasce = st->lista_fasce_orarie;
		printf("\tID\tINIZIO\tFINE\n");
		while(fasce != NULL){
			printf("\t%d",fasce->fascia_oraria.id_stanza);
			printf("\t%s",fasce->fascia_oraria.ora_inizio);
			printf("\t%s\n",fasce->fascia_oraria.ora_fine);
			fasce = fasce->succ;
		}
	st = st->succ;
	}
}

// MAIN
int main(void){
  PNodoListaFasceOrarie fasce_orarie = NULL;
  PNodoListaStanze      stanze = NULL;
  int                   scelta, n;
  char                  orario[16];
  int                  *id_stanze;
  
  int status; 
  
  do {
    scelta = Menu();

    switch (scelta){
      case 1:
      	status = CaricaFasceOrarie(NOME_FILE, &fasce_orarie);
      	if(status == 0){
      		break;
		  }
        printf("La Lista caricata e': \n");
        VisualizzaLista_FasceOrarie(fasce_orarie);
	break;

      case 2:
	    stanze = CreaStanze(fasce_orarie);
	    printf("La Lista di Stanze e': \n");
	    VisualizzaLista_Stanze(stanze);	    
	break;

      case 3:
	printf("Inserisci l'orario (hh:mm): ");
	scanf("%s", orario);
	id_stanze = RiscaldamentoAttivo(stanze, orario, &n);
	for (int i=0; i<n; i++){
		printf("%d, ", id_stanze[i]);
	}	  
	printf("\n");
	free(id_stanze);
	break;
      }
    
  } while (scelta != 0);

  // Disallocare le lista
  DisallocaListaFasceOrarie(fasce_orarie);
  DisallocaListaStanze(stanze);

  return 0;
}
