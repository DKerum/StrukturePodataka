
#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_string 50

typedef struct student {
	char ime[max_string];
	char prezime[max_string];
	int bodovi;
}stud;

//funkcija koja broji studente u datoteci

int brojStudenata(){
	FILE *dat = fopen("Studenti.txt", "r");
	if(dat == NULL)
		return -1;
	int br = 0;
	char buffer[150];
	int c;
	while((c = fgetc(dat)) != EOF) {
		if(c == '\n') {
			br++;
		}
	}
	// Ako datoteka nije prazna i ne završava novim redom, povećaj broj za 1
	/*fseek(file, -1, SEEK_END);
	if(ftell(file) > 0 && fgetc(file) != '\n') {
		br++;
	}
		br++;
	*/
	fclose(dat);
	return br;
}

int main() 
{
	return 0;
}