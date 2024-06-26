#include <iostream>
#include <string>

using namespace std;

double saldoCuenta1 = 0.0;
double saldoCuenta2 = 0.0;
double deudaTarjetaCredito = 0.0;

struct TarjetaDeCredito {
    string numero;
    string titular;
    double limite_credito;
    double saldo;
    int pagos_a_tiempo;
    int puntos;
};

TarjetaDeCredito tarjeta;

// Función para crear una tarjeta de crédito
void crearTarjetaDeCredito(TarjetaDeCredito &tarjeta) {
    cout << "Ingrese el número de la tarjeta: ";
    cin >> tarjeta.numero;
    cout << "Ingrese el titular de la tarjeta: ";
    cin.ignore(); // Para ignorar el salto de línea previo
    getline(cin, tarjeta.titular);
    cout << "Ingrese el límite de crédito: ";
    cin >> tarjeta.limite_credito;
    tarjeta.saldo = 0;
    tarjeta.pagos_a_tiempo = 0;
    tarjeta.puntos = 0;
    cout << "Tarjeta de crédito creada exitosamente.\n";
}

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
        tarjeta.pagos_a_tiempo++;
        tarjeta.puntos += cantidad * 0.01; // Añade 1 punto por cada $100 pagados
        cout << "Has pagado $" << cantidad << " de tu Tarjeta de Credito.\n";
        cout << "Pagos a tiempo: " << tarjeta.pagos_a_tiempo << "\n";
        cout << "Puntos acumulados: " << tarjeta.puntos << "\n";
    } else {
        cout << "Saldo Insuficiente.\n";
    }
}

//Consultar Puntos Acumulados X Cada Pago realizado en la Tarjeta de Credito
void consultarPuntosTarjeta() {
    cout << "Puntos acumulados en la tarjeta: " << tarjeta.puntos << "\n";
    cout << "Pagos a tiempo realizados: " << tarjeta.pagos_a_tiempo << "\n";
}

//Mejorar Menu 
//1. Transaccion
// 1.1 Retiro
// 1.2 Transfernecias
///  1.2.1 Transferencias entre cuentas del mismo usuario
///  1.2.2 Transferencias a otras cuentas
///  1.2.3 Transferencias a Otros Bancos
void mostrarMenu() {
    cout << "\n--- Menu de Banka Smart Aplication ---\n";
    cout << "1. Crear tarjeta de crédito\n";
    cout << "2. Depositar dinero en Cuenta 1\n";
    cout << "3. Retirar dinero de Cuenta 1\n";
    cout << "4. Consultar saldo de Cuenta 1\n";
    cout << "5. Depositar dinero en Cuenta 2\n";
    cout << "6. Retirar dinero de Cuenta 2\n";
    cout << "7. Consultar saldo de Cuenta 2\n";
    cout << "8. Transferir dinero entre cuentas\n";
    cout << "9. Transferir dinero a otro banco\n";
    cout << "10. Pagar servicios basicos\n";
    cout << "11. Pagar tarjeta de crédito\n";
    cout << "12. Consultar puntos de la tarjeta de crédito\n";
    cout << "13. Salir\n";
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
                crearTarjetaDeCredito(tarjeta);
                break;
            case 2:
                cout << "Introduce la cantidad a depositar en Cuenta 1: ";
                cin >> cantidad;
                depositar(saldoCuenta1, cantidad);
                break;
            case 3:
                cout << "Introduce la cantidad a retirar de Cuenta 1: ";
                cin >> cantidad;
                retirar(saldoCuenta1, cantidad);
                break;
            case 4:
                consultarSaldo(saldoCuenta1, 1);
                break;
            case 5:
                cout << "Introduce la cantidad a depositar en Cuenta 2: ";
                cin >> cantidad;
                depositar(saldoCuenta2, cantidad);
                break;
            case 6:
                cout << "Introduce la cantidad a retirar de Cuenta 2: ";
                cin >> cantidad;
                retirar(saldoCuenta2, cantidad);
                break;
            case 7:
                consultarSaldo(saldoCuenta2, 2);
                break;
            case 8:
                cout << "Introduce la cantidad a transferir de Cuenta 1 a Cuenta 2: ";
                cin >> cantidad;
                transferir(saldoCuenta1, saldoCuenta2, cantidad);
                break;
            case 9:
                cout << "Introduce la cantidad a transferir a otro banco: ";
                cin >> cantidad;
                transferirOtroBanco(saldoCuenta1, cantidad);
                break;
            case 10:
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
            case 11:
                cout << "Introduce la cantidad a pagar en tu tarjeta de credito: ";
                cin >> cantidad;
                pagarTarjetaCredito(saldoCuenta1, cantidad);
                break;
           case 12:
                consultarPuntosTarjeta();
                break;
            case 13:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    } while (opcion != 13);

    return 0;
}
