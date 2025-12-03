#pragma once
#include <string>

enum class MetodoPago { Tarjeta, Contactless, Transferencia, Efectivo, Wallet };
enum class Categoria {
    Supermercado, Tecnologia, Moda, Hogar, Servicios, Gaming, Jugueteria,
    Oficina, Mascotas, Salud, Bebidas, Automotriz
};

std::string metodoPagoToString(MetodoPago m);
std::string categoriaToString(Categoria c);
