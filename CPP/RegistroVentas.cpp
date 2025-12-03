#include "RegistroVentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>

static std::vector<std::string_view> splitCommas(std::string_view linea) {
    std::vector<std::string_view> cols;
    size_t i = 0;
    while (i < linea.size()) {
        while (i < linea.size() && linea[i] == ',') i++;
        if (i >= linea.size()) break;
        size_t fin = linea.find(',', i);
        if (fin == std::string_view::npos) {
            cols.push_back(linea.substr(i));
            break;
        }
        cols.push_back(linea.substr(i, fin - i));
        i = fin + 1;
    }
    return cols;
}

bool RegistroVentas::cargarCSV(const std::string &ruta) {
    std::ifstream file(ruta);
    if (!file.is_open()) return false;

    std::string linea;
    std::getline(file, linea); // skip header

    while (std::getline(file, linea)) {
        std::string_view sv = linea;
        auto cols = splitCommas(sv);
        if (cols.size() < 15) continue;

        Venta v;
        v.idVenta = std::stoi(std::string(cols[0]));

        int y = std::stoi(std::string(cols[1].substr(0,4)));
        int m = std::stoi(std::string(cols[1].substr(5,2)));
        int d = std::stoi(std::string(cols[1].substr(8,2)));
        v.fecha = std::chrono::year_month_day(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d));

        v.montoUnitario = std::stod(std::string(cols[2]));
        v.cantidad = std::stoi(std::string(cols[3]));

        v.categoria = Categoria::Supermercado; // luego se mapeará
        v.metodoPago = MetodoPago::Tarjeta;   // luego se mapeará

        v.clienteID = std::stoi(std::string(cols[6]));
        v.pais = std::string(cols[7]);
        v.costoEnvio = std::stod(std::string(cols[8]));
        v.descuento = std::stod(std::string(cols[9]));
        v.impuesto = std::stod(std::string(cols[10]));
        v.subtotal = std::stod(std::string(cols[11]));
        v.totalConDescuento = std::stod(std::string(cols[12]));
        v.totalConImpuesto = std::stod(std::string(cols[13]));
        v.totalFinal = std::stod(std::string(cols[14]));

        ventas.push_back(v);
    }
    return true;
}

double RegistroVentas::ventasTotales() const {
    double suma = 0;
    for (auto &v : ventas) suma += v.totalFinal;
    return suma;
}

double RegistroVentas::promedioVentas() const {
    if (ventas.empty()) return 0;
    return ventasTotales() / ventas.size();
}

Venta RegistroVentas::ventaMaxima() const {
    Venta max = ventas.front();
    for (auto &v : ventas) if (v.totalFinal > max.totalFinal) max = v;
    return max;
}