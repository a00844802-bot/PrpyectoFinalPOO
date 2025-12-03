#include "Enums.h"

std::string metodoPagoToString(MetodoPago m) {
    switch(m) {
        case MetodoPago::Tarjeta: return "Tarjeta";
        case MetodoPago::Contactless: return "Contactless";
        case MetodoPago::Transferencia: return "Transferencia";
        case MetodoPago::Efectivo: return "Efectivo";
        default: return "Wallet";
    }
}

std::string categoriaToString(Categoria c) {
    switch(c) {
        case Categoria::Supermercado: return "Supermercado";
        case Categoria::Tecnologia: return "Tecnologia";
        case Categoria::Moda: return "Moda";
        case Categoria::Hogar: return "Hogar";
        case Categoria::Servicios: return "Servicios";
        case Categoria::Gaming: return "Gaming";
        case Categoria::Jugueteria: return "Jugueteria";
        case Categoria::Oficina: return "Oficina";
        case Categoria::Mascotas: return "Mascotas";
        case Categoria::Salud: return "Salud";
        case Categoria::Bebidas: return "Bebidas";
        default: return "Automotriz";
    }
}
