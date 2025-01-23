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
        printf("Obecny wynik: %d\n", wynik);
        printf("Podaj polecenie (f x y - flaga, r x y - odkryj, s - przerwij gre): ");
        scanf(" %c", &komenda);

        if (komenda == 's') {
            printf("Przerwano gre. Ostateczny wynik: %d\n", wynik);
            wypiszPlansze(plansza);
            break;
        }

        scanf(" %d %d", &wiersz, &kolumna);

        if (!czyRuchPoprawny(wiersz, kolumna)) {
            printf("Nieprawidlowy ruch. Sprobuj ponownie.\n");
            continue;
        }

        if (komenda == 'f') {
            planszaWidoczna[wiersz][kolumna] = (planszaWidoczna[wiersz][kolumna] == '#') ? 'F' : '#';
        } 
        else if (komenda == 'r') {
            if (pierwszyRuch) {
                rozmiescMiny(wiersz, kolumna);
                pierwszyRuch = 0;
            }

            if (planszaWidoczna[wiersz][kolumna] == 'F') {
                printf("W tym miejscu znajduje sie flaga! Wybierz inne pole. \n");
                continue;
            }

            if (plansza[wiersz][kolumna] == 'X' && planszaWidoczna[wiersz][kolumna] != 'F') {
                printf("BUM! Trafiles na mine. Koniec gry. Ostateczny wynik: %d\n", wynik);
                wypiszPlansze(plansza);
                break;
            }

            odkryj(wiersz, kolumna);
            wynik += mnoznikWyniku;

            if (sprawdzWygrana()) {
                printf("Gratulacje! Wygrales! Ostateczny wynik: %d\n", wynik);
                wypiszPlansze(plansza);
                zaktualizujNajlepszeWyniki(wynik);
                break;
            }
        } 
        else {
            printf("Nieznane polecenie. Sprobuj ponownie.\n");
        }
    }

    zwolnijPlansze();
    return 0;
}