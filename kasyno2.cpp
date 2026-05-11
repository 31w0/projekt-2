#include "Kasyno.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Kasyno::Kasyno() : wydaneKarty(0), gracze(nullptr), liczbaGraczy(0), boty(nullptr), liczbaBotow(0) {
    int index = 0;
    for (int kolor = 0; kolor < 4; ++kolor) {
        for (int figura = 0; figura < 13; ++figura) {
            talia[index] = Karta(kolor, figura);
            index++;
        }
    }

    // 1. Inicjalizacja graczy ludzkich
    do {
        std::cout << "Podaj liczbe graczy ludzkich (1-3): ";
        std::cin >> liczbaGraczy;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            liczbaGraczy = 0;
        }
    } while (liczbaGraczy < 1 || liczbaGraczy > 3);
    gracze = new Gracz[liczbaGraczy];

    // 2. Inicjalizacja graczy komputerowych (Botów)
    do {
        std::cout << "Podaj liczbe graczy komputerowych - Botow (1-3): ";
        std::cin >> liczbaBotow;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            liczbaBotow = 0;
        }
    } while (liczbaBotow < 1 || liczbaBotow > 3);
    boty = new Bot[liczbaBotow];

    // Ustawianie odwagi dla każdego z botów
    for (int i = 0; i < liczbaBotow; ++i) {
        int typOdwagi;
        do {
            std::cout << "Wybierz typ Bota " << (i + 1) << " (1 - Ryzykujacy, 2 - Normalny, 3 - Zachowawczy): ";
            std::cin >> typOdwagi;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                typOdwagi = 0;
            }
        } while (typOdwagi < 1 || typOdwagi > 3);
        boty[i].ustawOdwage(typOdwagi);
    }
}

Kasyno::~Kasyno() {
    delete[] gracze;
    delete[] boty; // Pamiętamy o zwalnianiu pamięci botów
}

Kasyno::Kasyno(const Kasyno& inne) : wydaneKarty(inne.wydaneKarty), liczbaGraczy(inne.liczbaGraczy), liczbaBotow(inne.liczbaBotow) {
    for (int i = 0; i < 52; ++i) talia[i] = inne.talia[i];
    
    gracze = new Gracz[liczbaGraczy];
    for (int i = 0; i < liczbaGraczy; ++i) gracze[i] = inne.gracze[i];

    boty = new Bot[liczbaBotow];
    for (int i = 0; i < liczbaBotow; ++i) boty[i] = inne.boty[i];
}

Kasyno& Kasyno::operator=(const Kasyno& inne) {
    if (this != &inne) {
        delete[] gracze;
        delete[] boty;

        liczbaGraczy = inne.liczbaGraczy;
        liczbaBotow = inne.liczbaBotow;
        wydaneKarty = inne.wydaneKarty;
        for (int i = 0; i < 52; ++i) talia[i] = inne.talia[i];

        gracze = new Gracz[liczbaGraczy];
        for (int i = 0; i < liczbaGraczy; ++i) gracze[i] = inne.gracze[i];

        boty = new Bot[liczbaBotow];
        for (int i = 0; i < liczbaBotow; ++i) boty[i] = inne.boty[i];
    }
    return *this;
}

Karta* Kasyno::dajKarte() {
    if (wydaneKarty < 52) return &talia[wydaneKarty++];
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

void Kasyno::zresetuj() {
    tasuj();
    for (int i = 0; i < liczbaGraczy; ++i) gracze[i].resetuj();
    for (int i = 0; i < liczbaBotow; ++i) boty[i].resetuj(); // Zadanie 3: Resetowanie botów
    std::cout << "\n[Kasyno]: Stól przygotowany do nowej partii.\n";
}

void Kasyno::graj() {
    char nowaGraWybor;
    do {
        zresetuj();

        std::cout << "\n--- ROZDAWANIE 2 PIERWSZYCH KART ---\n";
        for (int i = 0; i < liczbaGraczy; ++i) {
            gracze[i].wezKarte(dajKarte());
            gracze[i].wezKarte(dajKarte());
        }
        for (int i = 0; i < liczbaBotow; ++i) {
            boty[i].wezKarte(dajKarte());
            boty[i].wezKarte(dajKarte());
        }

        bool wszyscySpasowali = false;
        while (!wszyscySpasowali) {
            wszyscySpasowali = true;

            // Tury graczy ludzkich
            for (int i = 0; i < liczbaGraczy; ++i) {
                if (!gracze[i].getSpasowal()) {
                    std::cout << "\n--- TURA GRACZA LUDZKIEGO " << (i + 1) << " ---\n";
                    gracze[i].decyduj(this);
                    if (!gracze[i].getSpasowal()) wszyscySpasowali = false;
                }
            }

            // Tury Botów
            for (int i = 0; i < liczbaBotow; ++i) {
                if (!boty[i].getSpasowal()) {
                    std::cout << "\n--- TURA BOTA " << (i + 1) << " ---\n";
                    boty[i].decyduj(this);
                    if (!boty[i].getSpasowal()) wszyscySpasowali = false;
                }
            }
        }

        // Zadanie 3: Podsumowanie uwzględniające boty
        std::cout << "\n=== KONIEC GRY - WYNIKI ===\n";
        for (int i = 0; i < liczbaGraczy; ++i) {
            std::cout << "Gracz " << (i + 1) << " -> ";
            gracze[i].pokazKarty();
        }
        for (int i = 0; i < liczbaBotow; ++i) {
            std::cout << "Bot " << (i + 1) << "   -> ";
            boty[i].pokazKarty(); // Bot odziedziczył pokazKarty() po klasie Gracz
        }

        std::cout << "\n-> Czy chcecie zagrac kolejna partie od nowa? (t/n): ";
        std::cin >> nowaGraWybor;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

    } while (nowaGraWybor == 't' || nowaGraWybor == 'T');

    std::cout << "\nDziekujemy za gre!\n";
}
