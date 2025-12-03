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

struct Alerta {
    std::string tipo;
    std::string mensaje;
    std::string nivel; // "CRITICO", "ADVERTENCIA", "INFO"
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
    
    // Funcionalidades existentes
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
    
    // NUEVAS FUNCIONALIDADES - DASHBOARD
    void mostrarDashboard() const;
    void mostrarGraficoBarras(const std::map<std::string, double>& datos, const std::string& titulo) const;
    void mostrarGraficoBarrasHorizontal(const std::map<std::string, double>& datos, const std::string& titulo, int anchoMax = 50) const;
    std::map<std::string, int> obtenerVentasPorCategoria() const;
    std::map<std::string, double> obtenerTotalesPorPais() const;
    std::map<std::string, int> obtenerVentasPorMes() const;
    
    // NUEVAS FUNCIONALIDADES - ALERTAS
    std::vector<Alerta> generarAlertas() const;
    void mostrarAlertas() const;
    std::vector<std::string> detectarPaisesBajoRendimiento() const;
    std::vector<std::string> detectarCategoriasPocoVendidas() const;
    std::vector<Venta> detectarVentasAtipicas() const;
};