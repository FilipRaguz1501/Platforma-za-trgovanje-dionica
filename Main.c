#include <stdio.h>
#include <stdbool.h>
#include "Funkcije.h"

#define BROJ_DIONICA 20
#define MAX_KORISNIKA 1000

int main() {
    Korisnik korisnici[MAX_KORISNIKA];
    static int brojKorisnika = 0;
    Korisnik* korisnik;
    void prikaziIzbornik(Korisnik* korisnik, bool prijavljen, Dionica* dionice, int brojDionica);

    Dionica dionice[BROJ_DIONICA] = {
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
        {"MR", 112.15},
        {"AVGO", 693.55}
    };

    int brojDionica = sizeof(dionice) / sizeof(Dionica);

    FILE* datoteka = fopen("Korisnici.txt", "a+");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.\n");
        return 1;
    }

    int izbor;
    bool prijavljen = false;
    bool registriran = false;
    double iznos;
    do {
        printf("\n----------------------------------------------------------\n");
        printf("\n");
        printf("         PLATFORMA ZA TRGOVANJE DIONICA         \n");
        printf("\n----------------------------------------------------------\n");
        printf("\n1. Registracija\n");
        printf("\n");
        printf("2. Prijava\n");
        printf("\n");
        printf("3. Odjava\n");
        printf("\n");
        printf("4. Proširi\n");
        printf("\n");
        printf("5. Izlaz\n");
        printf("\nUnesite broj izbora: ");

        if (scanf("%d", &izbor) != 1) {
            printf("\nNeispravan unos. Molim vas unesite broj izbora.\n");
            while (getchar() != '\n') {
                continue; // Pražnjenje ulaznog spremnika
            }
            continue; // Preskoči ostatak petlje i ponovno započni iteraciju
        }

        switch (izbor) {
            case 1:
                if (registriran) {
                    printf("\nKorisnik je već registriran u ovoj sesiji.\n");
                } else {
                    korisnik = registracija(datoteka, brojKorisnika, korisnici);
                    if (korisnik != NULL) {
                        printf("\nUspješna registracija korisnika %s.\n", korisnik->korisnickoIme);
                        registriran = true;
                        brojKorisnika++;
                    }
                }
                break;
            case 2:
                if (prijavljen) {
                    printf("\bKorisnik je već prijavljen.\n");
                } else {
                    korisnik = prijava(datoteka, brojKorisnika, korisnici);
                    if (korisnik != NULL) {
                        printf("\nUspješna prijava korisnika %s.\n", korisnik->korisnickoIme);
                        prijavljen = true;
                    }
                }
                break;
            case 3: 
                if(prijavljen) {
                    printf("\nUspješno ste se odjavili");
                    prijavljen = false;
                } else {
                    printf("\nMolim vas prijavite se prije odjavljivanja\n");
                }
            case 4:
                if(prijavljen) {
                    prikaziIzbornik(korisnik, prijavljen, dionice, brojDionica);
                } else {
                    printf("\nMolim vas prvo se prijavite prije odabira ove opcije\n");
                }
                break;
            case 5:
                prijavljen = false;
                registriran = false;
                printf("\nVratite nam se opet!");
                break;
            default:
                printf("\nNepoznat izbor.\n");
                break;
        }

    } while (izbor != 5);

    fclose(datoteka);
    obrisiDatotekuKorisnika("Korisnici.txt");
    return 0;
}

void prikaziIzbornik(Korisnik* korisnik, bool prijavljen, Dionica* dionice, int brojDionica) {
    int drugiIzbor;
    double iznos;
    do {
        printf("\n----------------------------------------------------------\n");
        printf("\n");
        printf("         PLATFORMA ZA TRGOVANJE DIONICA         \n");
        printf("\n----------------------------------------------------------\n");
        printf("\n1. Napravi Depozit\n");
        printf("2. Kupi Dionicu\n");
        printf("3. Sortiraj Portfelj po Cijeni\n");
        printf("4. Pretraži Portfelj\n");
        printf("5. Prodaj Dionicu\n");
        printf("6. Prikaži Iznos Budžeta\n");
        printf("7. Ispiši Portfelj\n");
        printf("8. Povratak\n");
        printf("\nUnesite broj izbora: ");

        if (scanf("%d", &drugiIzbor) != 1) {
            printf("\nNeispravan unos. Molim vas unesite broj izbora.\n");
            while (getchar() != '\n') {
                continue; // Pražnjenje ulaznog spremnika
            }
            continue; // Preskoči ostatak petlje i ponovno započni iteraciju
        }

        switch (drugiIzbor) {
            case 1:
                if (korisnik != NULL) {
                    printf("\nKoliki iznos želite uplatiti: ");
                    if (scanf("%lf", &iznos) != 1) {
                        printf("\nNeispravan unos iznosa depozita.\n");
                        while (getchar() != '\n') {
                            continue; // Pražnjenje ulaznog spremnika
                        }
                        break;
                    }
                    depozit(korisnik, iznos);
                } else {
                    printf("\nMolim vas prijavite se prije odabira opcije depozita.\n");
                }
                break;
            case 2:
                if (!prijavljen) {
                    printf("\nMorate se prijaviti prije nego što kupite dionicu.\n");
                } else {
                    Dionica* dionicaZaKupnju = provjeriDionicu(dionice, brojDionica);
                    if (dionicaZaKupnju != NULL) {
                        int kolicina;
                        printf("\nUnesite količinu dionica koje želite kupiti: ");
                        scanf("%d", &kolicina);
                        kupiDionicu(korisnik->portfelj, dionicaZaKupnju, kolicina, &korisnik->budzet);
                    }
                }
                break;
            case 3:
                sortirajPortfeljPoCijeni(korisnik->portfelj);
                ispisiPortfelj(korisnik->portfelj);
                break;
            case 4:
                sortirajPortfeljPoNazivu(korisnik->portfelj);
                char nazivDionice[100];
                printf("\nKoju dionicu želite provjeriti nalazi li se u vašem portfelju: ");
                scanf("%99s", nazivDionice);
                if (pretraziPortfelj(korisnik->portfelj, nazivDionice) != NULL) {
                    printf("Dionica %s nalazi se u vašem portfelju\n", nazivDionice);
                };
                break;
            case 5:
                ispisiPortfelj(korisnik->portfelj);
                char naziv[100];
                printf("\nKoju Dionicu želite prodati: ");
                scanf("%99s", naziv);
                sortirajPortfeljPoNazivu(korisnik->portfelj);
                Dionica* dionica = pretraziPortfelj(korisnik->portfelj, naziv);
                if (dionica == NULL) {
                    printf("\nNemate dionicu %s u svom portfelju.\n", naziv);
                    break;
                }
                int kolicina;
                printf("\nKoliko dionica želite prodati: ");
                scanf("%d", &kolicina);
                prodajDionicu(korisnik->portfelj, dionica, kolicina, &(korisnik->budzet));
                break;
            case 6:
                ISPISI_BUDZET(korisnik->budzet);
                break;
            case 7:
                ispisiPortfelj(korisnik->portfelj);
                break;
            case 8:
                printf("\nPovratak na prethodni izbornik.\n");
                break;
            default:
                printf("\nNepoznat izbor.\n");
                break;
        }
    } while (drugiIzbor != 8);
}


