#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iomanip>

using namespace std;

FILE *ptrF;

struct Cuenta {
    char nombre[50];
    char email[50];
    char direccion[100];
    char numero[9];
    char f_nacimiento[11];
} cuenta;

// Función para generar una contraseña basada en el nombre y día de nacimiento
string generar_contraseña(const string& nombre, int dia_nacimiento) {
    string primera_parte = nombre.substr(0, 3);  // Obtiene los primeros 3 caracteres del nombre
    string segunda_parte = to_string(dia_nacimiento);  // Convierte el día de nacimiento a string
    return primera_parte + segunda_parte;  // Concatena las dos partes
}

void limpiarPantalla() {
    system("cls");  // Cambia esto a "clear" si estás en un sistema Unix/Linux
}

// Validación de correo electrónico usando regex
bool validacion_email(const char* email) {
    const regex patron_email(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, patron_email);
}

// Validación de número de teléfono usando regex
bool validacion_numero(const char* numero) {
    const regex patron_telefono(R"(\d{8}$)");
    return regex_match(numero, patron_telefono);
}

// Validación de nombre usando regex
bool validacion_nombre(const char* nombre) {
    const regex patron_nombre(R"(^[A-Z][a-z]*(\s[A-Z][a-z]*)*$)");
    return regex_match(nombre, patron_nombre);
}

// Función para generar un número de cuenta de 12 dígitos aleatorio
string generar_numero_cuenta() {
    string numero_cuenta;
    for (int i = 0; i < 12; ++i) {
        numero_cuenta += to_string(rand() % 10);
    }
    return numero_cuenta;
}

// Función para actualizar los datos de una cuenta
void actualizar_cuenta(const char* nombre_archivo) {
    char numero_cuenta[13], numero_cuenta1[13];
    char nombre[50], nombre1[50];
    char email[50], email1[50];
    char direccion[100], direccion1[100];
    char numero[9], numero1[9];
    float saldo_inicial, saldo_inicial1;
    int d_nacimiento, d_nacimiento1;
    int m_nacimiento, m_nacimiento1;
    int a_nacimiento, a_nacimiento1;

    FILE *ptrF = fopen(nombre_archivo, "r");
    FILE *ptrF1 = fopen("temporal.txt", "w");

    cout << "\nIntroduzca el numero de cuenta que desea actualizar: ";
    cin >> numero_cuenta1;

    while (fscanf(ptrF, "%s %s %s %s %s %f %d %d %d", numero_cuenta, nombre, email, direccion, numero, &saldo_inicial, &d_nacimiento, &m_nacimiento, &a_nacimiento) != EOF) {
        if (strcmp(numero_cuenta, numero_cuenta1) == 0) {
            int opcion;
            do {
                cout << "\n¿Que desea actualizar?: ";
                cout << "\n1. Nombre";
                cout << "\n2. Correo electronico";
                cout << "\n3. Direccion";
                cout << "\n4. Numero de telefono";
                cout << "\n5. Saldo inicial";
                cout << "\n0. Salir";
                cout << "\nSeleccione una opción: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        cout << "\nIntroduzca el nuevo nombre: ";
                        cin.ignore();
                        cin.getline(nombre1, 50);
                        strcpy(nombre, nombre1);
                        limpiarPantalla();
                        break;
                    case 2:
                        cout << "\nIntroduzca el nuevo correo electronico: ";
                        cin >> email1;
                        strcpy(email, email1);
                        limpiarPantalla();
                        break;
                    case 3:
                        cout << "\nIntroduzca la nueva direccion: ";
                        cin.ignore();
                        cin.getline(direccion1, 100);
                        strcpy(direccion, direccion1);
                        limpiarPantalla();
                        break;
                    case 4:
                        cout << "\nIntroduzca el nuevo numero de telefono: ";
                        cin >> numero1;
                        strcpy(numero, numero1);
                        limpiarPantalla();
                        break;
                    case 5:
                        cout << "\nIntroduzca el nuevo saldo inicial: ";
                        cin >> saldo_inicial1;
                        saldo_inicial = saldo_inicial1;
                        limpiarPantalla();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opción invalida. Por favor intente nuevamente.\n";
                        limpiarPantalla();
                }
            } while (opcion != 0);
            fprintf(ptrF1, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta, nombre, email, direccion, numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);
        } else {
            fprintf(ptrF1, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta, nombre, email, direccion, numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);
        }
    }
    fclose(ptrF);
    fclose(ptrF1);
    remove(nombre_archivo);
    rename("temporal.txt", nombre_archivo);
}

// Función para generar informe de cuenta en forma de tabla
void generar_informe(const char* nombre_archivo) {
    FILE *ptrF = fopen(nombre_archivo, "r");
    if (ptrF == NULL) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    char numero_cuenta[13];
    float saldo_inicial;

    cout << "-------------------------------------------------------------\n";
    cout << left << setw(20) << "Numero de Cuenta" << "| " << setw(20) << "Saldo Inicial" << "| " << setw(20) << "Saldo Actual" << "\n";
    cout << "-------------------------------------------------------------\n";
    
    while (fscanf(ptrF, "%s", numero_cuenta) != EOF) {
        fseek(ptrF, 50 + 50 + 100 + 9, SEEK_CUR); // Avanza el puntero del archivo para saltar los campos no necesarios
        fscanf(ptrF, "%f", &saldo_inicial);
        fseek(ptrF, 3 * sizeof(int), SEEK_CUR); // Avanza el puntero del archivo para saltar los campos no necesarios

        float saldo_actual = saldo_inicial; // Aquí puedes añadir cualquier lógica para calcular el saldo actual si es necesario
        cout << left << setw(20) << numero_cuenta << "| " << setw(20) << fixed << setprecision(2) << saldo_inicial << "| " << setw(20) << fixed << setprecision(2) << saldo_actual << "\n";
    }

    cout << "-------------------------------------------------------------\n";
    fclose(ptrF);
}

// Funciones de manejo de cuenta
void cuenta_ahorro();
void cuenta_chiqui();
void cuenta_universitaria();

void cuenta_ahorro() {
    double saldo_inicial;
    bool v_nombre = false, v_email = false, v_numero = false, v_saldo = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    cin.getline(cuenta.nombre, 50);
    cout << endl;

    if(validacion_nombre(cuenta.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cuenta.email;
    cout << endl;

    if(validacion_email(cuenta.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    cin.getline(cuenta.direccion, 100);
    cout << endl;

    cout << "Ingrese su numero de telefono --> ";
    cin >> cuenta.numero;
    cout << endl;

    if(validacion_numero(cuenta.numero)) {
        v_numero = true;
        cout << "Numero valido" << endl;
    } else {
        cout << "Numero invalido" << endl;
    }

    cout << "Ingrese su saldo inicial --> ";
    cin >> saldo_inicial;
    cout << endl;

    if(saldo_inicial >= 0) {
        v_saldo = true;
        cout << "Saldo inicial valido" << endl;
    } else {
        cout << "Saldo inicial invalido" << endl;
    }

    cout << "Ingrese su fecha de nacimiento (dd mm aaaa) --> ";
    int d_nacimiento, m_nacimiento, a_nacimiento;
    cin >> d_nacimiento >> m_nacimiento >> a_nacimiento;
    cout << endl;

    if(v_nombre && v_email && v_numero && v_saldo) {
        if((ptrF = fopen("cuenta_ahorro.txt", "a")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            srand(time(NULL));
            string numero_cuenta = generar_numero_cuenta();
            string contrasena = generar_contraseña(cuenta.nombre, d_nacimiento);

            fprintf(ptrF, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta.c_str(), cuenta.nombre, cuenta.email, cuenta.direccion, cuenta.numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);

            cout << "Cuenta de ahorro registrada exitosamente" << endl;
            cout << "Su numero de cuenta es: " << numero_cuenta << endl;
            cout << "Su contraseña es: " << contrasena << endl;
            fclose(ptrF);
        }
    } else {
        cout << "Datos invalidos, no se puede registrar la cuenta" << endl;
    }
}

void cuenta_chiqui() {
    double saldo_inicial;
    bool v_nombre = false, v_email = false, v_numero = false, v_saldo = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    cin.getline(cuenta.nombre, 50);
    cout << endl;

    if(validacion_nombre(cuenta.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cuenta.email;
    cout << endl;

    if(validacion_email(cuenta.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    cin.getline(cuenta.direccion, 100);
    cout << endl;

    cout << "Ingrese su numero de telefono --> ";
    cin >> cuenta.numero;
    cout << endl;

    if(validacion_numero(cuenta.numero)) {
        v_numero = true;
        cout << "Numero valido" << endl;
    } else {
        cout << "Numero invalido" << endl;
    }

    cout << "Ingrese su saldo inicial --> ";
    cin >> saldo_inicial;
    cout << endl;

    if(saldo_inicial >= 0) {
        v_saldo = true;
        cout << "Saldo inicial valido" << endl;
    } else {
        cout << "Saldo inicial invalido" << endl;
    }

    cout << "Ingrese su fecha de nacimiento (dd mm aaaa) --> ";
    int d_nacimiento, m_nacimiento, a_nacimiento;
    cin >> d_nacimiento >> m_nacimiento >> a_nacimiento;
    cout << endl;

    if(v_nombre && v_email && v_numero && v_saldo) {
        if((ptrF = fopen("cuenta_chiqui.txt", "a")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            srand(time(NULL));
            string numero_cuenta = generar_numero_cuenta();
            string contrasena = generar_contraseña(cuenta.nombre, d_nacimiento);

            fprintf(ptrF, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta.c_str(), cuenta.nombre, cuenta.email, cuenta.direccion, cuenta.numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);

            cout << "Cuenta chiqui registrada exitosamente" << endl;
            cout << "Su numero de cuenta es: " << numero_cuenta << endl;
            cout << "Su contraseña es: " << contrasena << endl;
            fclose(ptrF);
        }
    } else {
        cout << "Datos invalidos, no se puede registrar la cuenta" << endl;
    }
}

void cuenta_universitaria() {
    double saldo_inicial;
    bool v_nombre = false, v_email = false, v_numero = false, v_saldo = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    cin.getline(cuenta.nombre, 50);
    cout << endl;

    if(validacion_nombre(cuenta.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cuenta.email;
    cout << endl;

    if(validacion_email(cuenta.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    cin.getline(cuenta.direccion, 100);
    cout << endl;

    cout << "Ingrese su numero de telefono --> ";
    cin >> cuenta.numero;
    cout << endl;

    if(validacion_numero(cuenta.numero)) {
        v_numero = true;
        cout << "Numero valido" << endl;
    } else {
        cout << "Numero invalido" << endl;
    }

    cout << "Ingrese su saldo inicial --> ";
    cin >> saldo_inicial;
    cout << endl;

    if(saldo_inicial >= 0) {
        v_saldo = true;
        cout << "Saldo inicial valido" << endl;
    } else {
        cout << "Saldo inicial invalido" << endl;
    }

    cout << "Ingrese su fecha de nacimiento (dd mm aaaa) --> ";
    int d_nacimiento, m_nacimiento, a_nacimiento;
    cin >> d_nacimiento >> m_nacimiento >> a_nacimiento;
    cout << endl;

    if(v_nombre && v_email && v_numero && v_saldo) {
        if((ptrF = fopen("cuenta_universitaria.txt", "a")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            srand(time(NULL));
            string numero_cuenta = generar_numero_cuenta();
            string contrasena = generar_contraseña(cuenta.nombre, d_nacimiento);

            fprintf(ptrF, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta.c_str(), cuenta.nombre, cuenta.email, cuenta.direccion, cuenta.numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);

            cout << "Cuenta universitaria registrada exitosamente" << endl;
            cout << "Su numero de cuenta es: " << numero_cuenta << endl;
            cout << "Su contraseña es: " << contrasena << endl;
            fclose(ptrF);
        }
    } else {
        cout << "Datos invalidos, no se puede registrar la cuenta" << endl;
    }
}

void generar_informe_chiqui() {
    generar_informe("cuenta_chiqui.txt");
}

void generar_informe_universitaria() {
    generar_informe("cuenta_universitaria.txt");
}

int main() {
    int opcion, tipo_cuenta;
    bool salir = false;

    do {
        cout << "\nMenu de opciones" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Actualizar cuenta" << endl;
        cout << "3. Generar informe" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "\nSeleccione el tipo de cuenta: " << endl;
                cout << "1. Cuenta de Ahorro" << endl;
                cout << "2. Cuenta Chiqui" << endl;
                cout << "3. Cuenta Universitaria" << endl;
                cout << "Seleccione una opcion: ";
                cin >> tipo_cuenta;
                limpiarPantalla();

                switch (tipo_cuenta) {
                    case 1:
                        cuenta_ahorro();
                        limpiarPantalla();
                        break;
                    case 2:
                        cuenta_chiqui();
                        limpiarPantalla();
                        break;
                    case 3:
                        cuenta_universitaria();
                        limpiarPantalla();
                        break;
                    default:
                        cout << "Opcion de cuenta invalida" << endl;
                }
                break;
            case 2:
                cout << "\nSeleccione el tipo de cuenta: " << endl;
                cout << "1. Cuenta de Ahorro" << endl;
                cout << "2. Cuenta Chiqui" << endl;
                cout << "3. Cuenta Universitaria" << endl;
                cout << "Seleccione una opcion: ";
                cin >> tipo_cuenta;
                limpiarPantalla();

                switch (tipo_cuenta) {
                    case 1:
                        actualizar_cuenta("cuenta_ahorro.txt");
                        limpiarPantalla();
                        break;
                    case 2:
                        actualizar_cuenta("cuenta_chiqui.txt");
                        limpiarPantalla();
                        break;
                    case 3:
                        actualizar_cuenta("cuenta_universitaria.txt");
                        limpiarPantalla();
                        break;
                    default:
                        cout << "Opcion de cuenta invalida" << endl;
                }
                break;
            case 3:
                cout << "\nSeleccione el tipo de cuenta: " << endl;
                cout << "1. Cuenta de Ahorro" << endl;
                cout << "2. Cuenta Chiqui" << endl;
                cout << "3. Cuenta Universitaria" << endl;
                cout << "Seleccione una opcion: ";
                cin >> tipo_cuenta;
                limpiarPantalla();

                switch (tipo_cuenta) {
                    case 1:
                        generar_informe("cuenta_ahorro.txt");
                        limpiarPantalla();
                        break;
                    case 2:
                        generar_informe_chiqui();
                        limpiarPantalla();
                        break;
                    case 3:
                        generar_informe_universitaria();
                        limpiarPantalla();
                        break;
                    default:
                        cout << "Opcion de cuenta invalida" << endl;
                }
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida, por favor intente nuevamente" << endl;
        }
    } while (!salir);

    return 0;
}


// FIN CUENTA 

//INICIO PRESTAMO
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
                limpiarPantalla();
                break;
            case 2:
                consultarSaldoPrestamo(saldoPrestamo);
                limpiarPantalla();
                break;
            case 3:
                cout << "Introduce la cantidad a pagar del prestamo: ";
                cin >> cantidad;
                realizarPagoPrestamo(saldoPrestamo, cantidad);
                limpiarPantalla();
                break;
            case 4:
                if (saldoInicial > 0) {
                    escribirResumen(saldoInicial, 0, saldoPrestamo);
                    cout << "Resumen del prestamo generado en 'resumen_prestamo.txt'.\n";
                } else {
                    cout << "No hay prestamos realizados para generar un resumen.\n";
                }
                limpiarPantalla();
                break;
            case 5:
                cout << "Saliendo...\n";
                escribirEnArchivo("Saliendo...\n");
                limpiarPantalla();
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
// FIN PRESTAMO

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

 
