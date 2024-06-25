#include <iostream>

using namespace std;

double saldoCuenta1 = 0.0;
double saldoCuenta2 = 0.0;
double deudaTarjetaCredito = 0.0;

void depositar(double &saldo, double cantidad) {
    if (cantidad > 0) {
        saldo += cantidad;
        cout << "Has depositado $" << cantidad << ".\n";
    } else {
        cout << "Cantidad invalida.\n";
    }
}

void retirar(double &saldo, double cantidad) {
    if (cantidad > 0 && cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Has retirado $" << cantidad << ".\n";
    } else {
        cout << "Saldo Insuficiente.\n";
    }
}

void consultarSaldo(double saldo, int cuenta) {
    cout << "Saldo actual de la cuenta " << cuenta << ": $" << saldo << ".\n";
}

void transferir(double &saldoOrigen, double &saldoDestino, double cantidad) {
    if (cantidad > 0 && cantidad <= saldoOrigen) {
        saldoOrigen -= cantidad;
        saldoDestino += cantidad;
        cout << "Has transferido $" << cantidad << " de la cuenta origen a la cuenta destino.\n";
    } else {
        cout << "Saldo Insuficiente en la Cuenta Origen.\n";
    }
}

void transferirOtroBanco(double &saldoOrigen, double cantidad) {
    double comision = 0.10 * cantidad;
    double total = cantidad + comision;
    if (total > 0 && total <= saldoOrigen) {
        saldoOrigen -= total;
        cout << "Has transferido $" << cantidad << " a otro banco con una comisión de $" << comision << ".\n";
        cout << "Total deducido de tu cuenta: $" << total << ".\n";
    } else {
        cout << "Saldo Insuficiente en la Cuenta Origen.\n";
    }
}

void pagarServicio(double &saldo, const string &servicio, double cantidad) {
    if (cantidad > 0 && cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Has pagado $" << cantidad << " por el servicio de " << servicio << ".\n";
    } else {
        cout << "Saldo Insuficiente.\n";
    }
}

void pagarTarjetaCredito(double &saldo, double cantidad) {
    if (cantidad > 0 && cantidad <= saldo) {
        saldo -= cantidad;
        deudaTarjetaCredito -= cantidad;
        cout << "Has pagado $" << cantidad << " de tu Tarjeta de Credito.\n";
    } else {
        cout << "Saldo Insuficiente.\n";
    }
}

void mostrarMenu() {
    cout << "\n--- Menu de Banka Smart Aplication ---\n";
    cout << "1. Depositar dinero en Cuenta 1\n";
    cout << "2. Retirar dinero de Cuenta 1\n";
    cout << "3. Consultar saldo de Cuenta 1\n";
    cout << "4. Depositar dinero en Cuenta 2\n";
    cout << "5. Retirar dinero de Cuenta 2\n";
    cout << "6. Consultar saldo de Cuenta 2\n";
    cout << "7. Transferir dinero entre cuentas\n";
    cout << "8. Transferir dinero a otro banco\n";
    cout << "9. Pagar servicios basicos\n";
    cout << "10. Pagar tarjeta de credito\n";
    cout << "11. Salir\n";
    cout << "Elige una opcion: ";
}

void mostrarMenuServicios() {
    cout << "\n--- Pago de Servicios Basicos ---\n";
    cout << "1. Pagar Luz\n";
    cout << "2. Pagar Agua\n";
    cout << "3. Pagar Internet\n";
    cout << "Elige una opcion: ";
}

int main() {
    int opcion, opcionServicio;
    double cantidad;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Introduce la cantidad a depositar en Cuenta 1: ";
                cin >> cantidad;
                depositar(saldoCuenta1, cantidad);
                break;
            case 2:
                cout << "Introduce la cantidad a retirar de Cuenta 1: ";
                cin >> cantidad;
                retirar(saldoCuenta1, cantidad);
                break;
            case 3:
                consultarSaldo(saldoCuenta1, 1);
                break;
            case 4:
                cout << "Introduce la cantidad a depositar en Cuenta 2: ";
                cin >> cantidad;
                depositar(saldoCuenta2, cantidad);
                break;
            case 5:
                cout << "Introduce la cantidad a retirar de Cuenta 2: ";
                cin >> cantidad;
                retirar(saldoCuenta2, cantidad);
                break;
            case 6:
                consultarSaldo(saldoCuenta2, 2);
                break;
            case 7:
                cout << "Introduce la cantidad a transferir de Cuenta 1 a Cuenta 2: ";
                cin >> cantidad;
                transferir(saldoCuenta1, saldoCuenta2, cantidad);
                break;
            case 8:
                cout << "Introduce la cantidad a transferir a otro banco: ";
                cin >> cantidad;
                transferirOtroBanco(saldoCuenta1, cantidad);
                break;
            case 9:
                mostrarMenuServicios();
                cin >> opcionServicio;
                cout << "Introduce la cantidad a pagar: ";
                cin >> cantidad;
                switch (opcionServicio) {
                    case 1:
                        pagarServicio(saldoCuenta1, "Luz", cantidad);
                        break;
                    case 2:
                        pagarServicio(saldoCuenta1, "Agua", cantidad);
                        break;
                    case 3:
                        pagarServicio(saldoCuenta1, "Internet", cantidad);
                        break;
                    default:
                        cout << "Opcion de servicio invalida.\n";
                }
                break;
            case 10:
                cout << "Introduce la cantidad a pagar en tu tarjeta de credito: ";
                cin >> cantidad;
                pagarTarjetaCredito(saldoCuenta1, cantidad);
                break;
            case 11:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    } while (opcion != 11);

    return 0;
}
