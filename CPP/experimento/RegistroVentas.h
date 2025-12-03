#pragma once
#include <vector>
#include <string>
#include <map>
#include "Venta.h"

struct EstadisticasPais {
    double total;
    double promedio;
    double maximo;
    double minimo;
    int cantidad;
    std::string nombrePais;
};

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
    
    // Nuevas funcionalidades
    std::vector<Venta> filtrarPorPais(const std::string& pais) const;
    std::vector<Venta> filtrarPorCategoria(const std::string& categoria) const;
    std::vector<Venta> filtrarPorRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) const;
    EstadisticasPais calcularEstadisticasPais(const std::string& pais) const;
    std::map<std::string, EstadisticasPais> calcularEstadisticasTodosPaises() const;
    
    void mostrarTablaFiltrada(const std::vector<Venta>& ventasFiltradas) const;
    void mostrarEstadisticasPorPais(const std::string& pais) const;
    void mostrarEstadisticasTodosPaises() const;
    
    std::vector<std::string> obtenerPaisesUnicos() const;
    std::vector<std::string> obtenerCategoriasUnicas() const;
};