#include "SistemaCodex.h"
#include <iostream>

void SistemaCodex::menu() {
    int opc;
    do {
        std::cout << "\nCodex Product Platform\n";
        std::cout << "1. Cargar archivo ventas_codex_platform.csv\n";
        std::cout << "2. Ventas totales\n";
        std::cout << "3. Venta máxima\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opc;

        if (opc == 1) {
            registro.cargarCSV("ventas_codex_platform.csv");
            std::cout << "Archivo cargado.\n";
        }
        else if (opc == 2) {
            std::cout << "Ventas totales: " << registro.ventasTotales() << "\n";
        }
        else if (opc == 3) {
            auto v = registro.ventaMaxima();
            std::cout << "Venta max: " << v.totalFinal << " ID: " << v.idVenta << "\n";
        }

    } while (opc != 0);
}
