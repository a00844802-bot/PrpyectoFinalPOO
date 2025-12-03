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
    getline(file, linea); // primera línea (encabezados)

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string idVenta, idProducto, cantidadStr, precioStr;

        getline(ss, idVenta, ',');
        getline(ss, idProducto, ',');
        getline(ss, cantidadStr, ',');
        getline(ss, precioStr, ',');

        int cantidad = std::stoi(cantidadStr);
        double precio = std::stod(precioStr);

        Venta v(idVenta, idProducto, cantidad, precio);
        ventas.push_back(v);
    }

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
                  << "  Producto: " << v.idProducto
                  << "  Cantidad: " << v.cantidad
                  << "  Total: " << v.totalFinal << "\n";
    }
}

Venta* RegistroVentas::buscarVenta(const string& id) {
    for (auto& v : ventas) {
        if (v.idVenta == id)
            return &v;
    }
    return nullptr;
}