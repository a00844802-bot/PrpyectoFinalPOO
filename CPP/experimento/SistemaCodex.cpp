#include "SistemaCodex.h"
#include <iostream>

using namespace std;

void SistemaCodex::pausar() {
    std::cout << "\nPresiona ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void SistemaCodex::menu() {
    int opc;
    do {
        std::cout << "\nCodex Product Platform\n";
        std::cout << "1. Cargar archivo ventas_codex_platform.csv\n";
        std::cout << "2. Ventas totales\n";
        std::cout << "3. Venta máxima\n";
        std::cout << "4. Buscar venta por ID\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opc;

        if (opc == 1) {
            registro.cargarCSV("ventas_codex_platform.csv");
            std::cout << "Archivo cargado.\n";
            pausar();
        }
        else if (opc == 2) {
            std::cout << "Ventas totales: " << registro.ventasTotales() << "\n";
            pausar();
        }
        else if (opc == 3) {
            auto v = registro.ventaMaxima();
            std::cout << "Venta más grande:\n";
            std::cout << "ID: " << v.idVenta << " | Total final: " << v.totalFinal << "\n";
            pausar();
        }
        else if (opc == 4) {
            string id;
            cout << "ID de venta: ";
            cin >> id;
            auto* v = registro.buscarVenta(id);
            
            if (v) {
                std::cout << "Venta encontrada:\n";
                std::cout << "ID: " << v->idVenta << "\n"
                          << "Producto: " << v->nombreProducto << "\n"
                          << "Cantidad: " << v->cantidad << "\n"
                          << "Precio: " << v->precioUnitario << "\n"
                          << "Total: " << v->totalFinal << "\n";
            } else {
                std::cout << "No existe una venta con ese ID.\n";
            }
            pausar();
        }

    } while (opc != 0);

    std::cout << "\nSaliendo de Codex Product Platform...\n";
}
