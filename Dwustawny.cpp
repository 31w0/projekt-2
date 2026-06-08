#include "Dwustawny.h"

Dwustawny::Dwustawny(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana)
    : Regulator(_pokoj, _piec, _zadana) {}

float Dwustawny::steruj(float dT) {
    if (pokoj->getTemperatura() < zadanaTemperatura) {
        return 1.0f;
    } else {
        return 0.0f;
    }
}
