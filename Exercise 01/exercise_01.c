/*
  Sviluppo di applicazione in ANSI C per gestire 
  le autovetture di una società di autonoleggio.

  In un file di testo ("autovetture.txt"), è memorizzato 
  l'elenco delle autovetture possedute dalla società.
  Così come visibile nel file, per ciascuna autovettura
  sono memorizzate le seguenti informazioni:
  - targa
  - nome categoria (es: citycar, berlina, SUV, sportive, monovolume, etc)
  - costo giornaliero
  - km percorsi
  - stato (disponibile/noleggiata).

  Implementare le seguenti funzioni:
  1. CaricaVetture: 
        carica le autovetture presenti nel file in due liste 
        rispettivamente una contenente quelle disponibili
        e l'altra contenente quelle noleggiate.

  2. Noleggia: 
        data una targa, rimuove tale vettura (se esiste) 
        dalla lista delle auto disponibili e la aggiunge 
        a quella delle auto noleggiate. 

  3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria,
        seleziona dalla lista delle vetture disponibili
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

// STRINGA VISUAL STUDIO
#define _CRT_SECURE_NO_WARNINGS

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUTTURA DATI
typedef struct Autovettura{
  char  targa[8];
  char categoria[16];
  float costo;
  long km;
}TAutovettura;

typedef struct NodoAutovettura{
  TAutovettura info;
  struct NodoAutovettura *next;
}TNodoAutovettura;

typedef TNodoAutovettura *TListaAutovetture;


/* AggiungiVettura inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiVettura(TListaAutovetture *plis, TAutovettura elem) {
  TListaAutovetture paux;

  paux = (TListaAutovetture)malloc(sizeof(TNodoAutovettura));

  if (paux == NULL)
    return 0;
  
  paux->info = elem;
  paux->next = *plis;

  *plis = paux;
  
  return 1;
}

/*
  1. CaricaVetture: carica le autovetture presenti nel file
  in due liste rispettivamente una contenente quelle disponibili
  e l'altra contenente quelle noleggiate.


  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle autovetture disponibili (disponibili),
                       lista delle autovetture noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaVetture(char *nome_file, TListaAutovetture *disponibili, TListaAutovetture *noleggiate) {
  // Implementare il corpo della funzione
  FILE *fp;
  fp = fopen(nome_file,"r");
  *disponibili = NULL;
  *noleggiate = NULL;
  int status = 0;
  char stato_veicolo[15];
  
  if(fp == NULL){
  	printf("Errore! Il FILE cercato NON ESISTE!");
  	return status;
  }
  TAutovettura elem;
  int num_parametri = 0;
  while(!feof(fp)){
  	num_parametri = fscanf(fp,"%s %s %f %d %s",elem.targa, elem.categoria, &elem.costo, &elem.km, stato_veicolo);

  	if(num_parametri == 5){
  		if((strcmp(stato_veicolo,"disponibile") == 0))
  			status = AggiungiVettura(disponibili, elem);
        if((strcmp(stato_veicolo,"noleggiata") == 0))
  			status = AggiungiVettura(noleggiate, elem);
    } else{
      	printf("Errore! Lista NON CARICATA CORRETTAMENTE!");
    	return status;
        }
  }
  fclose(fp);
  return status;
}

/*
  RicercaVettura: ricerca nella lista lis l'autovettura con la targa fornita in ingresso (targa). 
  Restituisce NULL se la vettura con quella targa non è presente nella lista lis.
 */
TListaAutovetture RicercaVettura(TListaAutovetture lis, char *targa) {
    while (lis != NULL) {
        if (strcmp(targa, lis->info.targa) == 0)
            return (lis);
        lis = lis->next;
    }
    return(NULL);
}

/*
  CancellaVettura: ricerca nella lista lis l'autovettura con la targa 
  fornita in ingresso (targa) e la rimuove dalla lista. 
 */
void CancellaVettura(TListaAutovetture *lis, char *targa) {
  // Implementare il corpo della funzione
  TListaAutovetture prec, corr;
  int trovato;
  
  if(*lis != NULL){
  	if(strcmp((*lis)->info.targa, targa) == 0){
  		prec = *lis;
  		*lis = (*lis)->next;
  		free(prec);
	  }else
	  	trovato = 0;
	  	prec = *lis;
	  	corr = (*lis)->next;
	  	while(corr != NULL && trovato == 0){
	  		if(strcmp((*lis)->info.targa, targa) == 0){
	  			trovato = 1;
				prec->next = corr->next;  
				free(corr);	  			
			  }
		    corr = corr->next;
		    prec = prec->next;
		}
  }
}  

/*
    2. Noleggia: data una targa, rimuove tale vettura(se esiste)
    dalla lista delle auto disponibili e la aggiunge a quella delle
    auto noleggiate.
    Parametri di ingresso: 
            targa autovettura,
    Parametri di ingresso/uscita: 
            lista delle autovetture disponibili (disponibili),
            lista delle autovetture noleggiate (noleggiate)
    Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Noleggia(char *targa, TListaAutovetture *disponibili, TListaAutovetture *noleggiate) {
  // Implementare il corpo della funzione
  TListaAutovetture AutoTrovata;
  TListaAutovetture Ldisponibili = *disponibili;
  TListaAutovetture Lnoleggiate = *noleggiate;
  
  AutoTrovata = RicercaVettura(Ldisponibili, targa);
  if(AutoTrovata == NULL){
  	printf("Errore! Auto NON TROVATA!");
  	return 0;
  }
  int esito;
  esito = AggiungiVettura(noleggiate, AutoTrovata->info);
  if(esito == 0){
  	printf("Errore! L'Auto NON E' STATA AGGIUNTA CORRETTAMENTE!");
  	return 0;
  }
  CancellaVettura(disponibili, targa);
  return 1;
}

/*
    3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria, 
        seleziona dalla lista delle vetture disponibili 
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

    Parametri di ingresso:
            lis - lista delle autovetture disponibili,
            maxkm - numero massimo di km percorsi,
            categoria - categoria di autovettura
    Parametri di uscita:
            dim - numero di autovetture che soddisfano i criteri
    Valore restituito: 
            TAutoVettura - vettore delle autovetture selezionate
*/

TAutovettura *EstraiVettureDiInteresse(TListaAutovetture lis, long maxkm, char *categoria, int *dim) {
   // Implementare il corpo della funzione
    TAutovettura *vettore;
    int cont = 0;
    TListaAutovetture paux = lis;
   
    while(paux != NULL){
   		if(paux->info.km < maxkm && (strcmp(paux->info.categoria,categoria) == 0)){
   		cont++;
	    }   
		paux = paux->next;	
    }
        
    if ((vettore = (TAutovettura*)malloc(cont * sizeof(TAutovettura))) == NULL) {
    printf("Errore allocazione memoria");
    exit(1);
    }
      
	int i = 0;
	paux = lis;
  	while(paux != NULL){
  		
   		if(paux->info.km < maxkm && (strcmp(paux->info.categoria,categoria) == 0)){
   		
   		vettore[i] = paux->info;
   		i++;
	    }
	paux = paux->next;
	}
	
   *dim = cont;
   return vettore;
}
/*
  VisualizzaVetture visualizza le informazioni delle vetture
  nella lista passata come parametro
 */
void VisualizzaVetture(TListaAutovetture lis) {
  while (lis != NULL)     {
      printf("%s %s %.2f %d\n",
          lis->info.targa,
          lis->info.categoria,
          lis->info.costo,
          lis->info.km);    
      lis = lis->next;
    }
}

/*
  VisualizzaVettoreAuto visualizza le informazioni delle vetture
  contenute nel vettore passato come parametro
 */
void VisualizzaVettoreAuto(TAutovettura v[], int dim) {
  // Implementare il corpo della funzione
  for(int i=0; i<dim; i++){
  	printf("%s\t",v[i].targa);
  	printf("%s\t",v[i].categoria);
  	printf("%.2f\t",v[i].costo);
  	printf("%d\n",v[i].km);  	
  }
}

int Menu() {
  int scelta;
  
  printf("\n\n*** M E N U ***\n"
	 "1 - Carica vetture\n"
	 "2 - Noleggia vettura\n"
	 "3 - Cerca Vetture di interesse \n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaAutovetture lista) {
  TListaAutovetture paux;
  // Implementare il corpo della funzione

}

// MAIN
int main(void) {
  TListaAutovetture disponibili = NULL;
  TListaAutovetture noleggiate = NULL;

  int  scelta;
  char nomefile[32];
  char targa[8];
  long km;
  char cat[16];
  int dim;
  TAutovettura *vett;
  
  int status;
  
  do {
    scelta = Menu();

    switch (scelta){
      case 1:
	  // acquisire il nome del file
	  // invocare la funzione CaricaVetture
	  // visualizzare le liste ottenute
	  printf("Inserisci il Nome del File da aprire: ");
	  scanf("%s",nomefile);
	  status = CaricaVetture(nomefile,&disponibili,&noleggiate);
	  if(status == 0){
	  	break;
	  }
	  printf("\nLa Lista delle Auto DISPONIBILI e' la seguente: \n");
	  VisualizzaVetture(disponibili);
	  printf("\n\nLa Lista delle Auto NOLEGGIATE e' la seguente: \n");
	  VisualizzaVetture(noleggiate); 
	        break;

      case 2:
	  // acquisire la targa dell'auto da noleggiare
	  // invocare la funzione Noleggia
	  // visualizzare le liste modificate
	  printf("Inserisci la Targa dell'auto da Noleggiare: ");
	  scanf("%s",targa);
	  status = Noleggia(targa, &disponibili, &noleggiate);
	  if(status == 1){
	  	printf("\nLa Lista delle Auto DISPONIBILI (Modificata) e' la seguente: \n");
	  	VisualizzaVetture(disponibili);
	  	printf("\n\nLa Lista delle Auto NOLEGGIATE (Modificata) e' la seguente: \n");
	  	VisualizzaVetture(noleggiate); 	  	
	  }
            break;

      case 3:
	  // acqusire i km max
	  // acquisire una categorai auto
	  // invocare la funzione EstraiVettureDiInteresse
	  // visualizzare il vettore restituito
	  printf("Inserisci i Km Massimi: ");
	  scanf("%d",&km);
	  printf("Inserisci una Categoria: ");
	  scanf("%s",cat);
	  vett = EstraiVettureDiInteresse(disponibili, km, cat, &dim);
	  printf("Il Vettore creato e' il seguente: \n");
	  VisualizzaVettoreAuto(vett, dim);
            break;
      }

  } while (scelta != 0);

  // Disallocare le liste
  DisallocaLista(disponibili);
  DisallocaLista(noleggiate);
  
  return 0;
}

