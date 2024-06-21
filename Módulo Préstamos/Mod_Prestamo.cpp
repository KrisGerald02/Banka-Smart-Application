#include <iostream>
#include <cmath> // Para pow

using namespace std;

double saldoPrestamo = 0.0;
double tasaInteresAnual = 0.05; // Tasa de interes anual del 5%
int plazoMeses = 0;

// Función para calcular el pago mensual del prestamo
double calcularPagoMensual(double montoPrestamo, double tasaInteresAnual, int plazoMeses) {
    double tasaInteresMensual = tasaInteresAnual / 12.0;
    return (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -plazoMeses));
}

void solicitarPrestamo(double &saldoPrestamo, double monto, double tasaInteresAnual, int plazoMeses) {
    saldoPrestamo = monto;
    cout << "Has solicitado un prestamo de $" << monto << ".\n";
    double pagoMensual = calcularPagoMensual(monto, tasaInteresAnual, plazoMeses);
    cout << "El pago mensual sera de $" << pagoMensual << " durante " << plazoMeses << " meses.\n";
}

void consultarSaldoPrestamo(double saldoPrestamo) {
    cout << "Saldo actual del prestamo: $" << saldoPrestamo << ".\n";
}

void realizarPagoPrestamo(double &saldoPrestamo, double cantidad) {
    if (cantidad > 0 && cantidad <= saldoPrestamo) {
        saldoPrestamo -= cantidad;
        cout << "Has realizado un pago de $" << cantidad << " del prestamo.\n";
    } else {
        cout << "Saldo Insuficiente.\n";
    }
}

void mostrarMenu() {
    cout << "\n--- Menu de Prestamos del Banco ---\n";
    cout << "1. Solicitar prestamo\n";
    cout << "2. Consultar saldo del prestamo\n";
    cout << "3. Realizar pago del prestamo\n";
    cout << "4. Salir\n";
    cout << "Elige una opcion: ";
}

//Para los requisitos falta añadir el saldo crediticio minimo, considerar historial de pagos de tarjeta de credito
//Si es q existe el historial si no continuar
//No se aceptan clientes con pagos atrasados (mora)
bool verificarRequisitos(double salario, int edad) {
    if (salario >= 15000 && edad > 21) {
        return true;
    } else {
        if (salario < 15000) {
            cout << "Salario insuficiente. Debes tener un salario minimo de C$15000.\n";
        }
        if (edad <= 21) {
            cout << "Debes tener mas de 21 anos para solicitar un prestamo.\n";
        }
        return false;
    }
}

int main() {
    //Identificadores
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
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}

