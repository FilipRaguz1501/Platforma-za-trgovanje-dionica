#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funkcije.h"
#define MAX 100000

Dionica* novaDionica(const char* naziv, float cijena) {
	Dionica* dionica = (Dionica*)malloc(sizeof(Dionica)); //14. Koristiti funkcije malloc(), calloc(), realloc(), free() – neku od njih, ako ne i sve.
	if (dionica == NULL) { //11. Zaštita parametara kod svih funkcija.

		perror("Neuspjela alokacija memorije za dionicu"); //19. Upravljati s pogreškama, errno, perror(), strerror(), feof(), ferror() – neku od njih ako ne sve.

		return NULL;
	}
	strncpy(dionica->naziv, naziv, sizeof(dionica->naziv) - 1);
	dionica->naziv[sizeof(dionica->naziv) - 1] = '\0';
	dionica->cijena = cijena;
	return dionica;
}

Portfelj* kreirajPortfelj() {
	Portfelj* noviPortfelj = (Portfelj*)malloc(sizeof(Portfelj));
	if (noviPortfelj == NULL) {
		fprintf(stderr, "Neuspjelo alociranje memorije za portfelj\n");
		return NULL;
	}
	noviPortfelj->dionice = NULL;  // Inicijalno postavite na NULL
	noviPortfelj->brojDionica = 0; // Nema dionica u novom portfelju
	return noviPortfelj;
}

void oslobodiPortfelj(Portfelj* portfelj) {
	if (portfelj == NULL) {
		fprintf(stderr, "Pogreška: Pokazivaè na portfelj je NULL\n");
		return;
	}

	// Oslobodite memoriju za sve dionice
	for (int i = 0; i < portfelj->brojDionica; i++) {
		oslobodiDionicu(portfelj->dionice[i]);
		portfelj->dionice[i] = NULL;  // Postavite pokazivaè na NULL da sprijeèite double free
	}

	// Oslobodite memoriju za niz pokazivaèa na dionice
	free(portfelj->dionice);
	portfelj->dionice = NULL;  // Postavite pokazivaè na NULL da sprijeèite double free

	// Oslobodite memoriju za sam portfelj
	free(portfelj); //15. Sigurno brisanje memorije koja je dinamièki zauzeta, anuliranje memorijskog prostora, provjera
//pokazivaèa kako se ne bi dogodila pogreška double free() i anuliranje svih pokazivaèa koji su bili
//usmjereni na memorijski prostor koji se dinamièki zauzeo.
}

void oslobodiDionicu(Dionica* dionica) {
	if (dionica == NULL) {
		fprintf(stderr, "Pogreška: Pokazivaè na dionicu je NULL\n");
		return;
	}

	//free(dionica->naziv);
	//dionica->naziv = NULL;  // Postavite pokazivaè na NULL da sprijeèite double free

	free(dionica);
}

int dodaj_dionicu(Portfelj* portfelj, Dionica* novaDionica) {
	// Provjera da li je nova dionica veæ u portfelju
	for (int i = 0; i < portfelj->brojDionica; ++i) {
		if (strcmp(portfelj->dionice[i]->naziv, novaDionica->naziv) == 0) {
			// Ako dionica veæ postoji, ažuriraj broj jedinica
			portfelj->dionice[i]->brojJedinica += novaDionica->brojJedinica;
			return 0;
		}
	}

	// Poveæanje broja dionica
	portfelj->brojDionica++;

	// Realokacija memorije za niz pokazivaèa na dionice
	portfelj->dionice = realloc(portfelj->dionice, portfelj->brojDionica * sizeof(Dionica*));

	// Provjera da li je realokacija uspjela
	if (portfelj->dionice == NULL) {
		fprintf(stderr, "Pogreška pri realokaciji memorije.\n");
		return -1;
	}

	// Dodavanje nove dionice u niz pokazivaèa
	portfelj->dionice[portfelj->brojDionica - 1] = novaDionica;

	return 0;  // Uspješno dodana dionica
}

int ukloni_dionicu(Portfelj* portfelj, char* naziv) {
	int index = -1;

	// Provjerava da li je dionica u portfelju
	for (int i = 0; i < portfelj->brojDionica; ++i) {
		if (strcmp(portfelj->dionice[i]->naziv, naziv) == 0) {
			index = i;
			break;
		}
	}

	// Ako dionica nije pronaðena
	if (index == -1) {
		fprintf(stderr, "Pogreška: Dionica s nazivom '%s' ne postoji u portfelju.\n", naziv);
		return -1;
	}

	// Oslobaðanje memorije za dionicu koja se uklanja
	oslobodiDionicu(portfelj->dionice[index]);

	// Pomak svih dionica za jedno mjesto unazad
	for (int i = index; i < portfelj->brojDionica - 1; ++i) {
		portfelj->dionice[i] = portfelj->dionice[i + 1];
	}

	// Smanjivanje broja dionica u portfelju
	portfelj->brojDionica--;

	// Realokacija memorije za niz pokazivaèa na dionice
	portfelj->dionice = realloc(portfelj->dionice, portfelj->brojDionica * sizeof(Dionica*));

	if (portfelj->dionice == NULL && portfelj->brojDionica > 0) {
		fprintf(stderr, "Pogreška pri realokaciji memorije.\n");
		return -1;
	}

	return 0;  // Uspješno uklonjena dionica
}

void izracunaj_vrijednost_portfelja(Portfelj* portfelj) {
	// Provjeriti je li portfelj prazan
	if (portfelj->brojDionica == 0) {
		printf("Nema dionica u portfelju.\n");
		return;
	}

	// Izraèunati ukupnu vrijednost portfelja
	double ukupna_vrijednost = 0.0;
	for (int i = 0; i < portfelj->brojDionica; i++) {
		ukupna_vrijednost += portfelj->dionice[i]->cijena * portfelj->dionice[i]->brojJedinica; // prokmjena .cijena u ->cijena
	}

	printf("Ukupna vrijednost portfelja je: %.2f\n", ukupna_vrijednost);
}

Korisnik* kreirajKorisnika(char* ime, char* lozinka, double polog) {
	Korisnik* noviKorisnik = (Korisnik*)malloc(sizeof(Korisnik));
	if (noviKorisnik == NULL) {
		printf("Greska pri alociranju memorije za novog korisnika.\n");
		return NULL;
	}

	strcpy(noviKorisnik->ime, ime);
	strcpy(noviKorisnik->lozinka, lozinka);
	noviKorisnik->budzet = polog;

	return noviKorisnik;
}


void dodajKorisnikaUDatoteku(Korisnik* korisnik) {
	FILE* datoteka = fopen("korisnici.txt", "a"); //16. Datoteke, koristiti tekstualnu ili binarnu, provjera pokazivaèa i zatvaranje datoteke
	if (datoteka == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return;
	}

	// Zapisivanje podataka u datoteku
	fprintf(datoteka, "Korisnik: %s, %s, %.2lf\n", korisnik->ime, korisnik->lozinka, korisnik->budzet);

	// Zatvaranje datoteke
	if (fclose(datoteka) != 0) {
		printf("Greska pri zatvaranju datoteke.\n");
	}
}

int provjeriKorisnika(const char* ime, const char* lozinka) {
	FILE* datoteka = fopen("korisnici.txt", "r");
	if (datoteka == NULL) {
		perror("Greska pri otvaranju datoteke");
		return -1;
	}

	fseek(datoteka, 0, SEEK_END);
	long velicina = ftell(datoteka); //17. Koristiti funkcije fseek(), ftell(), rewind(), ovisno o potrebi – neku od njih ako ne sve.
	rewind(datoteka);

	if (velicina == 0) {
		printf("Nema registriranih korisnika.\n");
		return 0;
	}

	char korisnik[256], procitano_ime[256], procitana_lozinka[256];
	while (fgets(korisnik, sizeof(korisnik), datoteka) != NULL) {
		sscanf(korisnik, "%s %s", procitano_ime, procitana_lozinka);
		if (strcmp(procitano_ime, ime) == 0 && strcmp(procitana_lozinka, lozinka) == 0) {
			printf("Korisnik je uspjesno prijavljen.\n");
			return 1;
		}
	}

	printf("Korisnik nije pronadjen ili je lozinka netocna.\n");
	return 0;
}
int dodajNovacKorisniku(const char* ime, double iznos) {
	if (iznos > MAX) {
		printf("Ne možete dodati više od %d u korisnikov budžet.\n", MAX);
		return -1;
	}


	FILE* staraDatoteka = fopen("korisnici.txt", "r");
	if (staraDatoteka == NULL) {
		perror("Greška pri otvaranju datoteke korisnici.txt");
		return -1;
	}

	FILE* novaDatoteka = fopen("novi_korisnici.txt", "w");
	if (novaDatoteka == NULL) {
		perror("Greška pri otvaranju datoteke novi_korisnici.txt");
		return -1;
	}

	char linija[256];
	while (fgets(linija, sizeof(linija), staraDatoteka) != NULL) {
		char korisnik[256];
		double budzet;
		sscanf(linija, "Korisnik: %s , lozinka, %lf", korisnik, &budzet);
		if (strcmp(korisnik, ime) == 0) {
			budzet += iznos;
			fprintf(novaDatoteka, "Korisnik: %s , lozinka, %lf\n", korisnik, budzet);
		}
		else {
			fputs(linija, novaDatoteka);
		}
	}

	fclose(staraDatoteka);
	fclose(novaDatoteka);

	if (remove("korisnici.txt") == 0) {
		if (rename("novi_korisnici.txt", "korisnici.txt") != 0) { //18. Koristiti funkcije remove(), rename(), po potrebi implementirati funkciju za kopiranje datoteka.
			perror("Greška pri preimenovanju datoteke");
			return -1;
		}
	}
	else {
		perror("Greška pri brisanju datoteke");
		return -1;
	}

	return 0;
}

Korisnik* registracija() {
	char ime[50];
	char lozinka[50];
	double polog;

	printf("Unesite ime: ");
	scanf("%49s", ime);
	printf("Unesite lozinku: ");
	scanf("%49s", lozinka);
	printf("Unesite polog: ");
	scanf("%lf", &polog);

	if (postojiKorisnik(ime)) {
		printf("Korisnik vec postoji. Molimo prijavite se.\n");
		return NULL;
	}
	else {
		Korisnik* noviKorisnik = kreirajKorisnika(ime, lozinka, polog);
		if (noviKorisnik != NULL) {
			printf("Uspjesno ste se registrirali.\n");
		}
		return noviKorisnik;
	}
}

Korisnik* prijava() {
	char ime[50];
	char lozinka[50];

	printf("Unesite ime: ");
	scanf("%s", ime);
	printf("Unesite lozinku: ");
	scanf("%s", lozinka);

	FILE* datoteka = fopen("korisnici.txt", "r");
	if (datoteka == NULL) {
		perror("Greska pri otvaranju datoteke korisnici.txt");
		return NULL;
	}

	Korisnik korisnik;
	while (fread(&korisnik, sizeof(Korisnik), 1, datoteka)) {
		if (strcmp(ime, korisnik.ime) == 0 && strcmp(lozinka, korisnik.lozinka) == 0) {
			printf("Uspjesno prijavljivanje.\n");
			Korisnik* prijavljeniKorisnik = malloc(sizeof(Korisnik));
			*prijavljeniKorisnik = korisnik;
			fclose(datoteka);
			return prijavljeniKorisnik;
		}
	}

	printf("Korisnicko ime ili lozinka su netocni.\n");
	fclose(datoteka);
	return NULL;
}


