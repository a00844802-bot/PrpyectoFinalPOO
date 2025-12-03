#pragma once
#include <string>

enum class CategoriaProducto {
    ELECTRONICA,
    HOGAR,
    JUGUETERIA,
    ROPA,
    OTROS
};

inline std::string categoriaToString(CategoriaProducto c) {
    switch (c) {
    case CategoriaProducto::ELECTRONICA: return "Electrónica";
    case CategoriaProducto::HOGAR:       return "Hogar";
    case CategoriaProducto::JUGUETERIA:  return "Juguetería";
    case CategoriaProducto::ROPA:        return "Ropa";
    default: return "Otros";
    }
}
