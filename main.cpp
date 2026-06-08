#include "Symulacja.h"
#include "Dwustawny.h"
#include "PID.h"
#include <iostream>

int main() {
    std::cout << " SYMULACJA: REGULATOR DWUSTAWNY \n";
    Symulacja sym1;
    Dwustawny regDwustawny(sym1.getPomieszczenie(), sym1.getGrzejnik(), 22.0f);
    sym1.ustawRegulator(&regDwustawny);
    sym1.przebieg(300, 1.0f);
    sym1.zapiszWyniki("wyniki_dwustawny.csv");

    std::cout << "\n--- SYMULACJA: REGULATOR PID ---\n";
    Symulacja sym2;
    PID regPID(sym2.getPomieszczenie(), sym2.getGrzejnik(), 22.0f);
    sym2.ustawRegulator(&regPID);
    sym2.przebieg(300, 1.0f);
    sym2.zapiszWyniki("wyniki_pid.csv");

    return 0;
}
