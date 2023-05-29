#ifndef KORISNIK_H
#define KORISNIK_H

#include "Portfelj.h"

typedef struct Korisnik
{
	char ime[50];
	char lozinka[50];
	Portfelj* portfelj;
	double proracun;
} Korisnik;

Korisnik* stvori_korisnik(char* ime, char* lozinka, double proracun);
void provjeri_portfelj(Korisnik* korisnik);
void sortiraj_portfelj(Korisnik* korisnik);
void pretrazi_portfelj(Korisnik* korisnik, char* ime_dionice);
void polog(Korisnik* korisnik, double iznos);
void kupi_dionicu(Korisnik* korisnik, char* ime_dionice, float cijena);
void prodaj_dionicu(Korisnik* korisnik, char* ime_dionice);

#endif