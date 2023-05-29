#define _CRT_SECURE_NO_WARNINGS
#ifndef DIONICA_H
#define DIONICA_H

#include <stdio.h>
typedef struct Dionica
{
	char naziv[10];
	float cijena;
	unsigned int datumKupnje;
} Dionica;

Dionica* nova_dionica(char* naziv, float cijena);
void ispis_dionice(Dionica* d);
void pohrani_dionicu_u_datoteku(FILE* datoteka, Dionica* d);
Dionica* citaj_dionicu_iz_datoteke(FILE* datoteka);
void zamijeni_dionice(Dionica** d1, Dionica** d2);
int usporedi_po_imenu(const void* a, const void* b);
void sortiraj_po_imenu(Dionica** dionice, int brojDionica);
int usporedi_po_cijeni(const void* a, const void* b);
void sortiraj_po_cijeni(Dionica** dionice, int brojDionica);
int usporedi_po_datumu(const void* a, const void* b);
void sortiraj_po_datumu_kupnje(Dionica** dionice, int broj_dionica);
Dionica* binarno_pretrazi_dionicu(Dionica** dionice, int broj_dionica, char* naziv);


#endif