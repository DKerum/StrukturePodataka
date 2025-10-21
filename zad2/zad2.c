#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX 10

//Definicija strukture i typedefa
typedef struct Person* Position;

typedef struct Person {
    char firstName[MAX];
    char lastName[MAX];
    int birthYear;
    Position next;
} Person;

//Prototipovi funkcija
int inputPerson(Position);
int addToFront(Position);
int addToEnd(Position);
int printList(Position);
int findByLastName(Position);
Position findPrevious(char*, Position);
int deleteByLastName(Position);

int main(void) {

    Person head = { "", "", 0, NULL };

    // Dodaj tri elementa (dva na početak i jedan na kraj)
    addToFront(&head);
    addToFront(&head);
    addToEnd(&head);

    // Pronađi osobu po prezimenu
    findByLastName(&head);

    // Ispiši cijelu listu
    printList(&head);

    // Obriši osobu i ponovno ispiši listu
    deleteByLastName(&head);
    printList(&head);

    return 0;
}

//Dodavanje osobe na početak liste
int addToFront(Position head) {
    Position newNode = (Position)malloc(sizeof(Person));
    if (!newNode) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    inputPerson(newNode);
    newNode->next = head->next;
    head->next = newNode;
    return 0;
}

//Dodavanje osobe na kraj liste
int addToEnd(Position head) {
    while (head->next != NULL)
        head = head->next;

    Position newNode = (Position)malloc(sizeof(Person));
    if (!newNode) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    inputPerson(newNode);
    newNode->next = NULL;
    head->next = newNode;
    return 0;
}

//Ispis cijele liste
int printList(Position head) {
    head = head->next; // preskoči "head" čvor

    if (!head) {
        printf("Lista je prazna!\n");
        return 0;
    }

    printf("\n--- Sadrzaj liste ---\n");
    while (head != NULL) {
        printf("%s %s, %d (adr: %p)\n", head->firstName, head->lastName, head->birthYear, head);
        head = head->next;
    }
    printf("----------------------\n\n");
    return 0;
}

//Unos podataka o osobi
int inputPerson(Position p) {
    char* buffer = (char*)malloc(100 * sizeof(char));
    int year = -1;

    // unos imena
    do {
        printf("Unesite ime (max 9 znakova): ");
        scanf("%s", buffer);
        while (getchar() != '\n');
    } while (strlen(buffer) > 9);
    strcpy(p->firstName, buffer);

    // unos prezimena
    do {
        printf("Unesite prezime (max 9 znakova): ");
        scanf("%s", buffer);
        while (getchar() != '\n');
    } while (strlen(buffer) > 9);
    strcpy(p->lastName, buffer);

    // unos godine rođenja
    do {
        printf("Unesite godinu rodenja: ");
        scanf("%d", &year);
        while (getchar() != '\n');
    } while (year < 0 || year > 2025);
    p->birthYear = year;

    free(buffer);
    return 0;
}

//Pronalaženje osobe po prezimenu
int findByLastName(Position head) {
    char* lastName = (char*)malloc(100 * sizeof(char));

    do {
        printf("Unesite prezime koje zelite pronaci: ");
        scanf("%s", lastName);
        while (getchar() != '\n');
    } while (strlen(lastName) > 9);

    head = head->next; // preskoči head
    while (head != NULL && strcmp(head->lastName, lastName) != 0)
        head = head->next;

    if (head == NULL)
        printf("Osoba s prezimenom '%s' nije pronadena.\n", lastName);
    else
        printf("Pronadena osoba na adresi: %p\n", head);

    free(lastName);
    return 0;
}

//Pomoćna funkcija: pronalazi prethodnika traženog prezimena
Position findPrevious(char* lastName, Position head) {
    Position prev = NULL;

    while (head != NULL && strcmp(head->lastName, lastName) != 0) {
        prev = head;
        head = head->next;
    }

    if (head == NULL)
        return NULL;

    return prev;
}

//Brisanje osobe po prezimenu
int deleteByLastName(Position head) {
    char* lastName = (char*)malloc(100 * sizeof(char));

    do {
        printf("Unesite prezime koje zelite obrisati: ");
        scanf("%s", lastName);
        while (getchar() != '\n');
    } while (strlen(lastName) > 9);

    // pronađi prethodni element
    Position prev = findPrevious(lastName, head);
    if (prev == NULL || prev->next == NULL) {
        printf("Osoba s tim prezimenom ne postoji.\n");
        free(lastName);
        return -1;
    }

    // briši traženi element
    Position toDelete = prev->next;
    prev->next = toDelete->next;
    free(toDelete);
    free(lastName);

    printf("Osoba je uspjesno obrisana.\n");
    return 0;
}
