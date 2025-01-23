#define LATWY_WIERSZE 9
#define LATWY_KOLUMNY 9
#define LATWY_MINY 10
#define SREDNI_WIERSZE 16
#define SREDNI_KOLUMNY 16
#define SREDNI_MINY 40
#define TRUDNY_WIERSZE 16
#define TRUDNY_KOLUMNY 30
#define TRUDNY_MINY 99
#define MAX_DLUGOSC_IMIENIA 50
#define MAX_WYNIKI 5

#ifndef _FUNKCJE_H_IS_INCLUDED_
#define _FUNKCJE_H_IS_INCLUDED_

typedef struct {
    char imie[MAX_DLUGOSC_IMIENIA];
    int wynik;
} WynikGracza;

extern char **plansza;
extern char **planszaWidoczna;
extern int wiersze, kolumny, miny;
extern int mnoznikWyniku;
extern WynikGracza najlepszeWyniki[MAX_WYNIKI];

void inicjalizujPlansze();

void inicjalizujNajlepszeWyniki();

void wczytajNajlepszeWyniki();

void zapiszNajlepszeWyniki();

void zwolnijPlansze();

void rozmiescMiny(int pierwszyWiersz, int pierwszaKolumna);

void wypiszPlansze(char **b);

int czyRuchPoprawny(int wiersz, int kolumna);

void odkryj(int wiersz, int kolumna);

int sprawdzWygrana(); 

void zaktualizujNajlepszeWyniki(int wynik); 

void ustawPoziomTrudnosci();

#endif