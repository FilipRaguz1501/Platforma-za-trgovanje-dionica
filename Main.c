#include <stdio.h>
#include "Funkcije.h"

int main() {
	// Stvaranje nekoliko primjeraka dionica
	Dionica* dionica1 = novaDionica("AAPL", 172.46);
	Dionica* dionica2 = novaDionica("MSFT", 321.50);
	Dionica* dionica3 = novaDionica("AMZN", 116.08);
	Dionica* dionica4 = novaDionica("NVDA", 372.89);
	Dionica* dionica5 = novaDionica("GOOGL", 124.07);
	Dionica* dionica6 = novaDionica("GOOG", 124.87);
	Dionica* dionica7 = novaDionica("BRK.B", 319.64);
	Dionica* dionica8 = novaDionica("META", 252.43);
	Dionica* dionica9 = novaDionica("TSLA", 185.57);
	Dionica* dionica10 = novaDionica("UNH", 476.25);
	Dionica* dionica11 = novaDionica("XOM", 105.37);
	Dionica* dionica12 = novaDionica("JNJ", 154.70);
	Dionica* dionica13 = novaDionica("JPM", 135.68);
	Dionica* dionica14 = novaDionica("V", 221.22);
	Dionica* dionica15 = novaDionica("PG", 144.55);
	Dionica* dionica16 = novaDionica("LLY", 423.45);
	Dionica* dionica17 = novaDionica("MA", 365.48);
	Dionica* dionica18 = novaDionica("HD", 290.86);
	Dionica* dionica19 = novaDionica("MRK", 112.15);
	Dionica* dionica20 = novaDionica("AVGO", 693.55);

	// Kreiranje korisnika i dodavanje dionica u portfelj
	Korisnik* korisnik = kreirajKorisnika("JohnDoe", "password", 10000.0);
	dodaj_dionicu(&(korisnik->portfelj), dionica1);
	dodaj_dionicu(&(korisnik->portfelj), dionica2);
	dodaj_dionicu(&(korisnik->portfelj), dionica3);
	dodaj_dionicu(&(korisnik->portfelj), dionica4);
	dodaj_dionicu(&(korisnik->portfelj), dionica5);

	// Ispisivanje informacija o dionicama u portfelju
	for (int i = 0; i < korisnik->portfelj.brojDionica; i++) {
		ispisDionice(korisnik->portfelj.dionice[i]);
	}

	// Izraèunavanje vrijednosti portfelja
	izracunaj_vrijednost_portfelja(&(korisnik->portfelj));

	// Uklanjanje dionice iz portfelja
	ukloni_dionicu(&(korisnik->portfelj), "AAPL");

	// Ponovno izraèunavanje vrijednosti portfelja nakon uklanjanja dionice
	izracunaj_vrijednost_portfelja(&(korisnik->portfelj));

	// Oslobaðanje resursa
	oslobodiDionicu(dionica1);
	oslobodiDionicu(dionica2);
	oslobodiDionicu(dionica3);
	oslobodiDionicu(dionica4);
	oslobodiDionicu(dionica5);
	oslobodiPortfelj(&(korisnik->portfelj));
	free(korisnik);

	return 0;
}
