#include "Venta.h"

Venta::Venta()
    : idVenta("N/A"), idProducto("N/A"),
      cantidad(0), precioUnitario(0), totalFinal(0) {}

Venta::Venta(const string& idV,
             const string& idP,
             int cant,
             double precio)
    : idVenta(idV),
      idProducto(idP),
      cantidad(cant),
      precioUnitario(precio) {
    calcularTotal();
}

void Venta::calcularTotal() {
    totalFinal = cantidad * precioUnitario;
}

