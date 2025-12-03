#include "RegistroVentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <cmath>

bool RegistroVentas::cargarCSV(const std::string& nombreArchivo) {
    ventas.clear();

    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir archivo CSV.\n";
        return false;
    }

    std::string linea;
    getline(file, linea); // saltar encabezados

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string idVenta, fecha, montoStr, cantStr, categoria, metodoPago,
                    clienteID, pais, costoStr, descStr, impStr, subStr,
                    totalDescStr, totalImpStr, totalFinStr;

        getline(ss, idVenta, ',');
        getline(ss, fecha, ',');
        getline(ss, montoStr, ',');
        getline(ss, cantStr, ',');
        getline(ss, categoria, ',');
        getline(ss, metodoPago, ',');
        getline(ss, clienteID, ',');
        getline(ss, pais, ',');
        getline(ss, costoStr, ',');
        getline(ss, descStr, ',');
        getline(ss, impStr, ',');
        getline(ss, subStr, ',');
        getline(ss, totalDescStr, ',');
        getline(ss, totalImpStr, ',');
        getline(ss, totalFinStr, ',');

        double monto = std::stod(montoStr);
        int cantidad = std::stoi(cantStr);
        double costo = std::stod(costoStr);
        double desc = std::stod(descStr);
        double imp = std::stod(impStr);
        double sub = std::stod(subStr);
        double totalDesc = std::stod(totalDescStr);
        double totalImp = std::stod(totalImpStr);
        double totalFin = std::stod(totalFinStr);

        Venta v(idVenta, fecha, monto, cantidad, categoria, metodoPago,
                clienteID, pais, costo, desc, imp, sub, totalDesc,
                totalImp, totalFin);
        ventas.push_back(v);
    }

    file.close();
    return true;
}

double RegistroVentas::ventasTotales() const {
    double total = 0;
    for (const auto& v : ventas) total += v.totalFinal;
    return total;
}

Venta RegistroVentas::ventaMaxima() const {
    if (ventas.empty()) return Venta();

    const Venta* maxVenta = &ventas[0];
    for (const auto& v : ventas)
        if (v.totalFinal > maxVenta->totalFinal)
            maxVenta = &v;

    return *maxVenta;
}

void RegistroVentas::mostrarTodas() const {
    for (const auto& v : ventas) {
        std::cout << "ID: " << v.idVenta
                  << " | Fecha: " << v.fecha
                  << " | Categoria: " << v.categoria
                  << " | Total: " << v.totalFinal << "\n";
    }
}

void RegistroVentas::mostrarTabla() const {
    std::cout << "\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(13) << "Fecha"
              << std::setw(16) << "Categoria"
              << std::setw(16) << "Pais"
              << std::setw(10) << "Cantidad"
              << std::setw(14) << "Total"
              << "\n";
    std::cout << std::string(77, '-') << "\n";

    for (const auto& v : ventas) {
        std::cout << std::left
                  << std::setw(8) << v.idVenta
                  << std::setw(13) << v.fecha.substr(0, 10)
                  << std::setw(16) << v.categoria
                  << std::setw(16) << v.pais
                  << std::setw(10) << v.cantidad
                  << "$" << std::fixed << std::setprecision(2) << v.totalFinal
                  << "\n";
    }
    std::cout << std::string(77, '-') << "\n";
}

void RegistroVentas::mostrarDetalleVenta(const Venta& v) const {
    std::cout << "\n+============================================================+\n";
    std::cout << "|                   DETALLE DE VENTA                         |\n";
    std::cout << "+============================================================+\n\n";
    
    std::cout << std::left << std::setw(25) << "ID:" << v.idVenta << "\n";
    std::cout << std::left << std::setw(25) << "Fecha:" << v.fecha << "\n";
    std::cout << std::left << std::setw(25) << "Categoria:" << v.categoria << "\n";
    std::cout << std::left << std::setw(25) << "Metodo de pago:" << v.metodoPago << "\n";
    std::cout << std::left << std::setw(25) << "Cliente ID:" << v.clienteID << "\n";
    std::cout << std::left << std::setw(25) << "Pais:" << v.pais << "\n";
    
    std::cout << std::string(60, '-') << "\n";
    
    std::cout << std::left << std::setw(25) << "Monto unitario:" 
              << "$" << std::fixed << std::setprecision(2) << v.montoUnit << "\n";
    std::cout << std::left << std::setw(25) << "Cantidad:" << v.cantidad << "\n";
    std::cout << std::left << std::setw(25) << "Subtotal:" 
              << "$" << v.subtotal << "\n";
    std::cout << std::left << std::setw(25) << "Costo envio:" 
              << "$" << v.costoEnvio << "\n";
    std::cout << std::left << std::setw(25) << "Descuento:" 
              << "$" << v.descuento << "\n";
    std::cout << std::left << std::setw(25) << "Impuesto:" 
              << "$" << v.impuesto << "\n";
    
    std::cout << std::string(60, '=') << "\n";
    
    std::cout << std::left << std::setw(25) << "TOTAL FINAL:" 
              << "$" << v.totalFinal << "\n\n";
}

Venta* RegistroVentas::buscarVenta(const std::string& id) {
    for (auto& v : ventas) {
        if (v.idVenta == id)
            return &v;
    }
    return nullptr;
}

// ==================== NUEVAS FUNCIONALIDADES ====================

std::vector<Venta> RegistroVentas::filtrarPorPais(const std::string& pais) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.pais == pais) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

std::vector<Venta> RegistroVentas::filtrarPorCategoria(const std::string& categoria) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.categoria == categoria) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

std::vector<Venta> RegistroVentas::filtrarPorRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) const {
    std::vector<Venta> resultado;
    for (const auto& v : ventas) {
        if (v.fecha >= fechaInicio && v.fecha <= fechaFin) {
            resultado.push_back(v);
        }
    }
    return resultado;
}

EstadisticasPais RegistroVentas::calcularEstadisticasPais(const std::string& pais) const {
    EstadisticasPais stats;
    stats.nombrePais = pais;
    stats.total = 0;
    stats.cantidad = 0;
    stats.maximo = 0;
    stats.minimo = 999999999;
    
    for (const auto& v : ventas) {
        if (v.pais == pais) {
            stats.total += v.totalFinal;
            stats.cantidad++;
            
            if (v.totalFinal > stats.maximo) {
                stats.maximo = v.totalFinal;
            }
            if (v.totalFinal < stats.minimo) {
                stats.minimo = v.totalFinal;
            }
        }
    }
    
    if (stats.cantidad > 0) {
        stats.promedio = stats.total / stats.cantidad;
    } else {
        stats.promedio = 0;
        stats.minimo = 0;
    }
    
    return stats;
}

std::map<std::string, EstadisticasPais> RegistroVentas::calcularEstadisticasTodosPaises() const {
    std::map<std::string, EstadisticasPais> estadisticas;
    
    std::set<std::string> paises;
    for (const auto& v : ventas) {
        paises.insert(v.pais);
    }
    
    for (const auto& pais : paises) {
        estadisticas[pais] = calcularEstadisticasPais(pais);
    }
    
    return estadisticas;
}

void RegistroVentas::mostrarTablaFiltrada(const std::vector<Venta>& ventasFiltradas) const {
    if (ventasFiltradas.empty()) {
        std::cout << "\n[!] No se encontraron ventas con los criterios especificados.\n";
        return;
    }
    
    std::cout << "\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(13) << "Fecha"
              << std::setw(16) << "Categoria"
              << std::setw(16) << "Pais"
              << std::setw(10) << "Cantidad"
              << std::setw(14) << "Total"
              << "\n";
    std::cout << std::string(77, '-') << "\n";

    for (const auto& v : ventasFiltradas) {
        std::cout << std::left
                  << std::setw(8) << v.idVenta
                  << std::setw(13) << v.fecha.substr(0, 10)
                  << std::setw(16) << v.categoria
                  << std::setw(16) << v.pais
                  << std::setw(10) << v.cantidad
                  << "$" << std::fixed << std::setprecision(2) << v.totalFinal
                  << "\n";
    }
    std::cout << std::string(77, '-') << "\n";
    std::cout << "Total de ventas encontradas: " << ventasFiltradas.size() << "\n";
}

void RegistroVentas::mostrarEstadisticasPorPais(const std::string& pais) const {
    EstadisticasPais stats = calcularEstadisticasPais(pais);
    
    if (stats.cantidad == 0) {
        std::cout << "\n[!] No hay ventas registradas para el pais: " << pais << "\n";
        return;
    }
    
    std::cout << "\n+============================================================+\n";
    std::cout << "|              ESTADISTICAS POR PAIS: " << std::left << std::setw(19) << pais << "|\n";
    std::cout << "+============================================================+\n\n";
    
    std::cout << std::left << std::setw(25) << "Pais:" << stats.nombrePais << "\n";
    std::cout << std::left << std::setw(25) << "Cantidad de ventas:" << stats.cantidad << "\n";
    std::cout << std::left << std::setw(25) << "Total vendido:" 
              << "$" << std::fixed << std::setprecision(2) << stats.total << "\n";
    std::cout << std::left << std::setw(25) << "Promedio por venta:" 
              << "$" << stats.promedio << "\n";
    std::cout << std::left << std::setw(25) << "Venta maxima:" 
              << "$" << stats.maximo << "\n";
    std::cout << std::left << std::setw(25) << "Venta minima:" 
              << "$" << stats.minimo << "\n\n";
}

void RegistroVentas::mostrarEstadisticasTodosPaises() const {
    auto estadisticas = calcularEstadisticasTodosPaises();
    
    std::cout << "\n+=======================================================================================+\n";
    std::cout << "|                         ESTADISTICAS POR TODOS LOS PAISES                            |\n";
    std::cout << "+=======================================================================================+\n\n";
    
    std::cout << std::left
              << std::setw(18) << "Pais"
              << std::setw(10) << "Ventas"
              << std::setw(15) << "Total"
              << std::setw(15) << "Promedio"
              << std::setw(15) << "Maximo"
              << std::setw(15) << "Minimo"
              << "\n";
    std::cout << std::string(88, '-') << "\n";
    
    for (const auto& pair : estadisticas) {
        const EstadisticasPais& stats = pair.second;
        std::cout << std::left
                  << std::setw(18) << stats.nombrePais
                  << std::setw(10) << stats.cantidad
                  << "$" << std::setw(14) << std::fixed << std::setprecision(2) << stats.total
                  << "$" << std::setw(14) << stats.promedio
                  << "$" << std::setw(14) << stats.maximo
                  << "$" << std::setw(14) << stats.minimo
                  << "\n";
    }
    std::cout << std::string(88, '-') << "\n";
}

std::vector<std::string> RegistroVentas::obtenerPaisesUnicos() const {
    std::set<std::string> paisesSet;
    for (const auto& v : ventas) {
        paisesSet.insert(v.pais);
    }
    return std::vector<std::string>(paisesSet.begin(), paisesSet.end());
}

std::vector<std::string> RegistroVentas::obtenerCategoriasUnicas() const {
    std::set<std::string> categoriasSet;
    for (const auto& v : ventas) {
        categoriasSet.insert(v.categoria);
    }
    return std::vector<std::string>(categoriasSet.begin(), categoriasSet.end());
}

// ==================== DASHBOARD CON GRAFICOS ASCII ====================

std::map<std::string, int> RegistroVentas::obtenerVentasPorCategoria() const {
    std::map<std::string, int> resultado;
    for (const auto& v : ventas) {
        resultado[v.categoria]++;
    }
    return resultado;
}

std::map<std::string, double> RegistroVentas::obtenerTotalesPorPais() const {
    std::map<std::string, double> resultado;
    for (const auto& v : ventas) {
        resultado[v.pais] += v.totalFinal;
    }
    return resultado;
}

std::map<std::string, int> RegistroVentas::obtenerVentasPorMes() const {
    std::map<std::string, int> resultado;
    for (const auto& v : ventas) {
        // Extraer mes (formato YYYY-MM-DD)
        if (v.fecha.length() >= 7) {
            std::string mes = v.fecha.substr(5, 2);
            std::string nombreMes;
            
            if (mes == "01") nombreMes = "Enero";
            else if (mes == "02") nombreMes = "Febrero";
            else if (mes == "03") nombreMes = "Marzo";
            else if (mes == "04") nombreMes = "Abril";
            else if (mes == "05") nombreMes = "Mayo";
            else if (mes == "06") nombreMes = "Junio";
            else if (mes == "07") nombreMes = "Julio";
            else if (mes == "08") nombreMes = "Agosto";
            else if (mes == "09") nombreMes = "Septiembre";
            else if (mes == "10") nombreMes = "Octubre";
            else if (mes == "11") nombreMes = "Noviembre";
            else if (mes == "12") nombreMes = "Diciembre";
            
            resultado[nombreMes]++;
        }
    }
    return resultado;
}

void RegistroVentas::mostrarGraficoBarrasHorizontal(const std::map<std::string, double>& datos, const std::string& titulo, int anchoMax) const {
    if (datos.empty()) {
        std::cout << "[!] No hay datos para mostrar.\n";
        return;
    }
    
    // Encontrar el valor máximo
    double maxValor = 0;
    for (const auto& pair : datos) {
        if (pair.second > maxValor) {
            maxValor = pair.second;
        }
    }
    
    std::cout << "\n" << titulo << "\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    for (const auto& pair : datos) {
        std::string etiqueta = pair.first;
        double valor = pair.second;
        
        // Calcular longitud de la barra
        int longitudBarra = (int)((valor / maxValor) * anchoMax);
        
        // Mostrar etiqueta (ajustada a 15 caracteres)
        std::cout << std::left << std::setw(15) << etiqueta.substr(0, 14) << " | ";
        
        // Mostrar barra
        for (int i = 0; i < longitudBarra; i++) {
            std::cout << "=";
        }
        
        // Mostrar valor
        std::cout << " " << std::fixed << std::setprecision(0) << valor << "\n";
    }
    
    std::cout << "\n" << std::string(80, '=') << "\n";
}

void RegistroVentas::mostrarDashboard() const {
    std::cout << "\n";
    std::cout << "+==============================================================================+\n";
    std::cout << "|                           DASHBOARD INTERACTIVO                              |\n";
    std::cout << "+==============================================================================+\n";
    
    // Estadísticas generales
    double totalVentas = ventasTotales();
    int numVentas = ventas.size();
    double promedioVenta = numVentas > 0 ? totalVentas / numVentas : 0;
    
    std::cout << "\n[RESUMEN GENERAL]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  Total de ventas:      " << numVentas << "\n";
    std::cout << "  Ingresos totales:     $" << std::fixed << std::setprecision(2) << totalVentas << "\n";
    std::cout << "  Promedio por venta:   $" << promedioVenta << "\n";
    
    auto ventaMax = ventaMaxima();
    std::cout << "  Venta mas grande:     $" << ventaMax.totalFinal << " (ID: " << ventaMax.idVenta << ")\n";
    
    // Gráfico de ventas por país
    auto totalesPorPais = obtenerTotalesPorPais();
    mostrarGraficoBarrasHorizontal(totalesPorPais, "[INGRESOS POR PAIS]", 40);
    
    // Gráfico de cantidad de ventas por categoría
    auto ventasPorCat = obtenerVentasPorCategoria();
    std::map<std::string, double> catMap;
    for (const auto& pair : ventasPorCat) {
        catMap[pair.first] = pair.second;
    }
    mostrarGraficoBarrasHorizontal(catMap, "[CANTIDAD DE VENTAS POR CATEGORIA]", 40);
    
    // Gráfico de ventas por mes
    auto ventasPorMes = obtenerVentasPorMes();
    std::map<std::string, double> mesMap;
    for (const auto& pair : ventasPorMes) {
        mesMap[pair.first] = pair.second;
    }
    mostrarGraficoBarrasHorizontal(mesMap, "[DISTRIBUCION DE VENTAS POR MES]", 40);
    
    // Top 5 países por ingresos
    std::cout << "\n[TOP 5 PAISES POR INGRESOS]\n";
    std::cout << std::string(80, '-') << "\n";
    
    std::vector<std::pair<std::string, double>> paisesOrdenados(totalesPorPais.begin(), totalesPorPais.end());
    std::sort(paisesOrdenados.begin(), paisesOrdenados.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    int count = 0;
    for (const auto& pair : paisesOrdenados) {
        if (count >= 5) break;
        std::cout << "  " << (count + 1) << ". " << std::left << std::setw(15) << pair.first 
                  << " $" << std::fixed << std::setprecision(2) << pair.second << "\n";
        count++;
    }
    
    std::cout << "\n+==============================================================================+\n";
}

// ==================== SISTEMA DE ALERTAS INTELIGENTE ====================

std::vector<std::string> RegistroVentas::detectarPaisesBajoRendimiento() const {
    std::vector<std::string> paisesProblema;
    auto totalesPorPais = obtenerTotalesPorPais();
    
    if (totalesPorPais.empty()) return paisesProblema;
    
    // Calcular promedio de ingresos por país
    double totalGeneral = 0;
    for (const auto& pair : totalesPorPais) {
        totalGeneral += pair.second;
    }
    double promedioGeneral = totalGeneral / totalesPorPais.size();
    
    // Detectar países que están 30% por debajo del promedio
    double umbral = promedioGeneral * 0.7;
    
    for (const auto& pair : totalesPorPais) {
        if (pair.second < umbral) {
            paisesProblema.push_back(pair.first);
        }
    }
    
    return paisesProblema;
}

std::vector<std::string> RegistroVentas::detectarCategoriasPocoVendidas() const {
    std::vector<std::string> categoriasProblema;
    auto ventasPorCat = obtenerVentasPorCategoria();
    
    if (ventasPorCat.empty()) return categoriasProblema;
    
    // Calcular promedio de ventas por categoría
    int totalVentas = 0;
    for (const auto& pair : ventasPorCat) {
        totalVentas += pair.second;
    }
    double promedio = (double)totalVentas / ventasPorCat.size();
    
    // Detectar categorías con menos del 50% del promedio
    double umbral = promedio * 0.5;
    
    for (const auto& pair : ventasPorCat) {
        if (pair.second < umbral) {
            categoriasProblema.push_back(pair.first);
        }
    }
    
    return categoriasProblema;
}

std::vector<Venta> RegistroVentas::detectarVentasAtipicas() const {
    std::vector<Venta> ventasAtipicas;
    
    if (ventas.empty()) return ventasAtipicas;
    
    // Calcular promedio y desviación estándar
    double suma = 0;
    for (const auto& v : ventas) {
        suma += v.totalFinal;
    }
    double promedio = suma / ventas.size();
    
    double sumaCuadrados = 0;
    for (const auto& v : ventas) {
        double diff = v.totalFinal - promedio;
        sumaCuadrados += diff * diff;
    }
    double desviacion = std::sqrt(sumaCuadrados / ventas.size());
    
    // Detectar valores que estén más de 2 desviaciones estándar del promedio
    double limiteInferior = promedio - (2 * desviacion);
    double limiteSuperior = promedio + (2 * desviacion);
    
    for (const auto& v : ventas) {
        if (v.totalFinal < limiteInferior || v.totalFinal > limiteSuperior) {
            ventasAtipicas.push_back(v);
        }
    }
    
    return ventasAtipicas;
}

std::vector<Alerta> RegistroVentas::generarAlertas() const {
    std::vector<Alerta> alertas;
    
    // Alerta 1: Países con bajo rendimiento
    auto paisesBajos = detectarPaisesBajoRendimiento();
    if (!paisesBajos.empty()) {
        Alerta a;
        a.tipo = "BAJO RENDIMIENTO";
        a.nivel = "ADVERTENCIA";
        a.mensaje = "Paises con ingresos por debajo del promedio: ";
        for (size_t i = 0; i < paisesBajos.size(); i++) {
            a.mensaje += paisesBajos[i];
            if (i < paisesBajos.size() - 1) a.mensaje += ", ";
        }
        alertas.push_back(a);
    }
    
    // Alerta 2: Categorías poco vendidas
    auto catsBajas = detectarCategoriasPocoVendidas();
    if (!catsBajas.empty()) {
        Alerta a;
        a.tipo = "CATEGORIA POCO VENDIDA";
        a.nivel = "ADVERTENCIA";
        a.mensaje = "Categorias con pocas ventas: ";
        for (size_t i = 0; i < catsBajas.size(); i++) {
            a.mensaje += catsBajas[i];
            if (i < catsBajas.size() - 1) a.mensaje += ", ";
        }
        alertas.push_back(a);
    }
    
    // Alerta 3: Ventas atípicas
    auto ventasAtip = detectarVentasAtipicas();
    if (ventasAtip.size() > 0) {
        Alerta a;
        a.tipo = "VENTAS ATIPICAS";
        a.nivel = "INFO";
        a.mensaje = "Se detectaron " + std::to_string(ventasAtip.size()) + " ventas con valores atipicos (muy altos o muy bajos)";
        alertas.push_back(a);
    }
    
    // Alerta 4: Volumen total de ventas
    if (ventas.size() < 10) {
        Alerta a;
        a.tipo = "VOLUMEN BAJO";
        a.nivel = "CRITICO";
        a.mensaje = "Volumen de ventas muy bajo: solo " + std::to_string(ventas.size()) + " ventas registradas";
        alertas.push_back(a);
    } else if (ventas.size() > 100) {
        Alerta a;
        a.tipo = "VOLUMEN ALTO";
        a.nivel = "INFO";
        a.mensaje = "Excelente volumen de ventas: " + std::to_string(ventas.size()) + " ventas registradas";
        alertas.push_back(a);
    }
    
    // Alerta 5: País con más ingresos
    auto totalesPorPais = obtenerTotalesPorPais();
    if (!totalesPorPais.empty()) {
        std::string mejorPais;
        double maxIngreso = 0;
        for (const auto& pair : totalesPorPais) {
            if (pair.second > maxIngreso) {
                maxIngreso = pair.second;
                mejorPais = pair.first;
            }
        }
        
        Alerta a;
        a.tipo = "MEJOR MERCADO";
        a.nivel = "INFO";
        a.mensaje = "Mercado mas rentable: " + mejorPais + " con $" + std::to_string((int)maxIngreso);
        alertas.push_back(a);
    }
    
    return alertas;
}

void RegistroVentas::mostrarAlertas() const {
    auto alertas = generarAlertas();
    
    std::cout << "\n";
    std::cout << "+==============================================================================+\n";
    std::cout << "|                        SISTEMA DE ALERTAS INTELIGENTE                        |\n";
    std::cout << "+==============================================================================+\n\n";
    
    if (alertas.empty()) {
        std::cout << "[✓] No hay alertas. Todo funciona correctamente.\n\n";
        return;
    }
    
    std::cout << "Se detectaron " << alertas.size() << " alertas:\n\n";
    
    int numAlerta = 1;
    for (const auto& alerta : alertas) {
        std::cout << "[ALERTA #" << numAlerta << "]\n";
        std::cout << "Tipo:  " << alerta.tipo << "\n";
        
        // Color/símbolo según nivel
        if (alerta.nivel == "CRITICO") {
            std::cout << "Nivel: [!!!] CRITICO\n";
        } else if (alerta.nivel == "ADVERTENCIA") {
            std::cout << "Nivel: [!] ADVERTENCIA\n";
        } else {
            std::cout << "Nivel: [i] INFORMATIVO\n";
        }
        
        std::cout << "Msg:   " << alerta.mensaje << "\n";
        std::cout << std::string(80, '-') << "\n\n";
        numAlerta++;
    }
    
    std::cout << "+==============================================================================+\n";
}