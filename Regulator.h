#pragma once
#include "Pomieszczenie.h"
#include "Grzejnik.h"

class Regulator {
protected:
    Pomieszczenie* pokoj;
    Grzejnik* piec;
    float zadanaTemperatura;

public:
    Regulator(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana = 22.0f);
    virtual ~Regulator() {}
    virtual float steruj(float dT) = 0;
    void aktualizuj(float dT);
};
