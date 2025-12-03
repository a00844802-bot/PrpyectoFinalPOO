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
    void mostrarTabla() const;
    void mostrarDetalleVenta(const Venta& v) const;
    Venta* buscarVenta(const std::string& id);
    const std::vector<Venta>& obtenerVentas() const { return ventas; }
};