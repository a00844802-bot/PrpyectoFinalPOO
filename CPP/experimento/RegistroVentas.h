#pragma once
#include <vector>
#include <string>
#include "Venta.h"

class RegistroVentas {
private:
    std::vector<Venta> ventas;

public:
    bool cargarCSV(const std::string& nombreArchivo);
    double ventasTotales() const;
    Venta ventaMaxima() const;
    void mostrarTodas() const;
    Venta* buscarVenta(const string& id);
};
