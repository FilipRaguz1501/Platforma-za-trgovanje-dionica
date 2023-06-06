#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNKCIJE_H
#define FUNKCIJE_H
#define MAX_IME 50
#define MAX_LOZINKA 20
#include <stdio.h>

typedef struct {
	char naziv[10]; //2. Odabir konkretnih složenih tipova podataka za rad sa specifiènim objektima.
	float cijena;
	int brojJedinica;  // 1. Odabir konkretnih primitivnih tipova podataka za rad s cjelobrojnim i realnim konstantama.
} Dionica;

typedef struct {
	Dionica** dionice;  // Pokazivaè na pokazivaèe na Dionica
	int brojDionica;   // Trenutni broj dionica u portfelju
} Portfelj;

typedef struct { //3. Primjena typedef sa strukturama i unijama, po potrebi s enum tipovima podataka tamo gdje
	char ime[MAX_IME]; // 4. Imenovanje identifikatora (varijabli, konstanti, polja, funkcija, pokazivaèa…) 
	char lozinka[MAX_LOZINKA];
	Portfelj portfelj;
	double budzet;
} Korisnik;

Dionica* novaDionica(const char* naziv, float cijena);

// Implementacija kao inline funkcija
static inline void ispisDionice(const Dionica* dionica) { //7.Ako su funkcije jednostavne koristiti makro funkcije ili inline funkcije
	if (dionica == NULL) {
		fprintf(stderr, "Pogreška: Dionica ne može biti NULL\n");
		return;
	}
	printf("Naziv dionice: %s, Cijena: %.2f\n", dionica->naziv, dionica->cijena);
}

void oslobodiPortfelj(Portfelj* portfelj);
void oslobodiDionicu(Dionica* dionica);
int ukloni_dionicu(Portfelj* portfelj, char* naziv);
int dodaj_dionicu(Portfelj* portfelj, Dionica* novaDionica);
void izracunaj_vrijednost_portfelja(Portfelj* portfelj);
Korisnik* kreirajKorisnika(char* ime, char* lozinka, double polog);
void dodajKorisnikaUDatoteku(Korisnik* korisnik);
int provjeriKorisnika(const char* ime, const char* lozinka);
int dodajNovacKorisniku(const char* ime, double iznos);
Korisnik* registracija();
Korisnik* prijava();
#endif
