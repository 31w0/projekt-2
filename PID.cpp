#include "PID.h"

PID::PID(Pomieszczenie* _pokoj, Grzejnik* _piec, float _zadana)
    : Regulator(_pokoj, _piec, _zadana), 
      Kp(4.0f), Ki(0.01f), Kd(0.5f), 
      uchybCalka(0.0f), uchybPoprzedni(0.0f) {}

float PID::steruj(float dT) {
    float tempAktualna = pokoj->getTemperatura();
    float uchyb = zadanaTemperatura - tempAktualna;
    
    float Up = Kp * uchyb;
    
    uchybCalka += uchyb * dT;
    if (uchybCalka > 1000.0f) uchybCalka = 1000.0f;
    else if (uchybCalka < -1000.0f) uchybCalka = -1000.0f;
    
    float Ui = Ki * uchybCalka;
    
    float deltaUchyb = (uchyb - uchybPoprzedni) / dT;
    float Ud = Kd * deltaUchyb;
    
    uchybPoprzedni = uchyb;
    
    return Up + Ui + Ud;
}
