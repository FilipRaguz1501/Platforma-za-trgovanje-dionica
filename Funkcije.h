#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNKCIJE_H
#define FUNKCIJE_H
#define ISPISI_BUDZET(budzet) printf("\nVaš budžet iznosi: %.2f EUR.\n", budzet);
typedef struct Portfelj Portfelj;  // Naprijed deklaracija strukture Portfelj

typedef struct {
    char korisnickoIme[50];
    char lozinka[50];
    double budzet;
    Portfelj* portfelj;    // Dodavanje portfelj u strukturu Korisnik
} Korisnik;

typedef struct {
    char naziv[50];
    double cijena;
    int kolicina;
} Dionica;

struct Portfelj {
    Dionica* dionice;
    int brojDionica;
    int kapacitet;
};

Korisnik* kreirajKorisnika(const char* korisnickoIme, const char* lozinka, double budzet);
void obrisiKorisnika(Korisnik* korisnik);
Dionica* kreirajDionicu(const char* naziv, double cijena);
void obrisiDionicu(Dionica* dionica);
Portfelj* kreirajPortfelj();
void obrisiPortfelj(Portfelj* portfelj);
bool provjeri_bazu_podataka(FILE* datoteka, const char* korisnicko_ime, const char* lozinka);
Korisnik* prijava(FILE* datoteka, int brojKorisnika, Korisnik* korisnici);
//2 ->
Korisnik* registracija(FILE* datoteka, int brojKorisnika, Korisnik* korisnici);
bool kupiDionicu(Portfelj* portfelj, Dionica* dionica, int kolicina, double* budzet);
void prodajDionicu(Portfelj* portfelj, Dionica* dionica, int kolicina, double* budzet);
Dionica* provjeriDionicu(Dionica* dionice, int brojDionica);
void depozit(Korisnik* korisnik, double iznos);
int usporediDionicePoCijeni(const void* a, const void* b);
void sortirajPortfeljPoCijeni(Portfelj* portfelj);
int usporediDionicePoNazivuZaPretragu(const void* a, const void* b);
void sortirajPortfeljPoNazivu(Portfelj* portfelj);
Dionica* pretraziPortfelj(Portfelj* portfelj, char* nazivDionice);
void ispisiPortfelj(Portfelj* portfelj);
void ispisiBudzet(double budzet);
void obrisiDatotekuKorisnika(const char* imeDatoteke);
#endif
