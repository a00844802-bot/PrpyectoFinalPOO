#include "SistemaCodex.h"
#include <iostream>
#include <iomanip>

using namespace std;

void SistemaCodex::pausar() {
    std::cout << "\nPresiona ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void SistemaCodex::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void SistemaCodex::menu() {
    int opc;
    do {
        limpiarPantalla();
        std::cout << "\n";
        std::cout << "+============================================================+\n";
        std::cout << "|            CODEX PRODUCT PLATFORM                          |\n";
        std::cout << "+============================================================+\n";
        std::cout << "\n";
        std::cout << "  [1] Cargar archivo CSV\n";
        std::cout << "  [2] Ventas totales\n";
        std::cout << "  [3] Venta maxima\n";
        std::cout << "  [4] Buscar venta por ID\n";
        std::cout << "  [5] Mostrar todas las ventas\n";
        std::cout << "  [0] Salir\n";
        std::cout << "\n";
        std::cout << "  Opcion: ";
        std::cin >> opc;

        limpiarPantalla();

        if (opc == 1) {
            std::cout << "\nCargando archivo...\n";
            if (registro.cargarCSV("ventas_codex_platform.csv")) {
                std::cout << "[OK] Archivo cargado exitosamente!\n";
            } else {
                std::cout << "[ERROR] Error al cargar archivo.\n";
            }
            pausar();
        }
        else if (opc == 2) {
            std::cout << "\n+============================================================+\n";
            std::cout << "|                    VENTAS TOTALES                          |\n";
            std::cout << "+============================================================+\n";
            std::cout << "\n  Total: $" << fixed << setprecision(2) << registro.ventasTotales() << "\n";
            pausar();
        }
        else if (opc == 3) {
            auto v = registro.ventaMaxima();
            std::cout << "\n+============================================================+\n";
            std::cout << "|                     VENTA MAXIMA                           |\n";
            std::cout << "+============================================================+\n\n";
            
            std::cout << left << setw(25) << "ID:" << v.idVenta << "\n";
            std::cout << left << setw(25) << "Fecha:" << v.fecha << "\n";
            std::cout << left << setw(25) << "Categoria:" << v.categoria << "\n";
            std::cout << left << setw(25) << "Pais:" << v.pais << "\n";
            std::cout << left << setw(25) << "Total:" << "$" << fixed << setprecision(2) << v.totalFinal << "\n";
            
            pausar();
        }
        else if (opc == 4) {
            string id;
            std::cout << "\n  ID de venta: ";
            cin >> id;
            
            auto* v = registro.buscarVenta(id);
            
            if (v) {
                registro.mostrarDetalleVenta(*v);
            } else {
                std::cout << "\n[X] No existe una venta con ese ID.\n";
            }
            pausar();
        }
        else if (opc == 5) {
            std::cout << "\n+============================================================+\n";
            std::cout << "|                   TODAS LAS VENTAS                         |\n";
            std::cout << "+============================================================+\n";
            
            registro.mostrarTabla();
            pausar();
        }

    } while (opc != 0);

    std::cout << "\nSaliendo de Codex Product Platform...\n";
}