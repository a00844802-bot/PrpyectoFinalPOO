#pragma once
#include "RegistroVentas.h"

class SistemaCodex {
private:
    RegistroVentas registro;

    void pausar();
    void limpiarPantalla();
    void menuFiltros();
    void menuEstadisticas();

public:
    void menu();
};