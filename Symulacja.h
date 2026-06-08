#pragma once
#include "Pomieszczenie.h"
#include "Grzejnik.h"
#include <vector>
#include <string>

class Regulator;

class Symulacja {
private:
    Pomieszczenie pokoj;
    Grzejnik piec;
    Regulator* regulator;

    std::vector<float> historiaCzasu;
    std::vector<float> historiaTemperatury;
    std::vector<float> historiaGrzejnika;
    float czasSymulacji;

    void iteracja(float dT);

public:
    Symulacja();

    void ustawRegulator(Regulator* r) { regulator = r; }
    Pomieszczenie* getPomieszczenie() { return &pokoj; }
    Grzejnik* getGrzejnik() { return &piec; }

    void przebieg(int ileIteracji, float dT);
    void zapiszWyniki(const std::string& nazwaPliku);
};
