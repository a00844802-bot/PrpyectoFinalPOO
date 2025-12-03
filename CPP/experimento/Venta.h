#pragma once
#include <string>
using std::string;

class Venta {
public:
    string idVenta;
    string idProducto;
    string nombreProducto;
    int cantidad;
    double precioUnitario;
    double totalFinal;

    Venta();
    Venta(const string& idVenta,
          const string& idProducto,
          int cantidad,
          double precioUnitario);

    void calcularTotal();
};
