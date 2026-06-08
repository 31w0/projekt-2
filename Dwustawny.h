#pragma once
#include "Regulator.h"

class Dwustawny : public Regulator {
public:
    Dwustawny(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana = 22.0f);
    float steruj(float dT) override;
};
