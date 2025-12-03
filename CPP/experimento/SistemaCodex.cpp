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
        std::cout << "\n=== Codex Product Platform ===\n";
        std::cout << "1. Cargar archivo ventas_codex_platform.csv\n";
        std::cout << "2. Ventas totales\n";
        std::cout << "3. Venta máxima\n";
        std::cout << "4. Buscar venta por ID\n";
        std::cout << "5. Mostrar todas las ventas\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opc;

        if (opc == 1) {
            if (registro.cargarCSV("ventas_codex_platform.csv"))
                std::cout << "✓ Archivo cargado exitosamente.\n";
            else
                std::cout << "✗ Error al cargar archivo.\n";
            pausar();
        }
        else if (opc == 2) {
            std::cout << "Ventas totales: $" << registro.ventasTotales() << "\n";
            pausar();
        }
        else if (opc == 3) {
            auto v = registro.ventaMaxima();
            std::cout << "\n=== Venta más grande ===\n";
            std::cout << "ID: " << v.idVenta << "\n"
                      << "Fecha: " << v.fecha << "\n"
                      << "Categoría: " << v.categoria << "\n"
                      << "País: " << v.pais << "\n"
                      << "Total final: $" << v.totalFinal << "\n";
            pausar();
        }
        else if (opc == 4) {
            string id;
            cout << "ID de venta: ";
            cin >> id;
            auto* v = registro.buscarVenta(id);
            
            if (v) {
                std::cout << "\n=== Venta encontrada ===\n";
                std::cout << "ID: " << v->idVenta << "\n"
                          << "Fecha: " << v->fecha << "\n"
                          << "Monto unitario: $" << v->montoUnit << "\n"
                          << "Cantidad: " << v->cantidad << "\n"
                          << "Categoría: " << v->categoria << "\n"
                          << "Método de pago: " << v->metodoPago << "\n"
                          << "Cliente ID: " << v->clienteID << "\n"
                          << "País: " << v->pais << "\n"
                          << "Costo envío: $" << v->costoEnvio << "\n"
                          << "Descuento: $" << v->descuento << "\n"
                          << "Impuesto: $" << v->impuesto << "\n"
                          << "Subtotal: $" << v->subtotal << "\n"
                          << "Total con descuento: $" << v->totalConDescuento << "\n"
                          << "Total con impuesto: $" << v->totalConImpuesto << "\n"
                          << "TOTAL FINAL: $" << v->totalFinal << "\n";
            } else {
                std::cout << "✗ No existe una venta con ese ID.\n";
            }
            pausar();
        }
        else if (opc == 5) {
            registro.mostrarTodas();
            pausar();
        }

    } while (opc != 0);

    std::cout << "\nSaliendo de Codex Product Platform...\n";
}