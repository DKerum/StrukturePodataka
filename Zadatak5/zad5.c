#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

typedef struct Node* Position;
typedef struct Node {
    int value;
    Position next;
} Node;

// deklaracije funkcija
int checkFile();
int readFile(Position);
int push(Position, int);
int pop(Position, char);
int printResult(Position);

int main() {
    Node head = { 0, NULL };

    if (checkFile() == EXIT_FAILURE) {
        printf("Datoteka nije ispravna ili ne postoji.\n");
        return EXIT_FAILURE;
    }

    if (readFile(&head) == EXIT_FAILURE) {
        printf("Greska pri obradi izraza.\n");
        return EXIT_FAILURE;
    }

    printResult(head.next);

    return EXIT_SUCCESS;
}

// provjera ispravnosti postfix izraza
int checkFile() {
    FILE* f = fopen("postifx.txt", "r");
    if (!f) return EXIT_FAILURE;

    char temp[20];
    int numCount = 0, opCount = 0, x;

    while (fscanf(f, "%s", temp) == 1) {
        printf("%s ", temp);
        if (sscanf(temp, "%d", &x) == 1)
            numCount++;
        else if (*temp == '+' || *temp == '-' || *temp == '*' || *temp == '/' || *temp == '%')
            opCount++;
        else {
            fclose(f);
            return EXIT_FAILURE;
        }
    }
    fclose(f);

    if (numCount != opCount + 1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

// èitanje izraza i raèunanje rezultata
int readFile(Position head) {
    FILE* f = fopen("postifx.txt", "r");
    if (!f) return EXIT_FAILURE;

    char token[20];
    int broj;

    while (fscanf(f, "%s", token) == 1) {
        if (sscanf(token, "%d", &broj) == 1) {
            push(head, broj);
        }
        else {
            if (!head->next || !head->next->next) {
                printf("\nNedovoljno brojeva za operaciju '%c'\n", *token);
                fclose(f);
                return EXIT_FAILURE;
            }
            pop(head, *token);
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}

// dodaj broj na stog
int push(Position head, int broj) {
    Position novi = (Position)malloc(sizeof(Node));
    if (!novi) return EXIT_FAILURE;

    novi->value = broj;
    novi->next = head->next;
    head->next = novi;

    return EXIT_SUCCESS;
}

// izvrši operaciju nad dva gornja elementa stoga
int pop(Position head, char op) {
    Position first = head->next;        // vrh stoga (drugi operand)
    Position second = first->next;      // ispod njega (prvi operand)

    int rezultat = 0;

    switch (op) {
    case '+': rezultat = second->value + first->value; break;
    case '-': rezultat = second->value - first->value; break;
    case '*': rezultat = second->value * first->value; break;
    case '/':
        if (first->value == 0) {
            printf("\nDijeljenje s nulom!\n");
            return EXIT_FAILURE;
        }
        rezultat = second->value / first->value;
        break;
    case '%': rezultat = second->value % first->value; break;
    default:
        printf("\nNepoznata operacija: %c\n", op);
        return EXIT_FAILURE;
    }

    // ažuriraj stog
    second->value = rezultat;
    head->next = second;
    free(first);

    return EXIT_SUCCESS;
}

// ispis rezultata
int printResult(Position q) {
    if (!q) {
        printf("\nStog je prazan!\n");
        return EXIT_FAILURE;
    }

    printf("\nKonacni rezultat: %d\n", q->value);
    free(q);
    return EXIT_SUCCESS;
}
