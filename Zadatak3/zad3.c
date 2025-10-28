#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Definicija strukture
typedef struct Person* Position;

typedef struct Person {
    char firstName[MAX];
    char lastName[MAX];
    int birthYear;
    Position next;
} Person;

// Prototipovi funkcija
int inputPerson(Position);
int addToFront(Position);
int addToEnd(Position);
int printList(Position);
int findByLastName(Position);
Position findPrevious(char*, Position);
int deleteByLastName(Position);
int addAfter(Position);
int addBefore(Position);
int sortList(Position);
int writeToFile(Position, char*);
int readFromFile(Position, char*);

// Glavni program
int main(void) {
    Person head = { "", "", 0, NULL };
    int izbor = 0;

    while (1) {
        printf("       IZBORNIK OPCIJA       \n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Dodaj osobu na kraj\n");
        printf("3. Ispisi listu\n");
        printf("4. Pronadji osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("6. Dodaj osobu iza odredjene osobe\n");
        printf("7. Dodaj osobu ispred odredjene osobe\n");
        printf("8. Sortiraj listu po prezimenima\n");
        printf("9. Spremi listu u datoteku\n");
        printf("10. Ucitaj listu iz datoteke\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);
        while (getchar() != '\n');

        switch (izbor) {
        case 1:
            addToFront(&head);
            break;
        case 2:
            addToEnd(&head);
            break;
        case 3:
            printList(&head);
            break;
        case 4:
            findByLastName(&head);
            break;
        case 5:
            deleteByLastName(&head);
            break;
        case 6:
            addAfter(&head);
            break;
        case 7:
            addBefore(&head);
            break;
        case 8:
            sortList(&head);
            break;
        case 9:
            writeToFile(&head, "osobe.txt");
            break;
        case 10:
            readFromFile(&head, "osobe.txt");
            break;
        case 0:
            printf("Izlaz iz programa...\n");
            // oslobodi memoriju
            while (head.next != NULL) {
                Position temp = head.next;
                head.next = temp->next;
                free(temp);
            }
            return 0;
        default:
            printf("Nepostojeca opcija! Pokusajte ponovno.\n");
        }
    }
    return 0;
}

// Unos osobe
int inputPerson(Position p) {
    char buffer[100];
    int year = -1;

    // Ime
    do {
        printf("Unesite ime (max 9 znakova): ");
        scanf("%s", buffer);
        while (getchar() != '\n');
    } while (strlen(buffer) > 9);
    strcpy(p->firstName, buffer);

    // Prezime
    do {
        printf("Unesite prezime (max 9 znakova): ");
        scanf("%s", buffer);
        while (getchar() != '\n');
    } while (strlen(buffer) > 9);
    strcpy(p->lastName, buffer);

    // Godina roðenja
    do {
        printf("Unesite godinu rodenja: ");
        scanf("%d", &year);
        while (getchar() != '\n');
    } while (year < 0 || year > 2025);
    p->birthYear = year;

    return 0;
}

// Dodavanje osobe na poèetak liste
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

// Dodavanje osobe na kraj liste
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

// Ispis cijele liste
int printList(Position head) {
    head = head->next;

    if (!head) {
        printf("Lista je prazna!\n");
        return 0;
    }

    printf("\n--- Sadrzaj liste ---\n");
    while (head != NULL) {
        printf("%s %s, %d\n", head->firstName, head->lastName, head->birthYear);
        head = head->next;
    }
    printf("----------------------\n\n");
    return 0;
}

// Pronalaženje osobe po prezimenu
int findByLastName(Position head) {
    char lastName[100];

    do {
        printf("Unesite prezime koje zelite pronaci: ");
        scanf("%s", lastName);
        while (getchar() != '\n');
    } while (strlen(lastName) > 9);

    head = head->next;
    while (head != NULL && strcmp(head->lastName, lastName) != 0)
        head = head->next;

    if (head == NULL)
        printf("Osoba s prezimenom '%s' nije pronadena.\n", lastName);
    else
        printf("Pronadena osoba: %s %s, %d\n", head->firstName, head->lastName, head->birthYear);

    return 0;
}

// Pronalazak prethodnika osobe po prezimenu
Position findPrevious(char* lastName, Position head) {
    Position prev = head;

    while (prev->next != NULL && strcmp(prev->next->lastName, lastName) != 0)
        prev = prev->next;

    if (prev->next == NULL)
        return NULL;
    return prev;
}

// Brisanje osobe po prezimenu
int deleteByLastName(Position head) {
    char lastName[100];

    do {
        printf("Unesite prezime koje zelite obrisati: ");
        scanf("%s", lastName);
        while (getchar() != '\n');
    } while (strlen(lastName) > 9);

    Position prev = findPrevious(lastName, head);
    if (prev == NULL) {
        printf("Osoba s tim prezimenom ne postoji.\n");
        return -1;
    }

    Position toDelete = prev->next;
    prev->next = toDelete->next;
    free(toDelete);

    printf("Osoba je uspjesno obrisana.\n");
    return 0;
}

// (A) Dodavanje novog elementa iza odreðenog elementa
int addAfter(Position head) {
    char targetLastName[MAX];
    printf("Unesite prezime osobe iza koje zelite dodati novu osobu: ");
    scanf("%s", targetLastName);
    while (getchar() != '\n');

    Position current = head->next;
    while (current != NULL && strcmp(current->lastName, targetLastName) != 0)
        current = current->next;

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadena.\n", targetLastName);
        return -1;
    }

    Position newNode = (Position)malloc(sizeof(Person));
    if (!newNode) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    inputPerson(newNode);
    newNode->next = current->next;
    current->next = newNode;

    printf("Osoba dodana iza %s.\n", targetLastName);
    return 0;
}

// (B) Dodavanje novog elementa ispred odreðenog elementa
int addBefore(Position head) {
    char targetLastName[MAX];
    printf("Unesite prezime osobe ispred koje zelite dodati novu osobu: ");
    scanf("%s", targetLastName);
    while (getchar() != '\n');

    Position prev = head;
    while (prev->next != NULL && strcmp(prev->next->lastName, targetLastName) != 0)
        prev = prev->next;

    if (prev->next == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadena.\n", targetLastName);
        return -1;
    }

    Position newNode = (Position)malloc(sizeof(Person));
    if (!newNode) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    inputPerson(newNode);
    newNode->next = prev->next;
    prev->next = newNode;

    printf("Osoba dodana ispred %s.\n", targetLastName);
    return 0;
}

// (C) Sortiranje liste po prezimenima
int sortList(Position head) {
    if (head->next == NULL || head->next->next == NULL) {
        printf("Lista je prekratka za sortiranje.\n");
        return 0;
    }

    Position end = NULL;
    Position p, prev, temp;

    while (head->next != end) {
        prev = head;
        p = head->next;

        while (p->next != end) {
            if (strcmp(p->lastName, p->next->lastName) > 0) {
                temp = p->next;
                p->next = temp->next;
                temp->next = p;
                prev->next = temp;

                p = temp;
            }
            prev = p;
            p = p->next;
        }
        end = p;
    }

    printf("Lista je sortirana po prezimenima.\n");
    return 0;
}

// (D) Upis liste u datoteku
int writeToFile(Position head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    head = head->next;
    while (head != NULL) {
        fprintf(fp, "%s %s %d\n", head->firstName, head->lastName, head->birthYear);
        head = head->next;
    }

    fclose(fp);
    printf("Lista je uspjesno upisana u datoteku '%s'.\n", filename);
    return 0;
}

// (E) Èitanje liste iz datoteke
int readFromFile(Position head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    // Oèisti staru listu
    Position temp;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    while (!feof(fp)) {
        Position newNode = (Position)malloc(sizeof(Person));
        if (fscanf(fp, "%s %s %d", newNode->firstName, newNode->lastName, &newNode->birthYear) == 3) {
            newNode->next = head->next;
            head->next = newNode;
        }
        else {
            free(newNode);
            break;
        }
    }

    fclose(fp);
    printf("Lista je ucitana iz datoteke '%s'.\n", filename);
    return 0;
}
