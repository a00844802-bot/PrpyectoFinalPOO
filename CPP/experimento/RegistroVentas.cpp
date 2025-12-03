#include "RegistroVentas.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

        // Leer las 15 columnas separadas por comas
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

        // Convertir strings a números
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
                  << " | Categoría: " << v.categoria
                  << " | Total: " << v.totalFinal << "\n";
    }
}

Venta* RegistroVentas::buscarVenta(const string& id) {
    for (auto& v : ventas) {
        if (v.idVenta == id)
            return &v;
    }
    return nullptr;
}