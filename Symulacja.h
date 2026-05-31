#pragma once
#include "Pomieszczenie.h"
#include "Grzejnik.h"
#include <vector>
#include <string>

class Symulacja {
private:
    Pomieszczenie pokoj;
    Grzejnik piec;

    std::vector<float> historiaCzasu;
    std::vector<float> historiaTemperatury;
    float czasSymulacji;

    void iteracja(float dT);

public:
    Symulacja();
    void przebieg(int ileIteracji, float dT);
    void zapiszWyniki(const std::string& nazwaPliku);
};

