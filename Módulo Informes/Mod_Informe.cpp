#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std; // Usar el espacio de nombres std

// Estructura para almacenar los datos de una transacción
struct Transaccion {
    string fecha;
    string tipo;
    double monto;
    string cuentaOrigen;
    string cuentaDestino;
};

// Función para leer datos de transacciones desde un archivo de texto
vector<Transaccion> leerTransacDesdeArch(const string& ArchivoTransacciones) {
    vector<Transaccion> transacciones;
    ifstream archivo(ArchivoTransacciones);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Transaccion transaccion;
            ss >> transaccion.fecha >> transaccion.tipo >> transaccion.monto >> transaccion.cuentaOrigen >> transaccion.cuentaDestino;
            transacciones.push_back(transaccion);
        }
        archivo.close();
    }
    return transacciones;
}

// Función para generar un informe básico de transacciones
void InformeDeTransacciones(const vector<Transaccion>& transacciones) {
    for (const auto& transaccion : transacciones) 
    {
        cout << transaccion.fecha << "\t" << transaccion.tipo << "\t" << transaccion.monto << "\t" << transaccion.cuentaOrigen << "\t" << transaccion.cuentaDestino << endl;
    }
}

int main() {
    // Leer datos de transacciones desde un archivo de texto
    string ArchivoTransacciones = "datos_transaccion.txt"; // Nombre del archivo con los datos de transacciones
    vector<Transaccion> todasLasTransacciones = leerTransacDesdeArch(ArchivoTransacciones);

    // Generar un informe  de transacciones
    InformeDeTransacciones(todasLasTransacciones);

    return 0;
}
