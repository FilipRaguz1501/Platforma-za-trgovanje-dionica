#define _CRT_SECURE_NO_WARNINGS
#include "Funkcije.h"

Korisnik* kreirajKorisnika(const char* korisnickoIme, const char* lozinka, double budzet) {
    Korisnik* noviKorisnik = (Korisnik*)malloc(sizeof(Korisnik));
    if (noviKorisnik == NULL) {
        perror("Greska prilikom alociranja memorije za novog korisnika");
        return NULL;
    }
    strcpy(noviKorisnik->korisnickoIme, korisnickoIme);
    strcpy(noviKorisnik->lozinka, lozinka);
    noviKorisnik->budzet = budzet;
    noviKorisnik->portfelj = kreirajPortfelj();
    if (noviKorisnik->portfelj == NULL) {
        free(noviKorisnik);
        return NULL;
    }
    return noviKorisnik;
}
void obrisiKorisnika(Korisnik* korisnik) {
    obrisiPortfelj(korisnik->portfelj); // Brisanje portfelja korisnika
    free(korisnik);
}


Dionica* kreirajDionicu(const char* naziv, double cijena) {
    Dionica* novaDionica = (Dionica*)malloc(sizeof(Dionica));
    if (novaDionica == NULL) {
        perror("Greska prilikom alociranja memorije za novu dionicu");
        return NULL;
    }
    strcpy(novaDionica->naziv, naziv);
    novaDionica->cijena = cijena;
    return novaDionica;
}
void obrisiDionicu(Dionica* dionica) {
    free(dionica);
}


Portfelj* kreirajPortfelj() {
    Portfelj* noviPortfelj = (Portfelj*)malloc(sizeof(Portfelj));
    noviPortfelj->dionice = malloc(10 * sizeof(Dionica)); // Inicijalno postavimo kapacitet na 10
    noviPortfelj->brojDionica = 0;
    noviPortfelj->kapacitet = 10;  // Dodajemo kapacitet u strukturu Portfelj
    return noviPortfelj;
}

void obrisiPortfelj(Portfelj* portfelj) {
    free(portfelj->dionice);
    free(portfelj);
}

bool provjeri_bazu_podataka(FILE* datoteka, const char* korisnicko_ime, const char* lozinka) {
    rewind(datoteka);  // Vratimo se na pocetak datoteke
    if (ferror(datoteka)) {
        perror("Greska prilikom vracanja na pocetak datoteke");
        return false;
    }
    char ime[50];
    char zaporka[50];
    
    while (fscanf(datoteka, "%s %s\n", ime, zaporka) != EOF) {
        if (strcmp(ime, korisnicko_ime) == 0 && strcmp(zaporka, lozinka) == 0) {
            return true;
        }
    }

    return false;
}


Korisnik* registracija(FILE* datoteka, int brojKorisnika, Korisnik* korisnici) {
    char korisnicko_ime[50];
    char lozinka[50];
    
    printf("\nUnesite korisnicko ime: ");
    scanf("%s", korisnicko_ime);
    printf("\nUnesite lozinku: ");
    scanf("%s", lozinka);

    if (provjeri_bazu_podataka(datoteka, korisnicko_ime, lozinka)) {
        printf("Korisnik sa ovim korisnickim imenom i lozinkom vec postoji.\n");
        return NULL;
    } else {
        Korisnik* noviKorisnik = kreirajKorisnika(korisnicko_ime, lozinka, 0.0);
        fseek(datoteka, 0, SEEK_END); // Pomaknemo se na kraj datoteke
        fprintf(datoteka, "%s %s\n", korisnicko_ime, lozinka);
        korisnici[brojKorisnika++] = *noviKorisnik;
        return noviKorisnik;
    }
    
}

Korisnik* prijava(FILE* datoteka, int brojKorisnika, Korisnik* korisnici) {
    char korisnicko_ime[50];
    char lozinka[50];
    
    printf("\nUnesite korisnicko ime: ");
    scanf("%s", korisnicko_ime);
    printf("\nUnesite lozinku: ");
    scanf("%s", lozinka);

    if (provjeri_bazu_podataka(datoteka, korisnicko_ime, lozinka)) {
        
        // Prolazimo kroz sve korisnike
        for(int i = 0; i < brojKorisnika; i++) {
            // Provjeravamo ima li korisnik isto korisnicko ime i lozinku
            if(strcmp(korisnici[i].korisnickoIme, korisnicko_ime) == 0 &&
               strcmp(korisnici[i].lozinka, lozinka) == 0) {
                return &korisnici[i]; // Ako ima, vracamo tog korisnika
            }
        }
    } else {
        printf("\nKorisnicko ime ili lozinka su netocni.\n");
    }
    return NULL; // Ako prijava nije uspjela, vracamo NULL
}



//2->
bool kupiDionicu(Portfelj* portfelj, Dionica* dionica, int kolicina, double* budzet) {
    if(*budzet < dionica->cijena * kolicina) {
        printf("\nNemate dovoljno novca za kupnju ove dionice.\n");
        return false;
    }
    for (int i = 0; i < portfelj->brojDionica; i++) {
        if (strcmp(portfelj->dionice[i].naziv, dionica->naziv) == 0) {
            portfelj->dionice[i].kolicina += kolicina;
            *budzet -= dionica->cijena * kolicina;
            printf("\nUspjesno ste kupili %d dionica %s.\n", kolicina, dionica->naziv);
            return true;
        }
    }
    if (portfelj->brojDionica >= portfelj->kapacitet) {
        portfelj->kapacitet *= 2;
        portfelj->dionice = realloc(portfelj->dionice, portfelj->kapacitet * sizeof(Dionica));
    }
    portfelj->dionice[portfelj->brojDionica] = *dionica;
    portfelj->dionice[portfelj->brojDionica].kolicina = kolicina;
    portfelj->brojDionica++;
    *budzet -= dionica->cijena * kolicina;
    printf("\nUspjesno ste kupili %d dionica %s.\n", kolicina, dionica->naziv);
}
void prodajDionicu(Portfelj* portfelj, Dionica* dionica, int kolicina, double* budzet) {
    for (int i = 0; i < portfelj->brojDionica; i++) {
        if (strcmp(portfelj->dionice[i].naziv, dionica->naziv) == 0) {
            if (portfelj->dionice[i].kolicina < kolicina) {
                printf("\nNemate dovoljno dionica za prodaju.\n");
                return;
            }
            portfelj->dionice[i].kolicina -= kolicina;
            *budzet += dionica->cijena * kolicina;
            printf("\nUspjesno ste prodali %d dionica %s.\n", kolicina, dionica->naziv);
            
            if(portfelj->dionice[i].kolicina == 0) {
                for(int j = i; j < portfelj->brojDionica - 1; j++) {
                    portfelj->dionice[j] = portfelj->dionice[j + 1];
                }
                portfelj->brojDionica--;
            }
            return;
        }
    }
    printf("\nNemate dionice %s u svom portfelju.\n", dionica->naziv);
}
Dionica* provjeriDionicu(Dionica* dionice, int brojDionica) {
    char nazivDionice[50];
    printf("\nUnesite naziv dionice koju zelite kupiti: ");
    scanf("%s", nazivDionice);
    for(int i = 0; i < brojDionica; i++) {
        if(strcmp(dionice[i].naziv, nazivDionice) == 0) {
            return &dionice[i];
        }
    }
    printf("\nDionica koju zelite kupiti nije za prodaju.\n");
    return NULL;
}
void depozit(Korisnik* korisnik, double iznos) {
    if (iznos < 1 || iznos > 1000000) {
        printf("Neispravan iznos za depozit. Iznos treba biti izmedju 1 i 1000000.\n");
        return;
    }
    korisnik->budzet += iznos;
    printf("\nDepozit je uspjesno dodan. Novi budzet iznosi %.2f EUR.\n", korisnik->budzet);
}
// Usporedna funkcija koja se koristi za sortiranje dionica
int usporediDionicePoCijeni(const void* a, const void* b) {
    Dionica* dionicaA = (Dionica*)a;
    Dionica* dionicaB = (Dionica*)b;
    if (dionicaA->cijena < dionicaB->cijena) return 1;
    if (dionicaA->cijena > dionicaB->cijena) return -1;
    return 0;
}

void sortirajPortfeljPoCijeni(Portfelj* portfelj) {
    qsort(portfelj->dionice, portfelj->brojDionica, sizeof(Dionica), usporediDionicePoCijeni);
}
void sortirajPortfeljPoNazivu(Portfelj* portfelj) {
    qsort(portfelj->dionice, portfelj->brojDionica, sizeof(Dionica), usporediDionicePoNazivuZaPretragu);
}

int usporediDionicePoNazivuZaPretragu(const void* a, const void* b) {
    char* nazivDionice = (char*)a;
    Dionica* dionica = (Dionica*)b;
    return strcmp(nazivDionice, dionica->naziv);
}

Dionica* pretraziPortfelj(Portfelj* portfelj, char* nazivDionice) {
    return (Dionica*)bsearch(nazivDionice, portfelj->dionice, portfelj->brojDionica, sizeof(Dionica), usporediDionicePoNazivuZaPretragu);
}

void ispisiPortfelj(Portfelj* portfelj) {
    if (portfelj->brojDionica == 0) {
        printf("\nPortfelj je prazan.\n");
        return;
    }

    for (int i = 0; i < portfelj->brojDionica; i++) {
        printf("\nNaziv dionice: %s, Cijena: %.2f, Kolicina: %d\n", portfelj->dionice[i].naziv, portfelj->dionice[i].cijena, portfelj->dionice[i].kolicina);
    }
}

inline void obrisiDatotekuKorisnika(const char* imeDatoteke) {
    if (remove(imeDatoteke) == 0) 
        printf("Datoteka je uspjesno obrisana.\n");
    else
        printf("Greska prilikom brisanja datoteke.\n");
}

