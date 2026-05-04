#include "Kasyno.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Kasyno::Kasyno() : wydaneKarty(0), gracze(nullptr), liczbaGraczy(0) {
    int index = 0;
    for (int kolor = 0; kolor < 4; ++kolor) {
        for (int figura = 0; figura < 13; ++figura) {
            talia[index] = Karta(kolor, figura);
            index++;
        }
    }

    do {
        std::cout << "Podaj liczbe graczy (1-3): ";
        std::cin >> liczbaGraczy;
    } while (liczbaGraczy < 1 || liczbaGraczy > 3);

    gracze = new Gracz[liczbaGraczy];
}

Kasyno::~Kasyno() {
    delete[] gracze;
}

Kasyno::Kasyno(const Kasyno& inne) : wydaneKarty(inne.wydaneKarty), liczbaGraczy(inne.liczbaGraczy) {
    for (int i = 0; i < 52; ++i) {
        talia[i] = inne.talia[i];
    }
    gracze = new Gracz[liczbaGraczy];
    for (int i = 0; i < liczbaGraczy; ++i) {
        gracze[i] = inne.gracze[i];
    }
}

Kasyno& Kasyno::operator=(const Kasyno& inne) {
    if (this != &inne) {
        delete[] gracze;
        liczbaGraczy = inne.liczbaGraczy;
        wydaneKarty = inne.wydaneKarty;
        for (int i = 0; i < 52; ++i) {
            talia[i] = inne.talia[i];
        }
        gracze = new Gracz[liczbaGraczy];
        for (int i = 0; i < liczbaGraczy; ++i) {
            gracze[i] = inne.gracze[i];
        }
    }
    return *this;
}

Karta* Kasyno::dajKarte() {
    if (wydaneKarty < 52) {
        return &talia[wydaneKarty++];
    }
    return nullptr; 
}

void Kasyno::tasuj() {
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 100; ++i) {
        int idx1 = rand() % 52;
        int idx2 = rand() % 52;
        Karta temp = talia[idx1];
        talia[idx1] = talia[idx2];
        talia[idx2] = temp;
    }
    wydaneKarty = 0; 
}

void Kasyno::graj() {
    tasuj();
    
    std::cout << "\n--- ROZDAWANIE 2 PIERWSZYCH KART ---\n";
    // Automatyczne rozdanie 2 pierwszych kart
    for (int i = 0; i < liczbaGraczy; ++i) {
        gracze[i].wezKarte(dajKarte());
        gracze[i].wezKarte(dajKarte());
    }
    
    // Główna pętla gry
    bool wszyscySpasowali = false;
    while (!wszyscySpasowali) {
        wszyscySpasowali = true; // Z góry zakładamy, że to już koniec...
        
        for (int i = 0; i < liczbaGraczy; ++i) {
            if (!gracze[i].getSpasowal()) {
                std::cout << "\n--- TURA GRACZA " << (i + 1) << " ---\n";
                gracze[i].decyduj(this); // Gracz decyduje i korzysta z Kasyna do ewentualnego pobrania karty
                
                if (!gracze[i].getSpasowal()) {
                    wszyscySpasowali = false; // Jeśli ktokolwiek nie spasował gra toczy się dalej
                }
            }
        }
    }
    
    // Podsumowanie po końcu gry
    std::cout << "\n=== KONIEC GRY - PODSUMOWANIE ===\n";
    for (int i = 0; i < liczbaGraczy; ++i) {
        std::cout << "Gracz " << (i + 1) << " -> ";
        gracze[i].pokazKarty();
    }
}
