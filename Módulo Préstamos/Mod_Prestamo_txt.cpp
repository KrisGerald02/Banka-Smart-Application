#include <iostream>
#include <math.h> // Para pow
#include <stdio.h> // Para FILE y funciones relacionadas
#include <stdlib.h> // Para NULL

using namespace std;

double saldoPrestamo = 0.0;
double tasaInteresAnual = 0.05; // Tasa de interes anual del 5%
int plazoMeses = 0;
double saldoInicial = 0.0;

void escribirEnArchivo(const char* mensaje) {
    FILE* archivo = fopen("transacciones.txt", "a");
    if (archivo == NULL) {
        printf("\nNo se pudo abrir/crear el archivo.");
        return;
    }
    fprintf(archivo, "%s", mensaje);
    fclose(archivo);
}

void escribirResumen(double saldoInicial, double montoPago, double saldoActualizado) {
    FILE* archivo = fopen("resumen_prestamo.txt", "a");
    if (archivo == NULL) {
        printf("\nNo se pudo abrir/crear el archivo.");
        return;
    }
    fprintf(archivo, "%-15s%-15s%-20s\n", "Saldo Inicial", "Monto del Pago", "Saldo Actualizado");
    fprintf(archivo, "%-15.2f%-15.2f%-20.2f\n", saldoInicial, montoPago, saldoActualizado);
    fclose(archivo);

    // También mostrar en la terminal
    cout << "\n--- Resumen del Prestamo ---\n";
    cout << "Saldo Inicial: " << saldoInicial << "\n";
    cout << "Monto del Pago: " << montoPago << "\n";
    cout << "Saldo Actualizado: " << saldoActualizado << "\n";
}

double calcularPagoMensual(double montoPrestamo, double tasaInteresAnual, int plazoMeses) {
    double tasaInteresMensual = tasaInteresAnual / 12.0;
    return (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -plazoMeses));
}

void solicitarPrestamo(double &saldoPrestamo, double monto, double tasaInteresAnual, int plazoMeses) {
    saldoPrestamo = monto;
    saldoInicial = monto;
    cout << "Has solicitado un prestamo de $" << monto << ".\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Has solicitado un prestamo de $%.2f.\n", monto);
    escribirEnArchivo(buffer);
    
    double pagoMensual = calcularPagoMensual(monto, tasaInteresAnual, plazoMeses);
    cout << "El pago mensual sera de $" << pagoMensual << " durante " << plazoMeses << " meses.\n";
    snprintf(buffer, sizeof(buffer), "El pago mensual sera de $%.2f durante %d meses.\n", pagoMensual, plazoMeses);
    escribirEnArchivo(buffer);
}

void consultarSaldoPrestamo(double saldoPrestamo) {
    cout << "Saldo actual del prestamo: $" << saldoPrestamo << ".\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Saldo actual del prestamo: $%.2f.\n", saldoPrestamo);
    escribirEnArchivo(buffer);
}

void realizarPagoPrestamo(double &saldoPrestamo, double cantidad) {
    if (cantidad > 0 && cantidad <= saldoPrestamo) {
        double saldoAnterior = saldoPrestamo;
        saldoPrestamo -= cantidad;
        cout << "Has realizado un pago de $" << cantidad << " del prestamo.\n";
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Has realizado un pago de $%.2f del prestamo.\n", cantidad);
        escribirEnArchivo(buffer);
        escribirResumen(saldoAnterior, cantidad, saldoPrestamo);
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Saldo Insuficiente.\n");
    }
}

void limpiarPantalla() {
    system("cls");
}

void mostrarMenu() {
    cout << "\n--- Menu de Prestamos del Banco ---\n";
    cout << "1. Solicitar prestamo\n";
    cout << "2. Consultar saldo del prestamo\n";
    cout << "3. Realizar pago del prestamo\n";
    cout << "4. Generar resumen del prestamo\n";
    cout << "5. Salir\n";
    cout << "Elige una opcion: ";
}

bool verificarRequisitos(double salario, int edad) {
    bool requisitosCumplidos = true;
    if (salario < 15000) {
        cout << "Salario insuficiente. Debes tener un salario minimo de C$15000.\n";
        escribirEnArchivo("Salario insuficiente. Debes tener un salario minimo de C$15000.\n");
        requisitosCumplidos = false;
    }
    if (edad <= 21) {
        cout << "Debes tener mas de 21 anos para solicitar un prestamo.\n";
        escribirEnArchivo("Debes tener mas de 21 anos para solicitar un prestamo.\n");
        requisitosCumplidos = false;
    }
    return requisitosCumplidos;
}

int main() {
    int opcion;
    double cantidad;
    double monto;
    int plazo;
    double salario;
    int edad;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Introduce tu salario: ";
                cin >> salario;
                cout << "Introduce tu edad: ";
                cin >> edad;
                if (verificarRequisitos(salario, edad)) {
                    cout << "Introduce el monto del prestamo: ";
                    cin >> monto;
                    cout << "Introduce el plazo en meses: ";
                    cin >> plazo;
                    solicitarPrestamo(saldoPrestamo, monto, tasaInteresAnual, plazo);
                    plazoMeses = plazo;
                }
                break;
            case 2:
                consultarSaldoPrestamo(saldoPrestamo);
                break;
            case 3:
                cout << "Introduce la cantidad a pagar del prestamo: ";
                cin >> cantidad;
                realizarPagoPrestamo(saldoPrestamo, cantidad);
                break;
            case 4:
                if (saldoInicial > 0) {
                    escribirResumen(saldoInicial, 0, saldoPrestamo);
                    cout << "Resumen del prestamo generado en 'resumen_prestamo.txt'.\n";
                } else {
                    cout << "No hay prestamos realizados para generar un resumen.\n";
                }
                break;
            case 5:
                cout << "Saliendo...\n";
                escribirEnArchivo("Saliendo...\n");
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
                escribirEnArchivo("Opcion invalida. Intenta de nuevo.\n");
        }

        if (opcion != 5) {
            cout << "Presiona Enter para continuar...";
            cin.ignore(); // Ignora el salto de línea previo
            cin.get(); // Espera a que el usuario presione Enter
            limpiarPantalla();
        }

    } while (opcion != 5);

    return 0;
}
