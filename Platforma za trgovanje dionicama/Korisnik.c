#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Korisnik.h"

Korisnik* stvori_korisnik(char* ime, char* lozinka, double proracun)
{
    Korisnik* k = malloc(sizeof(Korisnik));
    if (k == NULL)
    {
        printf("Greska pri alociranju memorije.\n");
        exit(1);
    }
    strcpy(k->ime, ime);
    strcpy(k->lozinka, lozinka);
    k->portfelj = kreiraj_portfelj();
    k->proracun = proracun;

    return k;
}

void provjeri_portfelj(Korisnik* korisnik)
{
    ispis_portfelja(korisnik->portfelj);
}

void sortiraj_portfelj(Korisnik* korisnik)
{
    // sortiraj_po_imenu is from Dionica.h
    sortiraj_po_imenu(korisnik->portfelj->dionice, korisnik->portfelj->broj_dionica);
    printf("Sortirano po imenu:\n");
    ispis_portfelja(korisnik->portfelj);
}

void pretrazi_portfelj(Korisnik* korisnik, char* ime_dionice)
{
    // binarno_pretrazi_dionicu is from Dionica.h
    Dionica* d = binarno_pretrazi_dionicu(korisnik->portfelj->dionice, korisnik->portfelj->broj_dionica, ime_dionice);
    if (d != NULL)
    {
        printf("Pronadena dionica: ");
        ispis_dionice(d);
    }
    else
    {
        printf("Dionica %s nije pronadena.\n", ime_dionice);
    }
}

void polog(Korisnik* korisnik, double iznos)
{
    korisnik->proracun += iznos;
    printf("Novi proracun: %.2f\n", korisnik->proracun);
}

void kupi_dionicu(Korisnik* korisnik, char* ime_dionice, float cijena)
{
    Dionica* d = nova_dionica(ime_dionice, cijena);
    if (d != NULL)
    {
        if (korisnik->proracun >= cijena)
        {
            dodaj_dionicu(korisnik->portfelj, d);
            korisnik->proracun -= cijena;
            printf("Dionica %s uspjesno kupljena.\n", ime_dionice);
        }
        else
        {
            printf("Nedovoljno sredstava za kupovinu dionice %s.\n", ime_dionice);
            free(d);
        }
    }
    else
    {
        printf("Stvaranje dionice %s nije uspjelo.\n", ime_dionice);
    }
}

void prodaj_dionicu(Korisnik* korisnik, char* ime_dionice)
{
    Dionica* d = binarno_pretrazi_portfelj(korisnik->portfelj, ime_dionice);
    if (d != NULL)
    {
        ukloni_dionicu(korisnik->portfelj, ime_dionice);
        korisnik->proracun += d->cijena;
        free(d);
        printf("Dionica %s uspjesno prodana.\n", ime_dionice);
    }
    else
    {
        printf("Dionica %s nije pronadena u portfelju.\n", ime_dionice);
    }
}
