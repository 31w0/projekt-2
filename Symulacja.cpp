#include "Symulacja.h"
#include "Regulator.h"
#include <iostream>
#include <fstream>

Symulacja::Symulacja()
    : pokoj(3.0f, 4.0f, 5.0f), piec(1000.0f), czasSymulacji(0.0f), regulator(nullptr) {}

void Symulacja::iteracja(float dT) {
    if (regulator != nullptr) {
        regulator->aktualizuj(dT);
    }

    float cieplo = piec.emitujCieplo(dT);
    pokoj.dodajCieplo(cieplo);
    pokoj.aktualizuj(dT);
    czasSymulacji += dT;

    historiaCzasu.push_back(czasSymulacji);
    historiaTemperatury.push_back(pokoj.getTemperatura());
    historiaGrzejnika.push_back(piec.getNastawa());

    std::cout << "Czas: " << czasSymulacji << "s | Temp: " << pokoj.getTemperatura() 
              << " C | Nastawa: " << piec.getNastawa() << "\n";
}

void Symulacja::przebieg(int ileIteracji, float dT) {
    for (int i = 0; i < ileIteracji; ++i) {
        iteracja(dT);
    }
}

void Symulacja::zapiszWyniki(const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        plik << "Iteracja;Czas;Temperatura;Nastawa\n";
        for (size_t i = 0; i < historiaCzasu.size(); ++i) {
            plik << i << ";" << historiaCzasu[i] << ";" 
                 << historiaTemperatury[i] << ";" << historiaGrzejnika[i] << "\n";
        }
        plik.close();
        std::cout << "\n[Symulacja] Zapisano wyniki do pliku: " << nazwaPliku << "\n";
    }
}
