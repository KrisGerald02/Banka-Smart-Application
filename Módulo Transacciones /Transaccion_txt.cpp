#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iomanip>

using namespace std;
//INICIO TRANSACCIONES
#include <iostream>
#include <string>
#include <fstream>

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

void limpiarPantalla() {
    system("cls");
}

void escribirEnArchivo(const string &mensaje) {
    ofstream archivo("transacciones.txt", ios::app);
    if (!archivo) {
        cout << "No se pudo abrir/crear el archivo." << endl;
        return;
    }
    archivo << mensaje << endl;
    archivo.close();
}

// Función para crear una tarjeta de crédito
void crearTarjetaDeCredito(TarjetaDeCredito &tarjeta) {
    cout << "Ingrese el numero de la tarjeta: ";
    cin >> tarjeta.numero;
    cout << "Ingrese el titular de la tarjeta: ";
    cin.ignore(); // Para ignorar el salto de línea previo
    getline(cin, tarjeta.titular);
    cout << "Ingrese el limite de credito: ";
    cin >> tarjeta.limite_credito;
    tarjeta.saldo = 0;
    tarjeta.pagos_a_tiempo = 0;
    tarjeta.puntos = 0;
    cout << "Tarjeta de credito creada exitosamente.\n";

    escribirEnArchivo("Tarjeta de credito creada: " + tarjeta.numero + ", Titular: " + tarjeta.titular + ", Limite de credito: $" + to_string(tarjeta.limite_credito));
}

void depositar(double &saldo, double cantidad) {
    if (cantidad > 0) {
        saldo += cantidad;
        cout << "Has depositado $" << cantidad << ".\n";
        escribirEnArchivo("Deposito de $" + to_string(cantidad) + ". Saldo actual: $" + to_string(saldo));
    } else {
        cout << "Cantidad invalida.\n";
        escribirEnArchivo("Intento de deposito con cantidad invalida: $" + to_string(cantidad));
    }
}

void retirar(double &saldo, double cantidad) {
    if (cantidad > 0 && cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Has retirado $" << cantidad << ".\n";
        escribirEnArchivo("Retiro de $" + to_string(cantidad) + ". Saldo actual: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de retiro con saldo insuficiente. Cantidad: $" + to_string(cantidad) + ", Saldo actual: $" + to_string(saldo));
    }
}

void consultarSaldo(double saldo, int cuenta) {
    cout << "Saldo actual de la cuenta " << cuenta << ": $" << saldo << ".\n";
    escribirEnArchivo("Consulta de saldo. Cuenta " + to_string(cuenta) + ": $" + to_string(saldo));
}

void transferir(double &saldoOrigen, double &saldoDestino, double cantidad) {
    if (cantidad > 0 && cantidad <= saldoOrigen) {
        saldoOrigen -= cantidad;
        saldoDestino += cantidad;
        cout << "Has transferido $" << cantidad << " de la cuenta origen a la cuenta destino.\n";
        escribirEnArchivo("Transferencia de $" + to_string(cantidad) + " de cuenta origen a cuenta destino. Saldo origen: $" + to_string(saldoOrigen) + ", Saldo destino: $" + to_string(saldoDestino));
    } else {
        cout << "Saldo Insuficiente en la Cuenta Origen.\n";
        escribirEnArchivo("Intento de transferencia con saldo insuficiente. Cantidad: $" + to_string(cantidad) + ", Saldo origen: $" + to_string(saldoOrigen));
    }
}

void transferirOtroBanco(double &saldoOrigen, double cantidad) {
    double comision = 0.10 * cantidad;
    double total = cantidad + comision;
    if (total > 0 && total <= saldoOrigen) {
        saldoOrigen -= total;
        cout << "Has transferido $" << cantidad << " a otro banco con una comision de $" << comision << ".\n";
        cout << "Total deducido de tu cuenta: $" << total << ".\n";
        escribirEnArchivo("Transferencia a otro banco de $" + to_string(cantidad) + " con comision de $" + to_string(comision) + ". Total deducido: $" + to_string(total) + ". Saldo actual: $" + to_string(saldoOrigen));
    } else {
        cout << "Saldo Insuficiente en la Cuenta Origen.\n";
        escribirEnArchivo("Intento de transferencia a otro banco con saldo insuficiente. Cantidad: $" + to_string(cantidad) + ", Saldo origen: $" + to_string(saldoOrigen));
    }
}

void pagarServicio(double &saldo, const string &servicio, double cantidad) {
    if (cantidad > 0 && cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Has pagado $" << cantidad << " por el servicio de " << servicio << ".\n";
        escribirEnArchivo("Pago de servicio: " + servicio + " de $" + to_string(cantidad) + ". Saldo actual: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de pago de servicio con saldo insuficiente. Servicio: " + servicio + ", Cantidad: $" + to_string(cantidad) + ", Saldo actual: $" + to_string(saldo));
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
        escribirEnArchivo("Pago de tarjeta de credito de $" + to_string(cantidad) + ". Pagos a tiempo: " + to_string(tarjeta.pagos_a_tiempo) + ", Puntos acumulados: " + to_string(tarjeta.puntos) + ". Saldo actual: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de pago de tarjeta de credito con saldo insuficiente. Cantidad: $" + to_string(cantidad) + ", Saldo actual: $" + to_string(saldo));
    }
}

void consultarPuntosTarjeta() {
    cout << "Puntos acumulados en la tarjeta: " << tarjeta.puntos << "\n";
    cout << "Pagos a tiempo realizados: " << tarjeta.pagos_a_tiempo << "\n";
    escribirEnArchivo("Consulta de puntos de tarjeta de credito. Puntos acumulados: " + to_string(tarjeta.puntos) + ", Pagos a tiempo: " + to_string(tarjeta.pagos_a_tiempo));
}

void mostrarMenuPrincipal() {
    cout << "\n--- Menu Principal de Banka Smart Aplication ---\n";
    cout << "1. Transacciones\n";
    cout << "2. Servicios Basicos\n";
    cout << "3. Tarjeta de Credito\n";
    cout << "4. Salir\n";
    cout << "Elige una opcion: ";
}

void mostrarMenuTransacciones() {
    cout << "\n--- Menu de Transacciones ---\n";
    cout << "1. Depositar dinero en Cuenta 1\n";
    cout << "2. Retirar dinero de Cuenta 1\n";
    cout << "3. Consultar saldo de Cuenta 1\n";
    cout << "4. Depositar dinero en Cuenta 2\n";
    cout << "5. Retirar dinero de Cuenta 2\n";
    cout << "6. Consultar saldo de Cuenta 2\n";
    cout << "7. Transferir dinero entre cuentas\n";
    cout << "8. Transferir dinero a otro banco\n";
    cout << "9. Regresar al Menu Principal\n";
    cout << "Elige una opcion: ";
}

void mostrarMenuServicios() {
    cout << "\n--- Menu de Servicios Basicos ---\n";
    cout << "1. Pagar Luz\n";
    cout << "2. Pagar Agua\n";
    cout << "3. Pagar Internet\n";
    cout << "4. Regresar al Menu Principal\n";
    cout << "Elige una opcion: ";
}

void mostrarMenuTarjetaCredito() {
    cout << "\n--- Menu de Tarjeta de Credito ---\n";
    cout << "1. Crear tarjeta de credito\n";
    cout << "2. Pagar tarjeta de credito\n";
    cout << "3. Consultar puntos de la tarjeta de credito\n";
    cout << "4. Regresar al Menu Principal\n";
    cout << "Elige una opcion: ";
}

int main() {
    int opcionPrincipal, opcionTransacciones, opcionServicios, opcionTarjetaCredito;
    double cantidad;

    do {
        mostrarMenuPrincipal();
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1:
                do {
                    mostrarMenuTransacciones();
                    cin >> opcionTransacciones;

                    switch (opcionTransacciones) {
                        case 1:
                            cout << "Introduce la cantidad a depositar en Cuenta 1: ";
                            cin >> cantidad;
                            depositar(saldoCuenta1, cantidad);
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Introduce la cantidad a retirar de Cuenta 1: ";
                            cin >> cantidad;
                            retirar(saldoCuenta1, cantidad);
                            limpiarPantalla();
                            break;
                        case 3:
                            consultarSaldo(saldoCuenta1, 1);
                            limpiarPantalla();
                            break;
                        case 4:
                            cout << "Introduce la cantidad a depositar en Cuenta 2: ";
                            cin >> cantidad;
                            depositar(saldoCuenta2, cantidad);
                            limpiarPantalla();
                            break;
                        case 5:
                            cout << "Introduce la cantidad a retirar de Cuenta 2: ";
                            cin >> cantidad;
                            retirar(saldoCuenta2, cantidad);
                            limpiarPantalla();
                            break;
                        case 6:
                            consultarSaldo(saldoCuenta2, 2);
                            limpiarPantalla();
                            break;
                        case 7:
                            cout << "Introduce la cantidad a transferir de Cuenta 1 a Cuenta 2: ";
                            cin >> cantidad;
                            transferir(saldoCuenta1, saldoCuenta2, cantidad);
                            limpiarPantalla();
                            break;
                        case 8:
                            cout << "Introduce la cantidad a transferir a otro banco: ";
                            cin >> cantidad;
                            transferirOtroBanco(saldoCuenta1, cantidad);
                            limpiarPantalla();
                            break;
                        case 9:
                            limpiarPantalla();
                            break;
                        default:
                            cout << "Opcion invalida. Intenta de nuevo.\n";
                            escribirEnArchivo("Opcion invalida seleccionada en el menu de transacciones.");
                    }
                } while (opcionTransacciones != 9);
                break;
            case 2:
                do {
                    mostrarMenuServicios();
                    cin >> opcionServicios;

                    switch (opcionServicios) {
                        case 1:
                            cout << "Introduce la cantidad a pagar: ";
                            cin >> cantidad;
                            pagarServicio(saldoCuenta1, "Luz", cantidad);
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Introduce la cantidad a pagar: ";
                            cin >> cantidad;
                            pagarServicio(saldoCuenta1, "Agua", cantidad);
                            limpiarPantalla();
                            break;
                        case 3:
                            cout << "Introduce la cantidad a pagar: ";
                            cin >> cantidad;
                            pagarServicio(saldoCuenta1, "Internet", cantidad);
                            limpiarPantalla();
                            break;
                        case 4:
                            limpiarPantalla();
                            break;
                        default:
                            cout << "Opcion de servicio invalida.\n";
                            escribirEnArchivo("Opcion de servicio invalida seleccionada.");
                    }
                } while (opcionServicios != 4);
                break;
            case 3:
                do {
                    mostrarMenuTarjetaCredito();
                    cin >> opcionTarjetaCredito;

                    switch (opcionTarjetaCredito) {
                        case 1:
                            crearTarjetaDeCredito(tarjeta);
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Introduce la cantidad a pagar en tu tarjeta de credito: ";
                            cin >> cantidad;
                            pagarTarjetaCredito(saldoCuenta1, cantidad);
                            limpiarPantalla();
                            break;
                        case 3:
                            consultarPuntosTarjeta();
                            limpiarPantalla();
                            break;
                        case 4:
                            limpiarPantalla();
                            break;
                        default:
                            cout << "Opcion invalida. Intenta de nuevo.\n";
                            escribirEnArchivo("Opción invalida seleccionada en el menu de tarjeta de credito.");
                    }
                } while (opcionTarjetaCredito != 4);
                break;
            case 4:
                cout << "Saliendo...\n";
                escribirEnArchivo("Salida del sistema.");
                limpiarPantalla();
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
                escribirEnArchivo("Opción invalida seleccionada en el menu principal.");
        }
    } while (opcionPrincipal != 4);

    return 0;
}
 // FIN TRANSACCION

