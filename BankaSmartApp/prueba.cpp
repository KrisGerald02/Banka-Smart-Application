#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Estructura para el manejo de usuarios
struct Usuario {
    string nombre;
    string password;
};

// Estructura para el manejo de tarjetas de crédito
struct TarjetaCredito {
    string numero;
    string titular;
    double limite_credito;
    double saldo;
    int pagos_a_tiempo;
    int puntos;
};

// Variables globales
double saldoCuenta1 = 0.0;
double saldoCuenta2 = 0.0;
double saldoPrestamo = 0.0;
double saldoInicial = 0.0;
double tasaInteresAnual = 0.05;
int plazoMeses = 0;
TarjetaCredito tarjeta;

// Función para escribir en el archivo de registro
void escribirEnArchivo(const string &mensaje) {
    ofstream archivo("registro.txt", ios::app);
    if (archivo.is_open()) {
        archivo << mensaje << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de registro.\n";
    }
}

// Menús
void mostrarMenuPrincipal() {
    cout << "\nMenu Principal:\n";
    cout << "1. Transacciones\n";
    cout << "2. Prestamos\n";
    cout << "3. Servicios\n";
    cout << "4. Tarjeta de Credito\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuTransacciones() {
    cout << "\nMenu de Transacciones:\n";
    cout << "1. Depositar en Cuenta 1\n";
    cout << "2. Retirar de Cuenta 1\n";
    cout << "3. Consultar Saldo de Cuenta 1\n";
    cout << "4. Depositar en Cuenta 2\n";
    cout << "5. Retirar de Cuenta 2\n";
    cout << "6. Consultar Saldo de Cuenta 2\n";
    cout << "7. Transferir de Cuenta 1 a Cuenta 2\n";
    cout << "8. Transferir a Otro Banco\n";
    cout << "9. Regresar al Menu Principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuPrestamos() {
    cout << "\nMenu de Prestamos:\n";
    cout << "1. Solicitar Prestamo\n";
    cout << "2. Consultar Saldo de Prestamo\n";
    cout << "3. Realizar Pago de Prestamo\n";
    cout << "4. Generar Resumen de Prestamo\n";
    cout << "5. Regresar al Menu Principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuServicios() {
    cout << "\nMenu de Servicios:\n";
    cout << "1. Pagar Servicio de Luz\n";
    cout << "2. Pagar Servicio de Agua\n";
    cout << "3. Pagar Servicio de Internet\n";
    cout << "4. Regresar al Menu Principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuTarjetaCredito() {
    cout << "\nMenu de Tarjeta de Credito:\n";
    cout << "1. Crear Tarjeta de Credito\n";
    cout << "2. Pagar Tarjeta de Credito\n";
    cout << "3. Consultar Saldo de Tarjeta de Credito\n";
    cout << "4. Regresar al Menu Principal\n";
    cout << "Seleccione una opcion: ";
}

// Funciones de transacciones
void depositar(double &saldo, double cantidad) {
    saldo += cantidad;
    cout << "Deposito realizado con exito.\n";
    escribirEnArchivo("Deposito en cuenta. Monto: $" + to_string(cantidad) + ", Nuevo saldo: $" + to_string(saldo));
}

void retirar(double &saldo, double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Retiro realizado con exito.\n";
        escribirEnArchivo("Retiro de cuenta. Monto: $" + to_string(cantidad) + ", Nuevo saldo: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de retiro fallido. Monto: $" + to_string(cantidad) + ", Saldo en cuenta: $" + to_string(saldo));
    }
}

void consultarSaldo(double saldo, int cuenta) {
    cout << "Saldo de la Cuenta " << cuenta << ": $" << saldo << ".\n";
    escribirEnArchivo("Consulta de saldo en Cuenta " + to_string(cuenta) + ". Saldo: $" + to_string(saldo));
}

void transferir(double &saldoDesde, double &saldoHacia, double cantidad) {
    if (cantidad <= saldoDesde) {
        saldoDesde -= cantidad;
        saldoHacia += cantidad;
        cout << "Transferencia realizada con exito.\n";
        escribirEnArchivo("Transferencia entre cuentas. Monto: $" + to_string(cantidad) + ", Saldo cuenta origen: $" + to_string(saldoDesde) + ", Saldo cuenta destino: $" + to_string(saldoHacia));
    } else {
        cout << "Saldo Insuficiente en la cuenta de origen.\n";
        escribirEnArchivo("Intento de transferencia fallido. Monto: $" + to_string(cantidad) + ", Saldo cuenta origen: $" + to_string(saldoDesde));
    }
}

void transferirOtroBanco(double &saldo, double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Transferencia a otro banco realizada con exito.\n";
        escribirEnArchivo("Transferencia a otro banco. Monto: $" + to_string(cantidad) + ", Nuevo saldo: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de transferencia a otro banco fallido. Monto: $" + to_string(cantidad) + ", Saldo en cuenta: $" + to_string(saldo));
    }
}

// Funciones de servicios
void pagarServicio(double &saldo, const string &servicio, double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Pago del servicio de " << servicio << " realizado con exito.\n";
        escribirEnArchivo("Pago de servicio. Servicio: " + servicio + ", Monto: $" + to_string(cantidad) + ", Nuevo saldo: $" + to_string(saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de pago de servicio fallido. Servicio: " + servicio + ", Monto: $" + to_string(cantidad) + ", Saldo en cuenta: $" + to_string(saldo));
    }
}

// Funciones de tarjeta de crédito
void pagarTarjetaCredito(double &saldo, double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        tarjeta.saldo -= cantidad;
        if (tarjeta.saldo <= 0) {
            tarjeta.pagos_a_tiempo++;
            tarjeta.puntos += 100;
            tarjeta.saldo = 0;
        }
        cout << "Pago de tarjeta de credito realizado con exito.\n";
        escribirEnArchivo("Pago de tarjeta de credito. Monto: $" + to_string(cantidad) + ", Nuevo saldo en cuenta: $" + to_string(saldo) + ", Saldo de la tarjeta: $" + to_string(tarjeta.saldo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de pago de tarjeta de credito fallido. Monto: $" + to_string(cantidad) + ", Saldo en cuenta: $" + to_string(saldo));
    }
}

void consultarSaldoTarjetaCredito() {
    cout << "Saldo de la Tarjeta de Credito: $" << tarjeta.saldo << ".\n";
    cout << "Limite de Credito: $" << tarjeta.limite_credito << ".\n";
    cout << "Puntos acumulados: " << tarjeta.puntos << ".\n";
    cout << "Pagos a tiempo: " << tarjeta.pagos_a_tiempo << ".\n";
    escribirEnArchivo("Consulta de saldo de tarjeta de credito. Saldo: $" + to_string(tarjeta.saldo) + ", Limite de credito: $" + to_string(tarjeta.limite_credito) + ", Puntos: " + to_string(tarjeta.puntos) + ", Pagos a tiempo: " + to_string(tarjeta.pagos_a_tiempo));
}

// Funciones de prestamos
void solicitarPrestamo() {
    cout << "Ingrese el monto del prestamo que desea solicitar: ";
    cin >> saldoInicial;
    cout << "Ingrese el plazo del prestamo en meses: ";
    cin >> plazoMeses;
    saldoPrestamo = saldoInicial;
    cout << "Prestamo solicitado con exito.\n";
    escribirEnArchivo("Solicitud de prestamo. Monto: $" + to_string(saldoInicial) + ", Plazo: " + to_string(plazoMeses) + " meses.");
}

void consultarSaldoPrestamo() {
    cout << "Saldo actual del prestamo: $" << saldoPrestamo << ".\n";
    escribirEnArchivo("Consulta de saldo de prestamo. Saldo actual: $" + to_string(saldoPrestamo));
}

void realizarPagoPrestamo(double &saldo, double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        saldoPrestamo -= cantidad;
        cout << "Pago del prestamo realizado con exito.\n";
        escribirEnArchivo("Pago de prestamo. Monto: $" + to_string(cantidad) + ", Nuevo saldo de prestamo: $" + to_string(saldoPrestamo));
    } else {
        cout << "Saldo Insuficiente.\n";
        escribirEnArchivo("Intento de pago de prestamo fallido. Monto: $" + to_string(cantidad) + ", Saldo en cuenta: $" + to_string(saldo));
    }
}

void generarResumenPrestamo() {
    double tasaInteresMensual = tasaInteresAnual / 12;
    double saldoPendiente = saldoInicial;
    double pagoMensual = saldoInicial * (tasaInteresMensual * pow(1 + tasaInteresMensual, plazoMeses)) / (pow(1 + tasaInteresMensual, plazoMeses) - 1);

    cout << "\nResumen del Prestamo:\n";
    cout << "Monto inicial del prestamo: $" << saldoInicial << "\n";
    cout << "Plazo del prestamo: " << plazoMeses << " meses\n";
    cout << "Pago mensual: $" << fixed << setprecision(2) << pagoMensual << "\n";
    cout << "Detalle de pagos:\n";
    cout << "Mes\tPago Mensual\tInteres\tPrincipal\tSaldo Pendiente\n";

    for (int mes = 1; mes <= plazoMeses; ++mes) {
        double interesMensual = saldoPendiente * tasaInteresMensual;
        double principalMensual = pagoMensual - interesMensual;
        saldoPendiente -= principalMensual;

        cout << mes << "\t$" << fixed << setprecision(2) << pagoMensual << "\t$" << interesMensual << "\t$" << principalMensual << "\t$" << saldoPendiente << "\n";
    }
    escribirEnArchivo("Generacion de resumen de prestamo. Monto inicial: $" + to_string(saldoInicial) + ", Plazo: " + to_string(plazoMeses) + " meses, Pago mensual: $" + to_string(pagoMensual));
}

// Función de inicio de sesión
bool iniciarSesion(Usuario usuarios[], int numUsuarios, string &nombre) {
    string password;
    cout << "Nombre de usuario: ";
    cin >> nombre;
    cout << "Contrasena: ";
    cin >> password;

    for (int i = 0; i < numUsuarios; ++i) {
        if (usuarios[i].nombre == nombre && usuarios[i].password == password) {
            return true;
        }
    }
    return false;
}

void iniciarSesion(Usuario usuarios[], int numUsuarios) {
    string nombre;
    if (iniciarSesion(usuarios, numUsuarios, nombre)) {
        cout << "Inicio de sesion exitoso. Bienvenido, " << nombre << ".\n";
        escribirEnArchivo("Inicio de sesion del usuario: " + nombre);

        int opcionMenuPrincipal;
        do {
            mostrarMenuPrincipal();
            cin >> opcionMenuPrincipal;
            switch (opcionMenuPrincipal) {
                case 1: {
                    int opcionTransacciones;
                    do {
                        mostrarMenuTransacciones();
                        cin >> opcionTransacciones;
                        double cantidad;
                        switch (opcionTransacciones) {
                            case 1: {
                                cout << "Ingrese la cantidad a depositar en Cuenta 1: ";
                                cin >> cantidad;
                                depositar(saldoCuenta1, cantidad);
                                break;
                            }
                            case 2: {
                                cout << "Ingrese la cantidad a retirar de Cuenta 1: ";
                                cin >> cantidad;
                                retirar(saldoCuenta1, cantidad);
                                break;
                            }
                            case 3:
                                consultarSaldo(saldoCuenta1, 1);
                                break;
                            case 4: {
                                cout << "Ingrese la cantidad a depositar en Cuenta 2: ";
                                cin >> cantidad;
                                depositar(saldoCuenta2, cantidad);
                                break;
                            }
                            case 5: {
                                cout << "Ingrese la cantidad a retirar de Cuenta 2: ";
                                cin >> cantidad;
                                retirar(saldoCuenta2, cantidad);
                                break;
                            }
                            case 6:
                                consultarSaldo(saldoCuenta2, 2);
                                break;
                            case 7: {
                                cout << "Ingrese la cantidad a transferir de Cuenta 1 a Cuenta 2: ";
                                cin >> cantidad;
                                transferir(saldoCuenta1, saldoCuenta2, cantidad);
                                break;
                            }
                            case 8: {
                                cout << "Ingrese la cantidad a transferir a otro banco: ";
                                cin >> cantidad;
                                transferirOtroBanco(saldoCuenta1, cantidad);
                                break;
                            }
                            case 9:
                                break;
                            default:
                                cout << "Opcion invalida. Intente nuevamente.\n";
                                break;
                        }
                    } while (opcionTransacciones != 9);
                    break;
                }
                case 2: {
                    int opcionPrestamos;
                    do {
                        mostrarMenuPrestamos();
                        cin >> opcionPrestamos;
                        double cantidad;
                        switch (opcionPrestamos) {
                            case 1:
                                solicitarPrestamo();
                                break;
                            case 2:
                                consultarSaldoPrestamo();
                                break;
                            case 3: {
                                cout << "Ingrese la cantidad a pagar del prestamo: ";
                                cin >> cantidad;
                                realizarPagoPrestamo(saldoCuenta1, cantidad);
                                break;
                            }
                            case 4:
                                generarResumenPrestamo();
                                break;
                            case 5:
                                break;
                            default:
                                cout << "Opcion invalida. Intente nuevamente.\n";
                                break;
                        }
                    } while (opcionPrestamos != 5);
                    break;
                }
                case 3: {
                    int opcionServicios;
                    do {
                        mostrarMenuServicios();
                        cin >> opcionServicios;
                        double cantidad;
                        switch (opcionServicios) {
                            case 1: {
                                cout << "Ingrese la cantidad a pagar por el servicio de luz: ";
                                cin >> cantidad;
                                pagarServicio(saldoCuenta1, "Luz", cantidad);
                                break;
                            }
                            case 2: {
                                cout << "Ingrese la cantidad a pagar por el servicio de agua: ";
                                cin >> cantidad;
                                pagarServicio(saldoCuenta1, "Agua", cantidad);
                                break;
                            }
                            case 3: {
                                cout << "Ingrese la cantidad a pagar por el servicio de internet: ";
                                cin >> cantidad;
                                pagarServicio(saldoCuenta1, "Internet", cantidad);
                                break;
                            }
                            case 4:
                                break;
                            default:
                                cout << "Opcion invalida. Intente nuevamente.\n";
                                break;
                        }
                    } while (opcionServicios != 4);
                    break;
                }
                case 4: {
                    int opcionTarjetaCredito;
                    do {
                        mostrarMenuTarjetaCredito();
                        cin >> opcionTarjetaCredito;
                        double cantidad;
                        switch (opcionTarjetaCredito) {
                            case 1: {
                                cout << "Ingrese el numero de la tarjeta de credito: ";
                                cin >> tarjeta.numero;
                                cout << "Ingrese el nombre del titular: ";
                                cin >> tarjeta.titular;
                                cout << "Ingrese el limite de credito: ";
                                cin >> tarjeta.limite_credito;
                                tarjeta.saldo = 0;
                                tarjeta.pagos_a_tiempo = 0;
                                tarjeta.puntos = 0;
                                cout << "Tarjeta de credito creada con exito.\n";
                                escribirEnArchivo("Creacion de tarjeta de credito. Numero: " + tarjeta.numero + ", Titular: " + tarjeta.titular + ", Limite: $" + to_string(tarjeta.limite_credito));
                                break;
                            }
                            case 2: {
                                cout << "Ingrese la cantidad a pagar de la tarjeta de credito: ";
                                cin >> cantidad;
                                pagarTarjetaCredito(saldoCuenta1, cantidad);
                                break;
                            }
                            case 3: {
                                consultarSaldoTarjetaCredito();
                                break;
                            }
                            case 4:
                                break;
                            default:
                                cout << "Opcion invalida. Intente nuevamente.\n";
                                break;
                        }
                    } while (opcionTarjetaCredito != 4);
                    break;
                }
                case 5:
                    cout << "Cerrando sesion...\n";
                    escribirEnArchivo("Cierre de sesion del usuario: " + nombre);
                    break;
                default:
                    cout << "Opcion invalida. Intente nuevamente.\n";
                    break;
            }
        } while (opcionMenuPrincipal != 5);
    } else {
        cout << "Credenciales incorrectas. Intente nuevamente.\n";
        escribirEnArchivo("Intento de inicio de sesion fallido para el usuario: " + nombre);
    }
}

int main() {
    int numUsuarios = 2;
    Usuario usuarios[numUsuarios];

    // Creación de usuarios
    usuarios[0].nombre = "admin";
    usuarios[0].password = "admin123";
    usuarios[1].nombre = "user";
    usuarios[1].password = "user123";

    escribirEnArchivo("Inicio del sistema bancario");

    // Inicio de sesión del usuario
    iniciarSesion(usuarios, numUsuarios);

    escribirEnArchivo("Cierre del sistema bancario");
    return 0;
}
