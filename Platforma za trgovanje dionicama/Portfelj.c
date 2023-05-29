#include "Portfelj.h"
#include <stdlib.h>
#include <string.h>

Portfelj* kreiraj_portfelj()
{
    Portfelj* p = malloc(sizeof(Portfelj));
    p->dionice = NULL;
    p->broj_dionica = 0;

    return p;
}

void dodaj_dionicu(Portfelj* p, Dionica* d)
{
    p->broj_dionica++;
    p->dionice = realloc(p->dionice, p->broj_dionica * sizeof(Dionica*));
    p->dionice[p->broj_dionica - 1] = d;
}

void ukloni_dionicu(Portfelj* p, char* naziv_dionice)
{
    for (int i = 0; i < p->broj_dionica; i++)
    {
        if (strcmp(p->dionice[i]->naziv, naziv_dionice) == 0)
        {
            for (int j = i; j < p->broj_dionica - 1; j++)
            {
                p->dionice[j] = p->dionice[j + 1];
            }
            p->broj_dionica--;
            p->dionice = realloc(p->dionice, p->broj_dionica * sizeof(Dionica*));
            break;
        }
    }
}

void ispis_portfelja(Portfelj* p)
{
    printf("Portfelj sadrzi %d dionica:\n", p->broj_dionica);
    for (int i = 0; i < p->broj_dionica; i++)
    {
        ispis_dionice(p->dionice[i]);
    }
}

void oslobodi_portfelj(Portfelj* p)
{
    for (int i = 0; i < p->broj_dionica; i++)
    {
        free(p->dionice[i]);
    }
    free(p->dionice);
    free(p);
}

float izracunaj_vrijednost_portfelja(Portfelj* p)
{
    float ukupna_vrijednost = 0.0;
    for (int i = 0; i < p->broj_dionica; i++)
    {
        ukupna_vrijednost += p->dionice[i]->cijena;
    }
    return ukupna_vrijednost;
}

Dionica* binarno_pretrazi_portfelj(Portfelj* p, char* naziv_dionice)
{
    Dionica kljuc;
    strncpy(kljuc.naziv, naziv_dionice, sizeof(kljuc.naziv));
    Dionica* pronadjena = (Dionica*)bsearch(&kljuc, p->dionice, p->broj_dionica, sizeof(Dionica*), usporedi_po_imenu);
    return pronadjena;
}

int usporedi_dionice_po_imenu(const void* a, const void* b)
{
    Dionica* d1 = *(Dionica**)a;
    Dionica* d2 = *(Dionica**)b;

    return strcmp(d1->naziv, d2->naziv);
}

void sortiraj_portfelj_po_imenu(Portfelj* p)
{
    qsort(p->dionice, p->broj_dionica, sizeof(Dionica*), usporedi_dionice_po_imenu);
}


int usporedi_dionice_po_cijeni(const void* a, const void* b)
{
    Dionica* d1 = *(Dionica**)a;
    Dionica* d2 = *(Dionica**)b;

    if (d1->cijena < d2->cijena)
        return -1;
    else if (d1->cijena > d2->cijena)
        return 1;
    else
        return 0;
}

void sortiraj_portfelj_po_cijeni(Portfelj* p)
{
    qsort(p->dionice, p->broj_dionica, sizeof(Dionica*), usporedi_dionice_po_cijeni);
}