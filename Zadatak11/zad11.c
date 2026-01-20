#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define HASH_SIZE 11

typedef struct _City {
    char name[MAX_LINE];
    int population;
    struct _City* left;
    struct _City* right;
} City;

typedef struct _Country {
    char name[MAX_LINE];
    City* cities;
    struct _Country* next;
} Country;

/* Stvara novi èvor stabla gradova */
City* createCityNode(char* name, int population) {
    City* new = (City*)malloc(sizeof(City));
    strcpy(new->name, name);
    new->population = population;
    new->left = new->right = NULL;
    return new;
}

/* Umeæe grad u stablo sortirano po broju stanovnika pa po nazivu */
City* insertCity(City* root, char* name, int population) {
    if (root == NULL)
        return createCityNode(name, population);

    if (population < root->population ||
        (population == root->population && strcmp(name, root->name) < 0))
        root->left = insertCity(root->left, name, population);
    else
        root->right = insertCity(root->right, name, population);

    return root;
}

/* Ispis stabla gradova inorder */
void printCities(City* root) {
    if (root == NULL)
        return;

    printCities(root->left);
    printf("\t%s, %d\n", root->name, root->population);
    printCities(root->right);
}

/* Pretraga gradova s vise stanovnika od zadanog broja */
void searchCities(City* root, int minPop) {
    if (root == NULL)
        return;

    searchCities(root->left, minPop);
    if (root->population > minPop)
        printf("\t%s, %d\n", root->name, root->population);
    searchCities(root->right, minPop);
}

/* Stvara novu drzavu */
Country* createCountry(char* name) {
    Country* new = (Country*)malloc(sizeof(Country));
    strcpy(new->name, name);
    new->cities = NULL;
    new->next = NULL;
    return new;
}

/* Hash funkcija: zbroj ASCII vrijednosti prvih 5 slova */
int hashFunction(char* name) {
    int sum = 0;
    for (int i = 0; i < 5 && name[i] != '\0'; i++)
        sum += (int)name[i];
    return sum % HASH_SIZE;
}

/* Umece drzavu u sortiranu vezanu listu (kolizije) */
Country* insertCountry(Country* head, char* name) {
    Country* new = createCountry(name);

    if (head == NULL || strcmp(name, head->name) < 0) {
        new->next = head;
        return new;
    }

    Country* current = head;
    while (current->next != NULL && strcmp(name, current->next->name) > 0)
        current = current->next;

    new->next = current->next;
    current->next = new;
    return head;
}

/* Pronalazi drzavu u vezanoj listi */
Country* findCountry(Country* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

/* Ucitava gradove iz datoteke */
City* loadCitiesFromFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke gradova.\n");
        return NULL;
    }

    City* root = NULL;
    char name[MAX_LINE];
    int population;

    while (fscanf(file, " %[^,],%d", name, &population) == 2)
        root = insertCity(root, name, population);

    fclose(file);
    return root;
}

/* Ucitava drzave u hash tablicu */
void loadCountriesFromFile(char* fileName, Country* hashTable[]) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju drzave.txt\n");
        return;
    }

    char name[MAX_LINE], cityFile[MAX_LINE];
    while (fscanf(file, "%s %s", name, cityFile) == 2) {
        int index = hashFunction(name);
        hashTable[index] = insertCountry(hashTable[index], name);

        Country* country = findCountry(hashTable[index], name);
        if (country != NULL)
            country->cities = loadCitiesFromFile(cityFile);
    }

    fclose(file);
}

/* Ispis hash tablice */
void printHashTable(Country* hashTable[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("\nHash index %d:\n", i);
        Country* current = hashTable[i];
        while (current != NULL) {
            printf("%s:\n", current->name);
            printCities(current->cities);
            current = current->next;
        }
    }
}

int main() {
    Country* hashTable[HASH_SIZE] = { NULL };

    loadCountriesFromFile("drzave.txt", hashTable);
    printHashTable(hashTable);

    char countryName[MAX_LINE];
    int minPop;

    printf("\nUnesite ime drzave: ");
    scanf("%s", countryName);

    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &minPop);

    int index = hashFunction(countryName);
    Country* country = findCountry(hashTable[index], countryName);

    if (country == NULL)
        printf("Drzava nije pronadena.\n");
    else {
        printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", countryName, minPop);
        searchCities(country->cities, minPop);
    }

    return 0;
}
