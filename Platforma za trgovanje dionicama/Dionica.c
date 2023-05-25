#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dionica.h"

Dionica* nova_dionica(char* naziv, float cijena)
{
	Dionica* d = malloc(sizeof(Dionica));
	if (d == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		exit(1);
	}
	strncpy(d->naziv, naziv, sizeof(d->naziv) - 1);
	d->cijena = cijena;
	d->datumKupnje = (unsigned int)time(NULL);

	return d;
}

void ispis_dionice(Dionica* d)
{
	printf("Dionica: %s, Cijena: %.2f\n", d->naziv, d->cijena);
}

void pohrani_dionicu_u_datoteku(FILE* datoteka, Dionica* d)
{
	if (datoteka == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		exit(1);
	}

	fprintf(datoteka, "%s %.2f %lu\n", d->naziv, d->cijena, d->datumKupnje);
}


Dionica* citaj_dionicu_iz_datoteke(FILE* datoteka)
{
	if (datoteka == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		exit(1);
	}

	Dionica* d = malloc(sizeof(Dionica));
	if (d == NULL)
	{
		printf("Greska pri alociranju memorije.\n");
		exit(1);
	}

	size_t procitano = fread(d, sizeof(Dionica), 1, datoteka);
	if (procitano != 1)
	{
		printf("Greska pri citanju dionice iz datoteke.\n");
		free(d);
		return NULL;
	}

	return d;
}


// funkcija za sortiranje po imenu
int usporedi_po_imenu(const void* a, const void* b)
{
	Dionica* d1 = *(Dionica**)a;
	Dionica* d2 = *(Dionica**)b;

	return strcmp(d1->naziv, d2->naziv);
}

void sortiraj_po_imenu(Dionica** dionice, int broj_dionica)
{
	qsort(dionice, broj_dionica, sizeof(Dionica*), usporedi_po_imenu);
}

// funkcija za sortiranje po cijeni (od najveće prema najmanjoj)
int usporedi_po_cijeni(const void* a, const void* b)
{
	Dionica* d1 = *(Dionica**)a;
	Dionica* d2 = *(Dionica**)b;

	return d2->cijena - d1->cijena;
}

void sortiraj_po_cijeni(Dionica** dionice, int broj_dionica)
{
	qsort(dionice, broj_dionica, sizeof(Dionica*), usporedi_po_cijeni);
}

// funkcija za sortiranje po datumu kupnje (od najstarijeg prema najnovijem)
int usporedi_po_datumu_kupnje(const void* a, const void* b)
{
	Dionica* d1 = *(Dionica**)a;
	Dionica* d2 = *(Dionica**)b;

	return d1->datumKupnje - d2->datumKupnje;
}

void sortiraj_po_datumu_kupnje(Dionica** dionice, int broj_dionica)
{
	qsort(dionice, broj_dionica, sizeof(Dionica*), usporedi_po_datumu_kupnje);
}

Dionica* binarno_pretrazi_dionicu(Dionica** dionice, int broj_dionica, char* naziv)
{
	if (dionice == NULL)
		return NULL;

	int lijevo = 0, desno = broj_dionica - 1;

	while (lijevo <= desno)
	{
		int sredina = lijevo + (desno - lijevo) / 2;

		// Provjeri je li naziv u sredini
		int rezultat = strncmp(dionice[sredina]->naziv, naziv, strlen(naziv));

		if (rezultat == 0)
			return dionice[sredina];
		else if (rezultat < 0)
			lijevo = sredina + 1;
		else
			desno = sredina - 1;
	}

	// Ako nismo našli element, vratiti NULL
	return NULL;
}




void zamijeni_dionice(Dionica** d1, Dionica** d2)
{
	Dionica* temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

