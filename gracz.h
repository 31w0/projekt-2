#pragma once
#include "Karta.h"

// Deklaracja wyprzedzająca (forward declaration) w celu uniknięcia pętli załączeń
class Kasyno; 

class Gracz {
private:
    Karta* reka[10];
    int liczbaKart;
    int sumaPunktow;
    bool spasowal; // Informacja czy gracz spasował

public:
    Gracz();
    void wezKarte(Karta* _karta);
    void pokazKarty();
    int getSumaPunktow() const { return sumaPunktow; }
    
    // Akcesor do odczytu informacji o pasowaniu
    bool getSpasowal() const { return spasowal; } 
    
    // Metoda realizująca dwukierunkową asocjację (gracz używa kasyna)
    void decyduj(Kasyno* kasyno); 
};
