#include "Regulator.h"

Regulator::Regulator(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana)
    : pokoj(_pokoj), piec(_piec), zadanaTemperatura(_zadana) {}

void Regulator::aktualizuj(float dT) {
    float nowaNastawa = steruj(dT);
    piec->ustawNastawe(nowaNastawa);
}
