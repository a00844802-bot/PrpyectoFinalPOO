#include "RegistroVentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>

bool RegistroVentas::cargarCSV(const std::string& nombreArchivo) {
    ventas.clear();

    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir archivo CSV.\n";
        return false;
    }

    std::string linea;
    getline(file, linea); // saltar encabezados

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string idVenta, fecha, montoStr, cantStr, categoria, metodoPago,
                    clienteID, pais, costoStr, descStr, impStr, subStr,
                    totalDescStr, totalImpStr, totalFinStr;

        getline(ss, idVenta, ',');
        getline(ss, fecha, ',');
        getline(ss, montoStr, ',');
        getline(ss, cantStr, ',');
        getline(ss, categoria, ',');
        getline(ss, metodoPago, ',');
        getline(ss, clienteID, ',');
        getline(ss, pais, ',');
        getline(ss, costoStr, ',');
        getline(ss, descStr, ',');
        getline(ss, impStr, ',');
        getline(ss, subStr, ',');
        getline(ss, totalDescStr, ',');
        getline(ss, totalImpStr, ',');
        getline(ss, totalFinStr, ',');

        double monto = std::stod(montoStr);
        int cantidad = std::stoi(cantStr);
        double costo = std::stod(costoStr);
        double desc = std::stod(descStr);
        double imp = std::stod(impStr);
        double sub = std::stod(subStr);
        double totalDesc = std::stod(totalDescStr);
        double totalImp = std::stod(totalImpStr);
        double totalFin = std::stod(totalFinStr);

        Venta v(idVenta, fecha, monto, cantidad, categoria, metodoPago,
                clienteID, pais, costo, desc, imp, sub, totalDesc,
                totalImp, totalFin);
        ventas.push_back(v);
    }

    file.close();
    return true;
}

double RegistroVentas::ventasTotales() const {
    double total = 0;
    for (const auto& v : ventas) total += v.totalFinal;
    return total;
}

Venta RegistroVentas::ventaMaxima() const {
    if (ventas.empty()) return Venta();

    const Venta* maxVenta = &ventas[0];
    for (const auto& v : ventas)
        if (v.totalFinal > maxVenta->totalFinal)
            maxVenta = &v;

    return *maxVenta;
}

void RegistroVentas::mostrarTodas() const {
    for (const auto& v : ventas) {
        std::cout << "ID: " << v.idVenta
                  << " | Fecha: " << v.fecha
                  << " | Categoria: " << v.categoria
                  << " | Total: " << v.totalFinal << "\n";
    }
}

void RegistroVentas::mostrarTabla() const {
    std::cout << "\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(13) << "Fecha"
              << std::setw(16) << "Categoria"
              << std::setw(16) << "Pais"
              << std::setw(10) << "Cantidad"
              << std::setw(14) << "Total"
              << "\n";
    std::cout << std::string(77, '-') << "\n";

    for (const auto& v : ventas) {
        std::cout << std::left
                  << std::setw(8) << v.idVenta
                  << std::setw(13) << v.fecha.substr(0, 10)
                  << std::setw(16) << v.categoria
                  << std::setw(16) << v.pais
                  << std::setw(10) << v.cantidad
                  << "$" << std::fixed << std::setprecision(2) << v.totalFinal
                  << "\n";
    }
    std::cout << std::string(77, '-') << "\n";
}

void RegistroVentas::mostrarDetalleVenta(const Venta& v) const {
    std::cout << "\n+============================================================+\n";
    std::cout << "|                   DETALLE DE VENTA                         |\n";
    std::cout << "+============================================================+\n\n";
    
    std::cout << std::left << std::setw(25) << "ID:" << v.idVenta << "\n";
    std::cout << std::left << std::setw(25) << "Fecha:" << v.fecha << "\n";
    std::cout << std::left << std::setw(25) << "Categoria:" << v.categoria << "\n";
    std::cout << std::left << std::setw(25) << "Metodo de pago:" << v.metodoPago << "\n";
    std::cout << std::left << std::setw(25) << "Cliente ID:" << v.clienteID << "\n";
    std::cout << std::left << std::setw(25) << "Pais:" << v.pais << "\n";
    
    std::cout << std::string(60, '-') << "\n";
    
    std::cout << std::left << std::setw(25) << "Monto unitario:" 
              << "$" << std::fixed << std::setprecision(2) << v.montoUnit << "\n";
    std::cout << std::left << std::setw(25) << "Cantidad:" << v.cantidad << "\n";
    std::cout << std::left << std::setw(25) << "Subtotal:" 
              << "$" << v.subtotal << "\n";
    std::cout << std::left << std::setw(25) << "Costo envio:" 
              << "$" << v.costoEnvio << "\n";
    std::cout << std::left << std::setw(25) << "Descuento:" 
              << "$" << v.descuento << "\n";
    std::cout << std::left << std::setw(25) << "Impuesto:" 
              << "$" << v.impuesto << "\n";
    
    std::cout << std::string(60, '=') << "\n";
    
    std::cout << std::left << std::setw(25) << "TOTAL FINAL:" 
              << "$" << v.totalFinal << "\n\n";
}

Venta* RegistroVentas::buscarVenta(const std::string& id) {
    for (auto& v : ventas) {
        if (v.idVenta == id)
            return &v;
    }
    return nullptr;
}

// ==================== NUEVAS FUNCIONALIDADES ====================

std::vector<Venta> RegistroVentas::filtrarPorPais(const std::string& pais) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.pais == pais) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

std::vector<Venta> RegistroVentas::filtrarPorCategoria(const std::string& categoria) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.categoria == categoria) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

std::vector<Venta> RegistroVentas::filtrarPorRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.fecha >= fechaInicio && v.fecha <= fechaFin) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

EstadisticasPais RegistroVentas::calcularEstadisticasPais(const std::string& pais) const {
    EstadisticasPais stats;
    stats.nombrePais = pais;
    stats.total = 0;
    stats.cantidad = 0;
    stats.maximo = 0;
    stats.minimo = 999999999;
    
    for (const auto& v : ventas) {
        if (v.pais == pais) {
            stats.total += v.totalFinal;
            stats.cantidad++;
            
            if (v.totalFinal > stats.maximo) {
                stats.maximo = v.totalFinal;
            }
            if (v.totalFinal < stats.minimo) {
                stats.minimo = v.totalFinal;
            }
        }
    }
    
    if (stats.cantidad > 0) {
        stats.promedio = stats.total / stats.cantidad;
    } else {
        stats.promedio = 0;
        stats.minimo = 0;
    }
    
    return stats;
}

std::map<std::string, EstadisticasPais> RegistroVentas::calcularEstadisticasTodosPaises() const {
    std::map<std::string, EstadisticasPais> estadisticas;
    
    std::set<std::string> paises;
    for (const auto& v : ventas) {
        paises.insert(v.pais);
    }
    
    for (const auto& pais : paises) {
        estadisticas[pais] = calcularEstadisticasPais(pais);
    }
    
    return estadisticas;
}

void RegistroVentas::mostrarTablaFiltrada(const std::vector<Venta>& ventasFiltradas) const {
    if (ventasFiltradas.empty()) {
        std::cout << "\n[!] No se encontraron ventas con los criterios especificados.\n";
        return;
    }
    
    std::cout << "\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(13) << "Fecha"
              << std::setw(16) << "Categoria"
              << std::setw(16) << "Pais"
              << std::setw(10) << "Cantidad"
              << std::setw(14) << "Total"
              << "\n";
    std::cout << std::string(77, '-') << "\n";

    for (const auto& v : ventasFiltradas) {
        std::cout << std::left
                  << std::setw(8) << v.idVenta
                  << std::setw(13) << v.fecha.substr(0, 10)
                  << std::setw(16) << v.categoria
                  << std::setw(16) << v.pais
                  << std::setw(10) << v.cantidad
                  << "$" << std::fixed << std::setprecision(2) << v.totalFinal
                  << "\n";
    }
    std::cout << std::string(77, '-') << "\n";
    std::cout << "Total de ventas encontradas: " << ventasFiltradas.size() << "\n";
}

void RegistroVentas::mostrarEstadisticasPorPais(const std::string& pais) const {
    EstadisticasPais stats = calcularEstadisticasPais(pais);
    
    if (stats.cantidad == 0) {
        std::cout << "\n[!] No hay ventas registradas para el pais: " << pais << "\n";
        return;
    }
    
    std::cout << "\n+============================================================+\n";
    std::cout << "|              ESTADISTICAS POR PAIS: " << std::left << std::setw(19) << pais << "|\n";
    std::cout << "+============================================================+\n\n";
    
    std::cout << std::left << std::setw(25) << "Pais:" << stats.nombrePais << "\n";
    std::cout << std::left << std::setw(25) << "Cantidad de ventas:" << stats.cantidad << "\n";
    std::cout << std::left << std::setw(25) << "Total vendido:" 
              << "$" << std::fixed << std::setprecision(2) << stats.total << "\n";
    std::cout << std::left << std::setw(25) << "Promedio por venta:" 
              << "$" << stats.promedio << "\n";
    std::cout << std::left << std::setw(25) << "Venta maxima:" 
              << "$" << stats.maximo << "\n";
    std::cout << std::left << std::setw(25) << "Venta minima:" 
              << "$" << stats.minimo << "\n\n";
}

void RegistroVentas::mostrarEstadisticasTodosPaises() const {
    auto estadisticas = calcularEstadisticasTodosPaises();
    
    std::cout << "\n+=======================================================================================+\n";
    std::cout << "|                         ESTADISTICAS POR TODOS LOS PAISES                            |\n";
    std::cout << "+=======================================================================================+\n\n";
    
    std::cout << std::left
              << std::setw(18) << "Pais"
              << std::setw(10) << "Ventas"
              << std::setw(15) << "Total"
              << std::setw(15) << "Promedio"
              << std::setw(15) << "Maximo"
              << std::setw(15) << "Minimo"
              << "\n";
    std::cout << std::string(88, '-') << "\n";
    
    for (const auto& pair : estadisticas) {
        const EstadisticasPais& stats = pair.second;
        std::cout << std::left
                  << std::setw(18) << stats.nombrePais
                  << std::setw(10) << stats.cantidad
                  << "$" << std::setw(14) << std::fixed << std::setprecision(2) << stats.total
                  << "$" << std::setw(14) << stats.promedio
                  << "$" << std::setw(14) << stats.maximo
                  << "$" << std::setw(14) << stats.minimo
                  << "\n";
    }
    std::cout << std::string(88, '-') << "\n";
}

std::vector<std::string> RegistroVentas::obtenerPaisesUnicos() const {
    std::set<std::string> paisesSet;
    for (const auto& v : ventas) {
        paisesSet.insert(v.pais);
    }
    return std::vector<std::string>(paisesSet.begin(), paisesSet.end());
}

std::vector<std::string> RegistroVentas::obtenerCategoriasUnicas() const {
    std::set<std::string> categoriasSet;
    for (const auto& v : ventas) {
        categoriasSet.insert(v.categoria);
    }
    return std::vector<std::string>(categoriasSet.begin(), categoriasSet.end());
}