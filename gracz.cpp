#include "Gracz.h"
#include "Kasyno.h" // Załączamy pełną definicję Kasyna dopiero w pliku .cpp
#include <iostream>

Gracz::Gracz() : liczbaKart(0), sumaPunktow(0), spasowal(false) {
    for (int i = 0; i < 10; ++i) {
        reka[i] = nullptr;
    }
}

void Gracz::wezKarte(Karta* _karta) {
    if (liczbaKart < 10 && _karta != nullptr) {
        reka[liczbaKart] = _karta;
        sumaPunktow += _karta->getWartosc();
        liczbaKart++;
    }
}

void Gracz::pokazKarty() {
    std::cout << "Karty: ";
    for (int i = 0; i < liczbaKart; ++i) {
        reka[i]->wypisz();
        std::cout << " ";
    }
    std::cout << " | Suma punktow: " << sumaPunktow << std::endl;
}

void Gracz::decyduj(Kasyno* kasyno) {
    if (spasowal) return;

    pokazKarty();

    // Automatyczny pas po przekroczeniu lub osiągnięciu 21 punktów
    if (sumaPunktow >= 21) {
        std::cout << "-> Zgromadzono 21 punktow lub wiecej. Automatyczny pas.\n";
        spasowal = true;
        return;
    }

    char wybor;
    std::cout << "-> Czy chcesz dobrac karte (d) czy spasowac (p)? ";
    std::cin >> wybor;

    if (wybor == 'd' || wybor == 'D') {
        wezKarte(kasyno->dajKarte());
        if (sumaPunktow >= 21) {
            pokazKarty();
            std::cout << "-> Przekroczono limit. Automatyczny pas.\n";
            spasowal = true;
        }
    } else {
        spasowal = true;
    }
}
