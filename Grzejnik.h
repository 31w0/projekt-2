#pragma once

class Grzejnik {
private:
    float mocMaksymalna;
    float mocAktualna;

public:
    Grzejnik(float _mocMaksymalna = 5000.0f);

    void ustawMoc(float nowaMoc);
    float emitujCieplo(float dT);
};
