#pragma once
#include <vector>
#include <string>
#include "Venta.h"

class RegistroVentas {
private:
    std::vector<Venta> ventas;

public:
    bool cargarCSV(const std::string &ruta);
    const std::vector<Venta>& getVentas() const { return ventas; }

    double ventasTotales() const;
    double promedioVentas() const;
    Venta ventaMaxima() const;

};
