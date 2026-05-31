#include "Symulacja.h"

int main() {
    Symulacja symulacja;

    symulacja.przebieg(100, 10.0f);

    symulacja.zapiszWyniki("wyniki.csv");

    return 0;
}