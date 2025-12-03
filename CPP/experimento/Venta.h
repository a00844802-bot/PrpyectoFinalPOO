#pragma once
#include <string>
using std::string;

class Venta {
public:
    string idVenta;
    string fecha;
    double montoUnit;
    int cantidad;
    string categoria;
    string metodoPago;
    string clienteID;
    string pais;
    double costoEnvio;
    double descuento;
    double impuesto;
    double subtotal;
    double totalConDescuento;
    double totalConImpuesto;
    double totalFinal;

    Venta();
    Venta(const string& idVenta,
          const string& fecha,
          double montoUnit,
          int cantidad,
          const string& categoria,
          const string& metodoPago,
          const string& clienteID,
          const string& pais,
          double costoEnvio,
          double descuento,
          double impuesto,
          double subtotal,
          double totalConDescuento,
          double totalConImpuesto,
          double totalFinal);
};