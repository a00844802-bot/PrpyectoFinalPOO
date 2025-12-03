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

void SistemaCodex::menuFiltros() {
    int opc;
    do {
        limpiarPantalla();
        std::cout << "\n";
        std::cout << "+============================================================+\n";
        std::cout << "|                  MENU DE FILTROS                           |\n";
        std::cout << "+============================================================+\n";
        std::cout << "\n";
        std::cout << "  [1] Filtrar por pais\n";
        std::cout << "  [2] Filtrar por categoria\n";
        std::cout << "  [3] Filtrar por rango de fechas\n";
        std::cout << "  [0] Volver al menu principal\n";
        std::cout << "\n";
        std::cout << "  Opcion: ";
        std::cin >> opc;

        limpiarPantalla();

        if (opc == 1) {
            // Mostrar países disponibles
            auto paises = registro.obtenerPaisesUnicos();
            std::cout << "\nPaises disponibles:\n";
            std::cout << std::string(40, '-') << "\n";
            for (size_t i = 0; i < paises.size(); i++) {
                std::cout << "  [" << (i+1) << "] " << paises[i] << "\n";
            }
            std::cout << std::string(40, '-') << "\n";
            
            int opcionPais;
            std::cout << "\nSelecciona el numero del pais: ";
            std::cin >> opcionPais;
            
            if (opcionPais < 1 || opcionPais > (int)paises.size()) {
                std::cout << "\n[X] Opcion invalida.\n";
                pausar();
                continue;
            }
            
            std::string pais = paises[opcionPais - 1];
            
            auto ventasFiltradas = registro.filtrarPorPais(pais);
            std::cout << "\n+============================================================+\n";
            std::cout << "|              VENTAS FILTRADAS POR PAIS                     |\n";
            std::cout << "+============================================================+\n";
            registro.mostrarTablaFiltrada(ventasFiltradas);
            pausar();
        }
        else if (opc == 2) {
            // Mostrar categorías disponibles
            auto categorias = registro.obtenerCategoriasUnicas();
            std::cout << "\nCategorias disponibles:\n";
            std::cout << std::string(40, '-') << "\n";
            for (size_t i = 0; i < categorias.size(); i++) {
                std::cout << "  [" << (i+1) << "] " << categorias[i] << "\n";
            }
            std::cout << std::string(40, '-') << "\n";
            
            int opcionCategoria;
            std::cout << "\nSelecciona el numero de la categoria: ";
            std::cin >> opcionCategoria;
            
            if (opcionCategoria < 1 || opcionCategoria > (int)categorias.size()) {
                std::cout << "\n[X] Opcion invalida.\n";
                pausar();
                continue;
            }
            
            std::string categoria = categorias[opcionCategoria - 1];
            
            auto ventasFiltradas = registro.filtrarPorCategoria(categoria);
            std::cout << "\n+============================================================+\n";
            std::cout << "|           VENTAS FILTRADAS POR CATEGORIA                   |\n";
            std::cout << "+============================================================+\n";
            registro.mostrarTablaFiltrada(ventasFiltradas);
            pausar();
        }
        else if (opc == 3) {
            std::string fechaInicio, fechaFin;
            std::cout << "\nIngresa fecha inicio (YYYY-MM-DD): ";
            std::cin >> fechaInicio;
            std::cout << "Ingresa fecha fin (YYYY-MM-DD): ";
            std::cin >> fechaFin;
            
            auto ventasFiltradas = registro.filtrarPorRangoFechas(fechaInicio, fechaFin);
            std::cout << "\n+============================================================+\n";
            std::cout << "|           VENTAS FILTRADAS POR FECHAS                      |\n";
            std::cout << "+============================================================+\n";
            std::cout << "Rango: " << fechaInicio << " a " << fechaFin << "\n";
            registro.mostrarTablaFiltrada(ventasFiltradas);
            pausar();
        }

    } while (opc != 0);
}

void SistemaCodex::menuEstadisticas() {
    int opc;
    do {
        limpiarPantalla();
        std::cout << "\n";
        std::cout << "+============================================================+\n";
        std::cout << "|                MENU DE ESTADISTICAS                        |\n";
        std::cout << "+============================================================+\n";
        std::cout << "\n";
        std::cout << "  [1] Estadisticas por pais especifico\n";
        std::cout << "  [2] Estadisticas de todos los paises\n";
        std::cout << "  [0] Volver al menu principal\n";
        std::cout << "\n";
        std::cout << "  Opcion: ";
        std::cin >> opc;

        limpiarPantalla();

        if (opc == 1) {
            // Mostrar países disponibles
            auto paises = registro.obtenerPaisesUnicos();
            std::cout << "\nPaises disponibles:\n";
            std::cout << std::string(40, '-') << "\n";
            for (size_t i = 0; i < paises.size(); i++) {
                std::cout << "  [" << (i+1) << "] " << paises[i] << "\n";
            }
            std::cout << std::string(40, '-') << "\n";
            
            int opcionPais;
            std::cout << "\nSelecciona el numero del pais: ";
            std::cin >> opcionPais;
            
            if (opcionPais < 1 || opcionPais > (int)paises.size()) {
                std::cout << "\n[X] Opcion invalida.\n";
                pausar();
                continue;
            }
            
            std::string pais = paises[opcionPais - 1];
            
            registro.mostrarEstadisticasPorPais(pais);
            pausar();
        }
        else if (opc == 2) {
            registro.mostrarEstadisticasTodosPaises();
            pausar();
        }

    } while (opc != 0);
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
        std::cout << "  [6] Filtros (Pais, Categoria, Fechas)\n";
        std::cout << "  [7] Estadisticas por paises\n";
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
        else if (opc == 6) {
            menuFiltros();
        }
        else if (opc == 7) {
            menuEstadisticas();
        }

    } while (opc != 0);

    std::cout << "\nSaliendo de Codex Product Platform...\n";
}