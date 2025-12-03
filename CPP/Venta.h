#pragma once
#include <string>
#include <chrono>
#include "Enums.h"

struct Venta {
    int idVenta;
    std::chrono::year_month_day fecha;
    double montoUnitario;
    int cantidad;
    Categoria categoria;
    MetodoPago metodoPago;
    int clienteID;
    std::string pais;
    double costoEnvio;
    double descuento;
    double impuesto;
    double subtotal;
    double totalConDescuento;
    double totalConImpuesto;
    double totalFinal;
};
