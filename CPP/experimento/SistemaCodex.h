#pragma once
#include "RegistroVentas.h"

class SistemaCodex {
private:
    RegistroVentas registro;

    void pausar();
    void limpiarPantalla();

public:
    void menu();
};