#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polinom* position;
typedef struct polinom {
	int koef;
	int eks;
	position next;
}pol;

void Sort(position);
int In(position, char*);
int Print(position);
int Sum(position, position, position);
int Multiply(position, position, position);

int main() {

	pol Head1, Head2, Heads, Headm;

	Head1.next = NULL;
	Head2.next = NULL;
	Heads.next = NULL;
	Headm.next = NULL;

	In(&Head1, "pol1.txt");
	In(&Head2, "pol2.txt");

	printf("Ispis 1. polinoma:\n");
	Print(Head1.next);

	printf("Ispis 2. polinoma:\n");
	Print(Head2.next);

	Sum(&Head1, &Head2, &Heads);
	printf("Zbroj:\n");
	Print(Heads.next);

	Multiply(&Head1, &Head2, &Headm);
	printf("Umnozak:\n");
	Print(Headm.next);

	return 0;
}

void Sort(position p) {
	if (p == NULL || p->next == NULL)
		return;

	position i, j;
	int tempk, tempe;

	for (i = p->next; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (i->eks < j->eks) {
				tempk = i->koef;
				tempe = i->eks;
				i->koef = j->koef;
				i->eks = j->eks;
				j->koef = tempk;
				j->eks = tempe;
			}
		}
	}
}


int In(position p, char* file) {

	FILE* fp = NULL;
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Greska 1");
		return 1;
	}

	char niz[100];
	while (fgets(niz, sizeof(niz), fp)) {
		position q = (position)malloc(sizeof(pol));
		if (q == NULL) {
			printf("Greska 2");
			return 1;
		}

		int br = 0;
		char* pt = niz;
		position prev, temp;
		while (sscanf(pt, "%d %d%n", &q->koef, &q->eks, &br) == 2) {
			pt += br;
			prev = p;
			temp = p->next;

			while (temp != NULL && (temp->eks < q->eks)) {
				prev = temp;
				temp = temp->next;
			}

			q->next = temp;
			prev->next = q;
			q = (position)malloc(sizeof(pol));
		}
	}

	fclose(fp);
	Sort(p);

	return 0;
}

int Print(position p) {

	while (p != NULL) {
		printf("Koef: %d, Eks: %d\n", p->koef, p->eks);
		p = p->next;
	}
	puts("");
	return 0;
}

int Sum(position p, position q, position r) {
	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL) {
		position s = (position)malloc(sizeof(pol));
		if (s == NULL) {
			printf("Greska 3");
			return 1;
		}
		s->next = NULL;

		if (p->eks == q->eks) {
			s->eks = p->eks;
			s->koef = p->koef + q->koef;
			p = p->next;
			q = q->next;
		}

		else if (p->eks < q->eks) {
			s->eks = q->eks;
			s->koef = q->koef;
			q = q->next;
		}

		else {
			s->eks = p->eks;
			s->koef = p->koef;
			p = p->next;
		}

		r->next = s;
		r = s;
	}

	position temp = (p != NULL) ? p : q;

	while (temp != NULL) {
		position a = (position)malloc(sizeof(pol));;
		if (a == NULL) {
			printf("Greska 4");
			return 1;
		}
		a->eks = temp->eks;
		a->koef = temp->koef;
		a->next = NULL;
		r->next = a;
		r = a;
		temp = temp->next;
	}

	return 0;
}

int Multiply(position p, position q, position s) {
	position a = p->next;
	position b = q->next;

	while (a != NULL) {
		b = q->next;
		while (b != NULL) {
			int newk, newe;

			newk = a->koef * b->koef;
			newe = a->eks + b->eks;

			position temp = s;
			while (temp->next != NULL && temp->next->eks > newe)
				temp = temp->next;

			if (temp->next != NULL && temp->next->eks == newe) {
				temp->next->koef += newk;
			}

			else {
				position r = (position)malloc(sizeof(pol));
				if (r == NULL) {
					printf("Greska 5");
					return 1;
				}

				r->koef = newk;
				r->eks = newe;
				r->next = temp->next;
				temp->next = r;
			}
			b = b->next;
		}
		a = a->next;
	}

	Sort(s);
	return 0;
}