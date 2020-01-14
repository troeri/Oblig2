#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


struct brukerkonto {
  char brukernavn[100];
  char fornavn   [250]; // alle navn bortsett fra etternavn
  char etternavn [100]; // det siste navnet
};

typedef struct brukerkonto konto_t;

void les_data   (konto_t *brukertabell);
void skriv_data (int argc, char **argv, konto_t *brukertabell);

int main(int argc, char** argv) {
  
  konto_t brukertabell[200];

  les_data  (brukertabell);
  skriv_data(argc, argv, brukertabell);

  return 0;
}


void les_data (konto_t *brukertabell) {

  char linje[256], *ord[20];
  char *bnavn, *fnavn, *enavn, *splitt, *splittnavn, *temp1, *siste;
  int uid, bindex=0, index;

  FILE *filpeker = fopen("/etc/passwd", "r");

  while (fgets(linje, sizeof(linje), filpeker)) {
    splitt = strtok(linje, ":"); //<-- initialiserer splitt av linje
    index=0;
    while (splitt) { //<-- legger hvert splitta ord i tabell
      ord[index++] = splitt;
      splitt = strtok(NULL, ":");
    }
    
    uid=atoi(ord[2]); //<-- sjekker uid-verdi
    if (uid >= 1000) {

      strcpy(brukertabell[bindex].brukernavn, ord[0]); //<-- brukernavn er klart. setter inn.
      
      splittnavn = ord[4]; //<-- splittnavn inneholder hele navn pluss ,,,etc
      temp1 = malloc(strlen(splittnavn)); //<-- allokerer minne i temp1 for å ta imot denne
      strcpy(temp1,splittnavn); //<-- tar en kopi av hele, trenger denne senere for å finne fornavn+mellomnavn
 
      enavn = strtok(splittnavn, " "); //<-- starter splitt for å finne etternavn pluss ,,,etc
      while (splittnavn) {
	siste = splittnavn;
	splittnavn = strtok(NULL, " "); //<-- når splittnavn er null, er siste på ordet før null, altså siste ord.
      }
       
      enavn = siste; //<-- etternavn ferdig splittet, men med ,,,etc
      int navnlengde = strlen(temp1)-strlen(enavn); //<-- differansen i bokstavlengde inkludert ,,,etc
      snprintf(brukertabell[bindex].fornavn, navnlengde, "%s", temp1); //<--trekker fra lengden av etternavn,,,etc fra hele navn. setter inn.

      enavn = strtok(enavn, ","); //<-- tar bort ,,,etc fra etternavn
      strcpy(brukertabell[bindex++].etternavn, enavn); //<-- setter inn
      
    }//if for uid>=1000
    	   
  }//while fgets

  fclose (filpeker);
  
}//les_data

void skriv_data (int argc, char **argv, konto_t *brukertabell) {

  char* peker, *peker2;
  int k=0;
  peker = argv[1];
  
  if (getenv("KONTO") != NULL) {

    //printf("funker");
    peker2 = getenv("KONTO");
    if (!strcmp(peker2, "b")) {
      //printf("brukernavn!");

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].brukernavn, brukertabell[k].fornavn, brukertabell[k].etternavn);
	k++;
	}
    }//if

    if (!strcmp(peker2, "f")) {
      //printf("brukernavn!");

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].fornavn, brukertabell[k].etternavn, brukertabell[k].brukernavn);
	k++;
      }
    }//if

    if (!strcmp(peker2, "e")) {
      printf("brukernavn!");
      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].etternavn, brukertabell[k].fornavn, brukertabell[k].brukernavn);
        k++;
      }                                                                                                                                                                          
    }//if
    
    
  }//ifvariabel
  
  //printf("%s %d", argv[1], argc);
  if (argc > 1 && getenv("KONTO") == NULL) {
    
    if (!strcmp(peker, "b")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].brukernavn, brukertabell[k].fornavn, brukertabell[k].etternavn);
	k++;
      }
    }//if

    if (!strcmp(peker, "f")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].fornavn, brukertabell[k].etternavn, brukertabell[k].brukernavn);
	k++;
      }
    }//if
    
    else if (!strcmp(peker, "e")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].etternavn, brukertabell[k].fornavn, brukertabell[k].brukernavn);
	k++;
      }
    }//if
  }//if argc>1

  if ((argc == 1 || argc > 2) && getenv("KONTO") == NULL) {
    printf("Program expected environment variable or one argument: f, e or b.\n");
    //printf("%s", getenv("KONTO"));
  }
   
  
}//skriv_data

