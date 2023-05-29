#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Dionica.h"
#include "Portfelj.h"
#include "Korisnik.h"
/*Organizacija izvornog koda*/
int main()
{
	FILE* datoteka = fopen("dionice.txt", "w");

	if (datoteka == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return 1;
	}

	struct {
		char* naziv;
		float cijena; // 1. Realni tip podatka
	} ulazne_dionice[] = {
		{"AAPL", 172.46},
		{"MSFT", 321.50},
		{"AMZN", 116.08},
		{"NVDA", 372.89},
		{"GOOGL", 124.07},
		{"GOOG", 124.87},
		{"BRK.B", 319.64},
		{"META", 252.43},
		{"TSLA", 185.57},
		{"UNH", 476.25},
		{"XOM", 105.37},
		{"JNJ", 154.70},
		{"JPM", 135.68},
		{"V", 221.22},
		{"PG", 144.55},
		{"LLY", 423.45},
		{"MA", 365.48},
		{"HD", 290.86},
		{"MRK", 112.15},
		{"AVGO", 693.55}
	};

	int broj_dionica = sizeof(ulazne_dionice) / sizeof(ulazne_dionice[0]);
	Dionica** dionice = malloc(broj_dionica * sizeof(Dionica*));

	if (dionice == NULL)
	{
		printf("Greska pri alociranju memorije za dionice.\n");
		fclose(datoteka);
		return 1;
	};

	for (int i = 0; i < broj_dionica; ++i)
	{
		dionice[i] = nova_dionica(ulazne_dionice[i].naziv, ulazne_dionice[i].cijena);
		if (dionice[i] == NULL)
		{
			printf("Greska pri alociranju memorije za dionicu.\n");
			fclose(datoteka);
			for (int j = 0; j < i; ++j)
			{
				free(dionice[j]);
			}
			free(dionice);
			return 1;
		}
		pohrani_dionicu_u_datoteku(datoteka, dionice[i]);
	}


	fclose(datoteka);







/*
	// Sort by cijeni
	sortiraj_po_cijeni(dionice, broj_dionica);
	printf("Sortirano po cijeni:\n");
	for (int i = 0; i < broj_dionica; ++i)
	{
		ispis_dionice(dionice[i]);
	}
	printf("\n");

	// Sort by imenu
	sortiraj_po_imenu(dionice, broj_dionica);
	printf("Sortirano po imenu:\n");
	for (int i = 0; i < broj_dionica; ++i)
	{
		ispis_dionice(dionice[i]);
	}
	printf("\n");




	// binarno pretrazivanje
	char* trazena_dionica = "AAPL";
	Dionica* d = binarno_pretrazi_dionicu(dionice, broj_dionica, trazena_dionica);
	if (d != NULL)
	{
		printf("Pronadena dionica: ");
		ispis_dionice(d);
	}
	else
	{
		printf("Dionica %s nije pronadena.\n", trazena_dionica);
	}

	// Sortiraj po datumu kupnje
	sortiraj_po_datumu_kupnje(dionice, broj_dionica);
	printf("Sortirano po datumu kupnje:\n");
	for (int i = 0; i < broj_dionica; ++i)
	{
		ispis_dionice(dionice[i]);
	}
	printf("\n");



	// oslobađanje
	for (int i = 0; i < broj_dionica; ++i)
	{
		free(dionice[i]);
	}
	free(dionice);


	Portfelj* portfelj = kreiraj_portfelj();

	Dionica* dionica1 = nova_dionica("AAPL", 172.46);
	Dionica* dionica2 = nova_dionica("MSFT", 321.50);
	Dionica* dionica3 = nova_dionica("AMZN", 116.08);

	dodaj_dionicu(portfelj, dionica1);
	dodaj_dionicu(portfelj, dionica2);
	dodaj_dionicu(portfelj, dionica3);

	ispis_portfelja(portfelj);
	sortiraj_portfelj_po_imenu(portfelj);
	ispis_portfelja(portfelj);
	char* naziv_dionice = "AAPL";

	sortiraj_portfelj_po_imenu(portfelj);
	ispis_portfelja(portfelj);
	sortiraj_portfelj_po_cijeni(portfelj);
	ispis_portfelja(portfelj); */

	// Stvori novog korisnika
		Korisnik * korisnik = stvori_korisnik("JohnDoe", "123456", 1000.0);

		// Uplati određeni iznos na korisnikov račun
		polog(korisnik, 500.0);  // Novi proračun: 1500.00

		// Stvori novu dionicu i dodaj je u korisnikov portfelj
		Dionica* dionica1 = nova_dionica("Apple", 150.0);
		dodaj_dionicu(korisnik->portfelj, dionica1);

		// Stvori još jednu dionicu i dodaj je u korisnikov portfelj
		Dionica* dionica2 = nova_dionica("Microsoft", 200.0);
		dodaj_dionicu(korisnik->portfelj, dionica2);

		// Prikaži korisnikov portfelj
		printf("\nPrije sortiranja:\n");
		provjeri_portfelj(korisnik);  // Prikazat će dionice "Apple" i "Microsoft"

		// Sortiraj korisnikov portfelj po imenu
		sortiraj_portfelj(korisnik);

		// Prikaži sortirani portfelj
		printf("\nPoslije sortiranja:\n");
		provjeri_portfelj(korisnik);  // Prikazat će dionice "Apple" i "Microsoft" sortirane po redu

		// Pretraži korisnikov portfelj za određenom dionicom
		pretrazi_portfelj(korisnik, "Apple");  // Prikazat će dionicu "Apple"

		// Očisti
		oslobodi_portfelj(korisnik->portfelj);
		free(korisnik);


	return 0;
}