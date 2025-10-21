#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

typedef struct {
    char ime[MAX_LEN];
    char prezime[MAX_LEN];
    int bodovi;
} stud;

//funkcija koja broji studente u datoteci

int brojStudenata(){
	FILE *dat = fopen("Studenti.txt", "r");
	if(dat == NULL)
		return -1;
	int br = 0;
	//char buffer[150];
	int c;
	while((c = fgetc(dat)) != EOF) {
		if(c == '\n') {
			br++;
		}
	}
	
	fclose(dat);
	return br;
}
//bolja praksa koristiti buffer
//definirati sve konstante npr. za buffer, predložila 1024
//definiraj na vrhu filea sto znaci error -1 
	//define File cant open (-1)


//Funkcija za unos studenata u program
stud* unosStudenata(FILE *dat, int n){

	stud* studenti = (stud*)malloc(n * sizeof(stud));
	if(studenti == NULL){
		return NULL;
	}

	for(int i = 0;i<n;i++){
		fscanf(dat, "%s %s %d",studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}
	return studenti;
}
//Ne koristit file pointere nego svaki put fopen i fclose



//Funkcija za ispis svih studenata i relativnih bodova
void printStudent(stud* studenti, int br, int max) {

    for (int i = 0; i < br; i++) {

        float rel = (float)studenti[i].bodovi / max * 100;

        printf("Ime i prezime: %s %s\n", studenti[i].ime, studenti[i].prezime);
        printf("Broj bodova: %d\n", studenti[i].bodovi);
        printf("Relativan broj bodova: %.2f%%\n\n", rel);

    }
}

//Oslobodi memoriju kad zavrsis sa pointeron na studenti sa free

int main() 
{
	
	FILE *dat = fopen("Studenti.txt", "r");

	int br = brojStudenata();

	stud* studenti = unosStudenata(dat, br);

	printStudent(studenti, br, 50);

	fclose(dat);
	return 0;
}
//deklariraj funkcije prije maina pa piši nakon maina