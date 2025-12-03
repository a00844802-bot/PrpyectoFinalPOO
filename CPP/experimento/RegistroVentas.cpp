#include "RegistroVentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

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
    // Encabezado
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

    // Filas
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