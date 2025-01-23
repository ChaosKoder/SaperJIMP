#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcje.h"

void inicjalizujPlansze() {
    plansza = malloc(wiersze * sizeof(char *));
    planszaWidoczna = malloc(wiersze * sizeof(char *));

    int i, j;
    for (i = 0; i < wiersze; i++) {
        plansza[i] = malloc(kolumny * sizeof(char));
        planszaWidoczna[i] = malloc(kolumny * sizeof(char));
        for (j = 0; j < kolumny; j++) {
            plansza[i][j] = '0';
            planszaWidoczna[i][j] = '#';
        }
    }
}

void inicjalizujNajlepszeWyniki() {
    int i;
    for (i = 0; i < MAX_WYNIKI; i++) {
        strcpy(najlepszeWyniki[i].imie, "");
        najlepszeWyniki[i].wynik = 0;
    }
}

void wczytajNajlepszeWyniki() {
    FILE *plik = fopen("wyniki.txt", "r");
    if (!plik) return;

    int i;
    for (i = 0; i < MAX_WYNIKI; i++) {
        if (fscanf(plik, "%s %d", najlepszeWyniki[i].imie, &najlepszeWyniki[i].wynik) != 2) break;
    }

    fclose(plik);
}

void zapiszNajlepszeWyniki() {
    FILE *plik = fopen("wyniki.txt", "w");
    if (!plik) return;

    int i;
    for (i = 0; i < MAX_WYNIKI; i++) {
        if (najlepszeWyniki[i].wynik > 0) {
            fprintf(plik, "%s %d\n", najlepszeWyniki[i].imie, najlepszeWyniki[i].wynik);
        }
    }

    fclose(plik);
}

void zwolnijPlansze() {
    int i;
    for (i = 0; i < wiersze; i++) {
        free(plansza[i]);
        free(planszaWidoczna[i]);
    }
    free(plansza);
    free(planszaWidoczna);
}

void rozmiescMiny(int pierwszyWiersz, int pierwszaKolumna) {
    int rozmieszczoneMiny = 0;
    srand(time(NULL));

    while (rozmieszczoneMiny < miny) {
        int wiersz = rand() % wiersze;
        int kolumna = rand() % kolumny;

        if ((wiersz == pierwszyWiersz && kolumna == pierwszaKolumna) || plansza[wiersz][kolumna] == 'X') {
            continue;
        }

        plansza[wiersz][kolumna] = 'X';
        rozmieszczoneMiny++;

        int i, j;
        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                int nowyWiersz = wiersz + i;
                int nowaKolumna = kolumna + j;

                if (nowyWiersz >= 0 && nowyWiersz < wiersze && nowaKolumna >= 0 && nowaKolumna < kolumny && plansza[nowyWiersz][nowaKolumna] != 'X') {
                    plansza[nowyWiersz][nowaKolumna]++;
                }
            }
        }
    }
}

void wypiszPlansze(char **b) {
    printf("   ");
    int i, j;
    for (i = 0; i < kolumny; i++) {
        printf("%2d", i);
    }
    printf("\n");

    for (i = 0; i < wiersze; i++) {
        printf("%2d ", i);
        for (j = 0; j < kolumny; j++) {
            printf("%2c", b[i][j]);
        }
        printf("\n");
    }
}

int czyRuchPoprawny(int wiersz, int kolumna) {
    return wiersz >= 0 && wiersz < wiersze && kolumna >= 0 && kolumna < kolumny;
}

void odkryj(int wiersz, int kolumna) {
    if (!czyRuchPoprawny(wiersz, kolumna) || planszaWidoczna[wiersz][kolumna] != '#') {
        return;
    }

    planszaWidoczna[wiersz][kolumna] = plansza[wiersz][kolumna];

    if (plansza[wiersz][kolumna] == '0') {
        int i, j;
        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                odkryj(wiersz + i, kolumna + j);
            }
        }
    }
}

int sprawdzWygrana() {
    int i, j;
    for (i = 0; i < wiersze; i++) {
        for (j = 0; j < kolumny; j++) {
            if (plansza[i][j] != 'X' && planszaWidoczna[i][j] == '#') {
                return 0;
            }
        }
    }
    return 1;
}

void zaktualizujNajlepszeWyniki(int wynik) {
    char imie[MAX_DLUGOSC_IMIENIA];
    printf("Podaj swoje imie: ");
    scanf("%s", imie);

    int i, j;
    for (i = 0; i < MAX_WYNIKI; i++) {
        if (wynik > najlepszeWyniki[i].wynik) {
            for (j = MAX_WYNIKI - 1; j > i; j--) {
                najlepszeWyniki[j] = najlepszeWyniki[j - 1];
            }
            strcpy(najlepszeWyniki[i].imie, imie);
            najlepszeWyniki[i].wynik = wynik;
            break;
        }
    }

    zapiszNajlepszeWyniki();
}

void ustawPoziomTrudnosci() {
    int wybor;
    printf("Wybierz poziom trudnosci:\n");
    printf("1. Latwy (9x9, 10 min)\n");
    printf("2. Sredni (16x16, 40 min)\n");
    printf("3. Trudny (16x30, 99 min)\n");
    printf("4. Wlasny\n");
    scanf("%d", &wybor);

    switch (wybor) {
        case 1:
            wiersze = LATWY_WIERSZE;
            kolumny = LATWY_KOLUMNY;
            miny = LATWY_MINY;
            mnoznikWyniku = 1;
            break;
        case 2:
            wiersze = SREDNI_WIERSZE;
            kolumny = SREDNI_KOLUMNY;
            miny = SREDNI_MINY;
            mnoznikWyniku = 2;
            break;
        case 3:
            wiersze = TRUDNY_WIERSZE;
            kolumny = TRUDNY_KOLUMNY;
            miny = TRUDNY_MINY;
            mnoznikWyniku = 3;
            break;
        case 4:
            printf("Podaj liczbe wierszy, kolumn i min: ");
            scanf("%d %d %d", &wiersze, &kolumny, &miny);
            mnoznikWyniku = 1;
            break;
        default:
            printf("Nieprawidlowy wybor. Ustawiam poziom latwy.\n");
            wiersze = LATWY_WIERSZE;
            kolumny = LATWY_KOLUMNY;
            miny = LATWY_MINY;
            mnoznikWyniku = 1;
    }
}
