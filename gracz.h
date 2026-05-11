#pragma once
#include "Karta.h"

class Kasyno; 

class Gracz {

protected: 
    Karta* reka[10];
    int liczbaKart;
    int sumaPunktow;
    bool spasowal;

public:
    Gracz();
    void wezKarte(Karta* _karta);
    void pokazKarty();
    int getSumaPunktow() const { return sumaPunktow; }
    bool getSpasowal() const { return spasowal; } 
    
    void decyduj(Kasyno* kasyno); 
    void resetuj();
};
