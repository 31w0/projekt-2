#include "Grzejnik.h"

Grzejnik::Grzejnik(float _mocMaksymalna)
    : mocMaksymalna(_mocMaksymalna), mocAktualna(0.0f) {
}

void Grzejnik::ustawMoc(float nowaMoc) {
    if (nowaMoc > mocMaksymalna) {
        mocAktualna = mocMaksymalna;
    }
    else if (nowaMoc < 0.0f) {
        mocAktualna = 0.0f; 
    }
    else {
        mocAktualna = nowaMoc;
    }
}

float Grzejnik::emitujCieplo(float dT) {

    return mocAktualna;
}