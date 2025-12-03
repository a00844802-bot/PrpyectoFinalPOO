#include "Venta.h"

Venta::Venta()
    : idVenta("N/A"), fecha("N/A"), montoUnit(0), cantidad(0),
      categoria("N/A"), metodoPago("N/A"), clienteID("N/A"),
      pais("N/A"), costoEnvio(0), descuento(0), impuesto(0),
      subtotal(0), totalConDescuento(0), totalConImpuesto(0),
      totalFinal(0) {}

Venta::Venta(const string& idV,
             const string& fech,
             double monto,
             int cant,
             const string& cat,
             const string& metodo,
             const string& cliente,
             const string& p,
             double costo,
             double desc,
             double imp,
             double sub,
             double totalDesc,
             double totalImp,
             double totalF)
    : idVenta(idV), fecha(fech), montoUnit(monto), cantidad(cant),
      categoria(cat), metodoPago(metodo), clienteID(cliente),
      pais(p), costoEnvio(costo), descuento(desc), impuesto(imp),
      subtotal(sub), totalConDescuento(totalDesc),
      totalConImpuesto(totalImp), totalFinal(totalF) {}