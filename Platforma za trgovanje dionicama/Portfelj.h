#define _CRT_SECURE_NO_WARNINGS
#ifndef PORTFELJ_H
#define PORTFELJ_H

#include "Dionica.h"

typedef struct Portfelj
{
    Dionica** dionice;
    int broj_dionica;
} Portfelj;

Portfelj* kreiraj_portfelj();
void dodaj_dionicu(Portfelj* p, Dionica* d);
void ukloni_dionicu(Portfelj* p, char* naziv_dionice);
void ispis_portfelja(Portfelj* p);
void oslobodi_portfelj(Portfelj* p);
float izracunaj_vrijednost_portfelja(Portfelj* p);
Dionica* binarno_pretrazi_portfelj(Portfelj* p, char* naziv_dionice);
int usporedi_dionice_po_imenu(const void* a, const void* b);
void sortiraj_portfelj_po_imenu(Portfelj* p);
#endif
