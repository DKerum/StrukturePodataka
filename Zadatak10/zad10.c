#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

//pod a)
/*
typedef struct _City {
	char name[MAX_LINE];
	int population;
	struct _City *left, * right;
}City;

typedef struct _Country {
	char name[MAX_LINE];
	City* cities;
	struct _Country* next;
}Country;

City* createCityNode(char* name, int population) {
	City* new = (City*)malloc(sizeof(City));
	strcpy(new->name, name);
	new->population = population;
	new->left = NULL;
	new->right = NULL;
	return new;
}

City* InsertCity(City* root, char* name, int population) {
	if (root == NULL)
		return createCityNode(name, population);

	if (population < root->population || (population == root->population && strcmp(name, root->name) < 0))
		root->left = InsertCity(root->left, name, population);
	else
		root->right = InsertCity(root->right, name, population);

	return root;
}

void printCities(City* root) {
	if (root == NULL)
		return 0;
	printCities(root->left);
	printf("\t%s, %d\n", root->name, root->population);
	printCities(root->right);
}

void searchCities(City* root, int minPop) {
	if (root == NULL)
		return 0;
	searchCities(root->left, minPop);
	if (root->population > minPop)
		printf("\t%s, %d\n", root->name, root->population);
	searchCities(root->right, minPop);
}

Country* createCountry(char* name) {
	Country* new = (Country*)malloc(sizeof(Country));
	strcpy(new->name, name);
	new->cities = NULL;
	new->next = NULL;
	return new;
}

Country* InsertCountry(Country* head, char* name) {
	Country* new = createCountry(name);
	if (head == NULL || strcmp(name, head->cities) < 0) {
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

void printCountries(Country* head) {
	while (head != NULL) {
		printf("%s:\n", head->name);
		printCities(head->cities);
		head = head->next;
	}
}

Country* findCountry(Country* head, char* name) {
	while (head != NULL) {
		if (strcmp(head->name, name) == 0)
			return head;
		head = head->next;
	}
	return NULL;
}

City* loadCitiesFromFile(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Greska 1");
		return NULL;
	}

	City* root = NULL;
	char name[MAX_LINE];
	int population;
	while (fscanf(file, "%[^,],%d\n", name, &population) == 2)
		root = InsertCity(root, name, population);

	fclose(file);
	return root;
}

Country* loadCountriesFromFile(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Greska 2");
		return NULL;
	}

	Country* head = NULL;
	char name[MAX_LINE], File[MAX_LINE];
	while (fscanf(file, "%s %s\n", name, File) == 2) {
		head = InsertCountry(head, name);
		Country* country = findCountry(head, name);
		if (country != NULL)
			country->cities = loadCitiesFromFile(File);
	}
	fclose(file);
	return head;
}

int main() {

	char countryName[MAX_LINE];
	int minPop;
	char countryFile[] = "drzave.txt";
	Country* countries = loadCountriesFromFile(countryFile);

	if (countries == NULL) {
		printf("Greska 3");
		return 1;
	}

	printCountries(countries);

	printf("\nUnesite ime drzave za pretragu: "); scanf("%s", countryName);
	printf("\nUnesite minimalan broj stanovnika: "); scanf("%d", &minPop);

	Country* selected = findCountry(countries, countryName);
	if (selected == NULL)
		printf("Drzava nije pronadena.");
	else {
		printf("Gradovi u drzavi %s sa vise od %d stanovnika:\n", countryName, minPop);
		searchCities(selected->cities, minPop);
	}

	return 0;
}
*/


//pod b)
typedef struct _City {
	char name[MAX_LINE];
	int population;
	struct _City* next;
}City;

typedef struct _Country {
	char name[MAX_LINE];
	City* cities;
	struct _Country* left, * right;
}Country;

City* createCity(char* name, int population) {
	City* new = (City*)malloc(sizeof(City));
	strcpy(new->name, name);
	new->population = population;
	new->next = NULL;
	return new;
}

City* insertCity(City* head, City* new) {
	if (!head || new->population > head->population || (new->population == head->population && strcmp(new->name, head->name) < 0)) {
		new->next = head;
		return new;
	}

	City* current = head;
	while (current->next && (current->next->population > new->population || (current->next->population == new->population && strcmp(current->next->name, new->name) < 0)))
		current = current->next;

	new->next = current->next;
	current->next = new;
	return head;
}

Country* createCountry(char* name) {
	Country* new = (Country*)malloc(sizeof(Country));
	strcpy(new->name, name);
	new->cities = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

Country* insertCountry(Country* root, Country* new) {
	if (!root)
		return new;

	if (strcmp(new->name, root->name) < 0)
		root->left = insertCountry(root->left, new);
	else if (strcmp(new->name, root->name) > 0)
		root->right = insertCountry(root->right, new);
	return root;
}

City* loadCities(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("Greska 1");
		return NULL;
	}

	City* head = NULL;
	char name[MAX_LINE];
	int population;

	while (fscanf(file, "%[^,],%d\n", name, &population) == 2) {
		City* new = createCity(name, population);
		head = insertCity(head, new);
	}

	fclose(file);
	return head;
}

void printCities(City* head) {
	while (head) {
		printf("\t%s, %d\n", head->name, head->population);
		head = head->next;
	}
}

void printCountries(Country* root) {
	if (!root)
		return;

	printCountries(root->left);
	printf("%s:\n", root->name);
	printCities(root->cities);
	printCountries(root->right);
}

Country* loadCountries(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("Greska 2");
		return NULL;
	}

	Country* root = NULL;
	char name[MAX_LINE], fileCity[MAX_LINE];

	while (fscanf(file, "%s %s\n", name, fileCity) == 2) {
		Country* new = createCountry(name);
		new->cities = loadCities(fileCity);
		root = insertCountry(root, new);
	}

	fclose(file);
	return root;
}

void findCities(Country* root, char* nameCountry, int minPop) {
	if (!root)
		return;

	if (strcmp(nameCountry, root->name) < 0)
		findCities(root->left, nameCountry, minPop);
	else if (strcmp(nameCountry, root->name) > 0)
		findCities(root->right, nameCountry, minPop);
	else {
		printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", nameCountry, minPop);
		City* current = root->cities;
		while (current) {
			if (current->population > minPop)
				printf("\t%s, %d\n", current->name, current->population);
			current = current->next;
		}
	}
}

int main() {

	char wanted[MAX_LINE];
	int minPop;

	Country* root = loadCountries("drzave.txt");
	if (!root)
		return 1;

	printCountries(root);

	printf("\nUnesite naziv drzave: "); scanf("%s", wanted);
	printf("Unesite minimalan broj stanovnika: "); scanf("%d", &minPop);

	findCities(root, wanted, minPop);

	return 0;
}