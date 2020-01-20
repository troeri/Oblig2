#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>

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

  char *enavn, *splittnavn, *temp1, *siste, *brukernavn, *navn;
  int bindex = 0;
  int rc = 0;
  
  sqlite3 *db;
  sqlite3_stmt *res;
  sqlite3 *conn;
  
  sqlite3_open("bruker.db", &conn);
  rc = sqlite3_prepare_v2(conn, "select * from Bruker where uid>1000", 1000, &res, NULL);

  while (sqlite3_step(res) == SQLITE_ROW) {
    brukernavn = (char*) sqlite3_column_text(res, 0);
    navn = (char*) sqlite3_column_text(res, 4);

    strcpy(brukertabell[bindex].brukernavn, brukernavn);

    splittnavn = navn; //<-- splittnavn inneholder hele navn pluss ,,,etc
    temp1 = (char*)malloc(strlen(splittnavn)+1); //<-- allokerer minne i temp1 for å ta imot denne
    strcpy(temp1,splittnavn); //<-- tar en kopi av hele, trenger denne senere for å finne fornavn+mellomnavn

    enavn = strtok(splittnavn, " "); //<-- starter splitt for å finne etternavn pluss ,,,etc
    while (splittnavn) {
      siste = splittnavn;
      splittnavn = strtok(NULL, " "); //<-- når splittnavn er null, er siste på ordet før null, altså siste ord.
    }//endwhile

    enavn = siste; //<-- etternavn ferdig splittet, men med ,,,etc
    int navnlengde = strlen(temp1)-strlen(enavn); //<-- differansen i bokstavlengde inkludert ,,,etc
    snprintf(brukertabell[bindex].fornavn, navnlengde, "%s", temp1); //<--trekker fra lengden av etternavn,,,etc fra hele navn. setter inn.

    enavn = strtok(enavn, ","); //<-- tar bort ,,,etc fra etternavn
    strcpy(brukertabell[bindex++].etternavn, enavn); //<-- setter inn
    free(temp1);

  }//endwhile
    
  sqlite3_finalize(res);
  sqlite3_close(conn);
  
}//les_data


void skriv_data (int argc, char **argv, konto_t *brukertabell) {

  char* peker, *peker2;
  int k=0;
  peker = argv[1];
  
  if (getenv("KONTO") != NULL) {

    peker2 = getenv("KONTO");
    if (!strcmp(peker2, "b")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].brukernavn, brukertabell[k].fornavn, brukertabell[k].etternavn);
	k++;
	}//endwhile
    }//if

    if (!strcmp(peker2, "f")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].fornavn, brukertabell[k].etternavn, brukertabell[k].brukernavn);
	k++;
      }//endwhile
    }//if

    if (!strcmp(peker2, "e")) {
      printf("brukernavn!");
      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].etternavn, brukertabell[k].fornavn, brukertabell[k].brukernavn);
        k++;
      }//endwhile                                                                                                                                                                          
    }//if
    
    
  }//ifvariabel
  
  if (argc > 1 && getenv("KONTO") == NULL) {
    
    if (!strcmp(peker, "b")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].brukernavn, brukertabell[k].fornavn, brukertabell[k].etternavn);
	k++;
      }//endwhile
    }//if

    if (!strcmp(peker, "f")) {

      while (strlen(brukertabell[k].brukernavn) > 0) {
	printf("%s %s %s\n", brukertabell[k].fornavn, brukertabell[k].etternavn, brukertabell[k].brukernavn);
	k++;
      }//endwhile
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
  }//endif
   
}//skriv_data

