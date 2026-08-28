/*
  Sviluppo di applicazione in ANSI C per gestire le code di un ufficio postale.

  In un file di testo ("prenotato.txt"), è memorizzato l'elenco dei prenotati.
  Per ciascuno dei prenotati è memorizzato il nome, il cognome e il tipo di operazione.

  Le operazioni previste sono tre:
  - raccomandata
  - spedizione_pacco
  - conto_corrente

  Si assuma che il nome e cognome non contengano spazi.

  Implementare le seguenti funzioni:

  1. CaricaOperazioni: carica le operazioni presenti nel file in un
  vettore di tre code che contengono, rispettivamente, i clienti prenotati per
  le raccomandate, quelli per la spedizione di un pacco e quelli per il pagamento
  di un conto corrente.

  2. Operazione: dato il tipo di operazione, rimuove il primo cliente
  dalla coda corrispondente e lo introduce nella lista delle operazioni
  effettuate. La lista delle operazioni effettuate contiene come informazione
  sia il cliente che il tipo di operazione.

  3. EstraiNumeroDiOperazioni: data la lista delle operazioni calcola il numero
  di operazione di ciascun tipo e le restituisce inserendole in un apposito
  vettore di interi.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

// STRINGA VISUAL STUDIO
#define _CRT_SECURE_NO_WARNINGS

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI
#define NOME_FILE "prenotati.txt"

// la funzione codifica restituisce un intero in basa al valore della stringa
int codifica(char* st) {
    if (strcmp(st, "raccomandata") == 0) return 0;
    if (strcmp(st, "pacco") == 0) return 1;
    return 2;
}

// STRUTTURA DATI (Coda Clienti)
typedef struct Cliente {
    char  nome[20];
    char  cognome[64];
} TCliente;

typedef struct NodoCliente {
    TCliente info;
    struct NodoCliente* next;
} TNodoCliente;

typedef struct C {
    TNodoCliente* primo, * ultimo;
} Coda;


/* AggiungiCliente inserisce un elemento in una coda passata
   come primo parametro.
   Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti
 */
int AggiungiCliente(Coda* pC, TCliente cliente) {
    TNodoCliente* paux;

    paux = (TNodoCliente*)malloc(sizeof(TNodoCliente));

    if (paux == NULL)
        return 0;
    paux->info = cliente;
    paux->next = NULL;
    if (pC->primo == NULL)
        pC->primo = pC->ultimo = paux;
    else {
        pC->ultimo->next = paux;
        pC->ultimo = paux;
    }
    return 1;
}

/*crea una coda vuota*/
void CodaVuota(Coda* pC) {
    pC->primo = pC->ultimo = NULL;
}

/*elimina un elemento dalla coda e restituisce, come parametro, il cliente
estratto dalla coda, la funzione restituisce 1 se a buon esito 0 se non
viene estratto nessun elemento dalla coda*/
int eliminaCoda(Coda* pC, TCliente* pCliente) {
    //implementazione a cura dello studente


}

// STRUTTURA DATI (Lista Operazioni)
typedef struct Operazione {
    char  nome[20];
    char  cognome[64];
    char operazione[20];
} TOperazione;

typedef struct NodoOperazione {
    TOperazione info;
    struct NodoOperazione* next;
} TNodoOperazione, * TListaOperazione;


/*inserimento in testa nella lista delle operazioni, restituisce 1 se l'operazione
ha successo 0 altrimenti*/
int InserisciTestaLista(TListaOperazione* plis, TOperazione operazione) {
    TListaOperazione paux;
    paux = (TListaOperazione)malloc(sizeof(TOperazione));
    if (paux == NULL) return 0;
    paux->next = *plis;
    paux->info = operazione;
    *plis = paux;
    return 1;
}

/*
  1. CaricaOperazioni: carica i dati del cliente in base al valore
  della operazione richiesta nella coda corrispondente.

  Parametri di ingresso: nome del file
  Parametri di uscita: il vettore contenente le tre code (coda dei clienti prenotati per una raccomandata (raccomandata),
  coda dei clienti prenotati per spedire un pacco (pacco)
  coda dei clienti prenotati per un contocorrente (contocorrente))
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/
int CaricaOperazioni(char* nome_file, Coda* vettoreCode) {

    for (int i = 0; i < 3; i++)
        CodaVuota(&vettoreCode[i]);

    FILE* fp;
    fp = fopen(nome_file, "r");

    int status = 0;

    if (fp == NULL) {
        printf("Errore! File cercato NON ESISTE");
        return status;
    }

    TCliente cliente;
    char operazione[20];
    int num_parametri = 0;

    while (!feof(fp)) {
        num_parametri = fscanf(fp, "%s %s %s", cliente.nome, cliente.cognome, operazione);
        if (num_parametri == 3) {
            status = AggiungiCliente(&vettoreCode[codifica(operazione)], cliente);
        }
        else {
            printf("Errore! File NON Caricato Correttamente!");
            return status;
        }
    }
    fclose(fp);
    return status;
}

/*
  2. Operazione: dato il tipo di operazione, rimuove il primo cliente
  dalla coda corrispondente e lo introduce nella lista delle operazioni effettuate.
  La lista delle operazioni effettuate contiene come informazione sia il cliente che il tipo di operazione.

  La funzione prende in ingresso la coda da cui estrarre, la stringa che identifica
  il tipo di operazione e la lista in cui inserire l'operazione.
*/
int Operazione(Coda* pC, char* tipo, TListaOperazione* pLista) {
    //implementazione a cura dello studente
	TCliente c = pC->primo->info;
	
	TOperazione operazione;
	strcpy(operazione.nome, c.nome);
	strcpy(operazione.cognome, c.cognome);	
	strcpy(operazione.operazione, tipo);	
	
    if (InserisciTestaLista(pLista, operazione) == 0) {
        printf("Errore! Operazione NON Riuscita");
        return 0;
    }else {
        eliminaCoda(pC, &c);
        return 1;
    }
    return 0;
}

/*
  3. ContaNumeroDiOperazioni: data la lista delle operazioni calcola il numero
  di operazione di ciascun tipo e le restituisce inserendole in un apposito
  vettore di interi

  Parametri di ingresso:
  lis - lista delle operazioni

  Valore restituito:
  int - vettore contenente il numero di operazioni per tipo
*/
int* ContaNumeroDiOperazioni(TListaOperazione lis) {
    //implementazione a cura dello studente

}


/*
  VisualizzaCoda visualizza le informazioni dei clienti
  contenute in una coda passata come parametro
*/
void VisualizzaCoda(Coda C) {
    TNodoCliente* paux = C.primo;
    while (paux != NULL) {
        printf("%s %s \n", paux->info.nome, paux->info.cognome);
        paux = paux->next;
    }
}

/*
  VisualizzaLista visualizza le informazioni delle operazioni
  contenute in una lista passata come parametro
*/
void Visualizzalista(TListaOperazione l) {
    while (l != NULL) {
        printf("\n%s %s  %s\n", l->info.nome, l->info.cognome, l->info.operazione);
        l = l->next;
    }
}

/*
  VisualizzaVettoreInteri v
*/
void VisualizzaVettore(int v[], int dim) {
    int i;
    for (i = 0; i < dim; i++)
        printf("%d\n", v[i]);
}


int Menu() {
    int scelta;

    printf("\n\n*** M E N U ***\n"
        "1 - Carica clienti\n"
        "2 - Esegui operazione\n"
        "3 - Conta operazioni \n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaLista(TListaOperazione* lista) {
    //implementazine a cura dello studente 
}

void DisallocaCoda(Coda* c) {
    TNodoCliente* paux, * lis = c->primo;

    while (lis != NULL) {
        paux = lis;
        lis = lis->next;
        free(paux);
    }
    c->primo = c->ultimo = NULL;
}

// MAIN
int main(void) {
    Coda vettoreCode[3];
    TListaOperazione ListaOperazioni = NULL;
    int scelta;
    TCliente cliente;
    char tipoOperazione[32];
    int* vett;

    for (int i = 0; i < 3; ++i)
        CodaVuota(&vettoreCode[i]);

    int status;

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            // invocare la funzione Carica
            // stampare il vettore di code
            status = CaricaOperazioni(NOME_FILE, vettoreCode);
            if (status == 0) {
                break;
            }
            printf("\nIl Vettore di Code caricato e': \n");
            for (int i = 0; i < 3; i++)
                VisualizzaCoda(vettoreCode[i]);
            break;

        case 2:
            // leggere il tipo di operazione
            // invocare la funzione Operazione e notificare se l'operazione è riuscita
            // nel caso di operazione riuscita stampare la lista delle operazioni effettuate
            printf("Inserisci il Tipo di Operazione: ");
            scanf("%s", tipoOperazione);
            int i = codifica(tipoOperazione);
            status = Operazione(&vettoreCode[i], tipoOperazione, &ListaOperazioni);
            if (status == 0) {
                break;
            }
            printf("La Lista Operazione e': \n");
            Visualizzalista(ListaOperazioni);
            break;

        case 3:
            // conta il numero di operazioni per tipo invocando la funzione ContaNumeroDiOperazioni
            // stampare le operazioni per ciascun tipo
            vett =  ContaNumeroDiOperazioni(ListaOperazioni);
            printf("\nIl Vettore e': \n");
            VisualizzaVettore(vett, int dim);           
            break;
        }
    } while (scelta != 0);

    // Didsallocare la lista e le code


    return 0;
}
