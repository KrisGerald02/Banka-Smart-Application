#include <iostream>
#include <string>

using namespace std;

struct TarjetaDeCredito {
    string numero;
    string titular;
    double limite_credito;
    double saldo;
    int pagos_a_tiempo;
    int puntos;
};

// Funcion para realizar una compra
void realizarCompra(TarjetaDeCredito &tarjeta, double monto) {
    if (monto + tarjeta.saldo > tarjeta.limite_credito) {
        cout << "Compra denegada. Límite de crédito excedido." << endl;
    } else {
        tarjeta.saldo += monto;
        cout << "Compra realizada. Nuevo saldo: " << tarjeta.saldo << endl;
    }
}

// Funcion para realizar un pago
void realizarPago(TarjetaDeCredito &tarjeta, double monto, bool a_tiempo = true) {
    if (monto > tarjeta.saldo) {
        cout << "Pago excede el saldo de la tarjeta." << endl;
    } else {
        tarjeta.saldo -= monto;
        cout << "Pago realizado. Nuevo saldo: " << tarjeta.saldo << endl;
        if (a_tiempo) {
            acumularPuntos(tarjeta);
        }
    }
}

// Funcion para acumular puntos
void acumularPuntos(TarjetaDeCredito &tarjeta) {
    // Acumula 1 punto por cada pago a tiempo
    tarjeta.pagos_a_tiempo += 1;
    tarjeta.puntos += 1;
    cout << "Pago a tiempo registrado. Puntos acumulados: " << tarjeta.puntos << endl;
}

// Funcion para mostrar el saldo
void mostrarSaldo(const TarjetaDeCredito &tarjeta) {
    cout << "Saldo actual: " << tarjeta.saldo << endl;
}

// Funcion para mostrar los puntos
void mostrarPuntos(const TarjetaDeCredito &tarjeta) {
    cout << "Puntos acumulados: " << tarjeta.puntos << endl;
}

int main() {
    TarjetaDeCredito tarjeta;
    string numero, titular;
    double limite, monto;
    char pago_a_tiempo;

    cout << "Ingrese el número de la tarjeta: ";
    cin >> numero;
    cout << "Ingrese el titular de la tarjeta: ";
    cin.ignore(); // Para ignorar el salto de línea previo
    getline(cin, titular);
    cout << "Ingrese el límite de crédito: ";
    cin >> limite;

    // Inicializando la tarjeta directamente
    tarjeta.numero = numero;
    tarjeta.titular = titular;
    tarjeta.limite_credito = limite;
    tarjeta.saldo = 0;
    tarjeta.pagos_a_tiempo = 0;
    tarjeta.puntos = 0;

    cout << "Ingrese el monto de la compra: ";
    cin >> monto;
    realizarCompra(tarjeta, monto);
    mostrarSaldo(tarjeta);

    cout << "Ingrese el monto del pago: ";
    cin >> monto;
    cout << "¿El pago fue a tiempo? (s/n): ";
    cin >> pago_a_tiempo;
    realizarPago(tarjeta, monto, pago_a_tiempo == 's');
    mostrarSaldo(tarjeta);
    mostrarPuntos(tarjeta);

    cout << "Ingrese el monto del pago: ";
    cin >> monto;
    cout << "¿El pago fue a tiempo? (s/n): ";
    cin >> pago_a_tiempo;
    realizarPago(tarjeta, monto, pago_a_tiempo == 's');
    mostrarSaldo(tarjeta);
    mostrarPuntos(tarjeta);

    return 0;
}
