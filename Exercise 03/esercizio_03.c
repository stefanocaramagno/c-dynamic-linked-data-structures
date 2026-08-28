/*
  Sviluppo di applicazione in ANSI C per gestire il noleggio di biciclette.

  In un file di testo ("biciclette.txt"), è memorizzato 
  l'elenco delle biciclette del bicinoleggio.
  Così come visibile nel file, per ciascuna bicicletta
  sono memorizzate le seguenti informazioni:
  - numero telaio
  - nome categoria (es: mountainbike, citta, corsa, elettrica, cross, bambini, etc)
  - costo giornaliero
  - stato (disponibile/noleggiata).

  Implementare le seguenti funzioni:

  1. CaricaBiciclette: carica le biciclette presenti nel file in due
  liste rispettivamente una contenente quelle disponibili e l'altra
  contenente quelle noleggiate.

  2. Noleggia: dato il numero di telaio, rimuove tale bicicletta (se
  esiste) dalla lista delle biciclette disponibili e la aggiunge a
  quella delle biciclette noleggiate.

  3. EstraiBicicletteDiInteresse: dato un costo massimo giornaliero,
  seleziona dalla lista delle biciclette disponibili quelle che
  soddisfano tale criterio e le inserisce in un apposito vettore di
  biciclette.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

// STRINGA VISUAL STUDIO
#define _CRT_SECURE_NO_WARNINGS

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUTTURA DATI
typedef struct Bicicletta{
  char  telaio[8];
  char  categoria[16];
  float costo;
  char  stato[12];
} TBicicletta;

typedef struct NodoBicicletta{
  TBicicletta info;
  struct NodoBicicletta *next;
} TNodoBicicletta;

typedef TNodoBicicletta *TListaBiciclette;


/* AggiungiBicicletta inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiBicicletta(TListaBiciclette *plis, TBicicletta elem){
  TListaBiciclette paux;

  paux = (TListaBiciclette)malloc(sizeof(TNodoBicicletta));

  if (paux == NULL)
    return 0;
  
  paux->info = elem;
  paux->next = *plis;

  *plis = paux;
  
  return 1;
}

/*
  1. CaricaBiciclette: carica le biciclette presenti nel file in due
  liste rispettivamente una contenente quelle disponibili e l'altra
  contenente quelle noleggiate.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle biciclette disponibili (disponibili),
  lista delle biciclette noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/
int CaricaBiciclette(char *nome_file, TListaBiciclette *disponibili, TListaBiciclette *noleggiate){
  // Implementare il corpo della funzione
  FILE *fp;
  fp = fopen(nome_file,"r");
  int status = 0;
  if(fp == NULL){
  	printf("Errore! Il File cercato NON ESISTE!");
  	return status;
  }
  TBicicletta elem;
  *disponibili = NULL;
  *noleggiate = NULL;
  int num_parametri = 0;
  
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%s %s %f %s", elem.telaio, elem.categoria, &elem.costo, elem.stato);
  	if(num_parametri == 4){
  		if(strcmp(elem.stato, "disponibile") == 0)
  			status = AggiungiBicicletta(disponibili,elem);
  		if(strcmp(elem.stato, "noleggiata") == 0)
  			status = AggiungiBicicletta(noleggiate, elem);
	  }else
	    printf("Errore! Liste NON CARICATE CORRETTAMENTE!");
	  	return status;
  }
  return status;
}

/*
  RicercaBicicletta: ricerca nella lista lis la bicicletta con il
  numero di telaio fornito in ingresso (telaio). Restituisce NULL se
  la bicicletta con quel numero di telaio non è presente nella lista
  lis.
*/
TListaBiciclette RicercaBicicletta(TListaBiciclette lis, char* telaio){
  while (lis != NULL){
    if (strcmp(telaio, lis->info.telaio) == 0)
	return (lis);
      lis = lis->next;
    }
  return(NULL);
}

/*
  CancellaBicicletta: ricerca nella lista lis la bicicletta con numero
  di telaio fornito in ingresso (telaio) e la rimuove dalla lista.
*/
void CancellaBicicletta(TListaBiciclette *lis, char *telaio){
  // Implementare il corpo della funzione
  TListaBiciclette prec, corr;
  
  int trovato = 0;
  
  if(lis != NULL){
  	if(strcmp(telaio, lis->info.telaio) == 0){
  		prec = *lis;
  		*lis = (*lis)->next;
  		free(prec);
    }else{
    	prec = *lis;
    	corr = (*lis)->next;
    	while(corr != NULL && trovato == 0){
  			if(strcmp(telaio, lis->info.telaio) == 0){
    			trovato = 1;
    			prec->next = corr->next;
    			free(corr);
		    }
            prec = prec->next;
			corr = corr->next; 
     	}
    }  
}  

/*
  2. Noleggia: dato il numero di telaio, rimuove tale bicicletta (se
  esiste) dalla lista delle bici disponibili e la aggiunge a quella
  delle bici noleggiate.

  Parametri di ingresso: 
  numero telaio bicicletta,

  Parametri di ingresso/uscita: 
  lista delle biciclette disponibili (disponibili),
  lista delle biciclette noleggiate (noleggiate)

  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Noleggia(char *telaio, TListaBiciclette *disponibili, TListaBiciclette *noleggiate){
  // Implementare il corpo della funzione
  TListaBiciclette BiciTrovata;
  BiciTrovata = RicercaBicicletta(*disponibili, telaio);
  if(BiciTrovata == NULL)
	return 0;
  }
  AggiungiBicicletta(noleggiate, BiciTrovata->info);
  CancellaBicicletta(disponibili, telaio);
  return 1;
}

/*
  3. EstraiBicicletteDiInteresse: dato un costo massimo giornaliero,
  seleziona dalla lista delle biciclette disponibili quelle che
  soddisfano tale criterio e le inserisce in un apposito vettore di
  biciclette.

  Parametri di ingresso:
  lis - lista delle biciclette disponibili,
  categoria - categoria di autobicicletta
  
  Parametri di uscita:
  dim - numero di biciclette che soddisfano i criteri
  
  Valore restituito: 
  TAutoBicicletta - vettore delle biciclette selezionate
*/
TBicicletta *EstraiBicicletteDiInteresse(TListaBiciclette lis, float max_costo, char *categoria, int *dim){
   // Implementare il corpo della funzione
   TBicicletta *vett;
   TListaBiciclette plis;
   
   plis = lis;
   while(plis != NULL){
   	if(max_costo = plis->info.costo && strcmp(categoria, plis->info.categoria) == 0)
   		(*dim)++;
   	plis = plis->next;
   }
   
   int i=0;
   plis = lis;  
   while(plis != NULL){
   	if(max_costo = plis->info.costo && strcmp(categoria, plis->info.categoria) == 0){
   		AggiungiBicicletta(vett[i], plis->info)
   		i++;
    }
    plis = plis->next;
   }   
   return vett;
}


/*
  VisualizzaBiciclette visualizza le informazioni delle biciclette
  nella lista passata come parametro
*/
void VisualizzaBiciclette(TListaBiciclette lis){
  while (lis != NULL)
    {
      printf("%s %s %.2f\n",
	     lis->info.telaio,
	     lis->info.categoria,
	     lis->info.costo);
      lis = lis->next;
    }
}

/*
  VisualizzaVettoreBici visualizza le informazioni delle biciclette
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreBici(TBicicletta v[], int dim){
  // Implementare il corpo della funzione
}



int Menu() {
  int scelta;
  
  printf("\n\n*** M E N U ***\n"
	 "1 - Carica biciclette\n"
	 "2 - Noleggia bicicletta\n"
	 "3 - Cerca biciclette di interesse \n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaBiciclette lista){
  TListaBiciclette paux;
  // Implementare il corpo della funzione
}

// MAIN
int main(void){
  TListaBiciclette disponibili = NULL;
  TListaBiciclette noleggiate = NULL;

  int          scelta;
  char         nomefile[32];
  char         telaio[8];
  char         cat[16];
  int          dim;
  float        costo_max;
  TBicicletta *vett;
  
  int status;
  
  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	  // acquisire il nome del file
	  // invocare la funzione CaricaBiciclette
	  // visualizzare le liste ottenute
	  printf("Inserisci il Nome del FILE da aprire: ");
	  scanf("%s",nomefile);
	  status = CaricaBiciclette(nomefile,&disponibili,&noleggiate);
	  if(status == 0){
	  	break;
	  }
	  printf("\nLista delle Auto Disponibili: \n");
	  VisualizzaBiciclette(disponibili);
	  printf("\nLa Lista delle Auto Noleggiate: \n");
	  VisualizzaBiciclette(noleggiate);	  
	break;

      case 2:
	  // acquisire il numero di telaio della bici da noleggiare
	  // invocare la funzione Noleggia
	  // visualizzare le liste modificate
	  printf("Inserisci il Numero di Telaio: ");
	  scanf("%s",telaio);
	  status = Noleggia(telaio,&disponibili,&noleggiate);
	  if(status == 1){
	  	printf("Errore! Trasferimento Bici NON AVVENUTO!");
	  	break;
	  }
	  printf("\nLista delle Auto Disponibili (MODIFICATA): \n");
	  VisualizzaBiciclette(disponibili);
	  printf("\nLa Lista delle Auto Noleggiate (MODIFICATA): \n");
	  VisualizzaBiciclette(noleggiate);	  	  
	break;

      case 3:
	  // acqusire il costo massimo
	  // acquisire una categora della bici
	  // invocare la funzione EstraiBicicletteDiInteresse
	  // visualizzare il vettore restituito
	  printf("Inserisci un Costo Massimo (Soglia): ");
	  scanf("%f".costo_max);
	  printf("Inserisci una Categoria di Riferimento: ");
	  scanf("%s",cat);
	  vett = EstraiBicicletteDiInteresse(disponibili, costo_max, cat, &dim);
	  printf("Il Vettore e': \n");
	  VisualizzaVettoreBici(vett, dim);
	break;
      }

  } while (scelta != 0);

  // Didsallocare le lista

  return 0;
}

