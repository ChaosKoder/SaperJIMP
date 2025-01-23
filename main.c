#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcje.h"

char **plansza;
char **planszaWidoczna;
int wiersze, kolumny, miny;
int mnoznikWyniku;
WynikGracza najlepszeWyniki[MAX_WYNIKI];

int main() {
    int wiersz, kolumna;
    char komenda;
    int wynik = 0;
    int pierwszyRuch = 1;

    inicjalizujNajlepszeWyniki();
    wczytajNajlepszeWyniki();
    ustawPoziomTrudnosci();
    inicjalizujPlansze();

    while (1) {
        wypiszPlansze(planszaWidoczna);
        printf("Podaj polecenie (f x y - flaga, r x y - odkryj): ");
        scanf(" %c %d %d", &komenda, &wiersz, &kolumna);

        if (!czyRuchPoprawny(wiersz, kolumna)) {
            printf("Nieprawidlowy ruch. Sprobuj ponownie.\n");
            continue;
        }

        if (komenda == 'f') {
            planszaWidoczna[wiersz][kolumna] = (planszaWidoczna[wiersz][kolumna] == '#') ? 'F' : '#';
        } else if (komenda == 'r') {
            if (pierwszyRuch) {
                rozmiescMiny(wiersz, kolumna);
                pierwszyRuch = 0;
            }

            if (plansza[wiersz][kolumna] == 'X') {
                printf("BUM! Trafiles na mine. Koniec gry.\n");
                wypiszPlansze(plansza);
                break;
            }

            odkryj(wiersz, kolumna);
            wynik += mnoznikWyniku;

            if (sprawdzWygrana()) {
                printf("Gratulacje! Wygrales!\n");
                wypiszPlansze(plansza);
                zaktualizujNajlepszeWyniki(wynik);
                break;
            }
        } else {
            printf("Nieznane polecenie. Sprobuj ponownie.\n");
        }
    }

    zwolnijPlansze();
    return 0;
}