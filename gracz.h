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
    
    bool getSpasowal() const { return spasowal; } 
    
    void decyduj(Kasyno* kasyno); 

    void resetuj(); // Resetuje stan gracza przed nowa gra
};
