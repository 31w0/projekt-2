#pragma once
#include "Regulator.h"

class PID : public Regulator {
private:
    float Kp, Ki, Kd;
    float uchybCalka;
    float uchybPoprzedni;

public:
    PID(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana = 22.0f);
    float steruj(float dT) override;
};
