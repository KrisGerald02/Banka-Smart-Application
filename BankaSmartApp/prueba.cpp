#include <iostream>
#include <iomanip>
#include "contenedor_cuenta.h"
#include "contenedor_prestamo.h"
#include "contenedor_transacciones.h"

using namespace std;

//INICIO CUENTA
FILE *ptrF;
Cuenta cuenta;

// Función para generar una contraseña basada en el nombre y día de nacimiento
void generar_contraseña(const char* nombre, int dia_nacimiento, char* contrasena) {
    strncpy(contrasena, nombre, 3);
    char dia[3];
    sprintf(dia, "%02d", dia_nacimiento);
    strcat(contrasena, dia);
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
void generar_numero_cuenta(char* numero_cuenta) {
    for (int i = 0; i < 12; ++i) {
        numero_cuenta[i] = '0' + rand() % 10;
    }
    numero_cuenta[12] = '\0';
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

    printf("\nIntroduzca el numero de cuenta que desea actualizar: ");
    scanf("%s", numero_cuenta1);

    while (fscanf(ptrF, "%s %s %s %s %s %f %d %d %d", numero_cuenta, nombre, email, direccion, numero, &saldo_inicial, &d_nacimiento, &m_nacimiento, &a_nacimiento) != EOF) {
        if (strcmp(numero_cuenta, numero_cuenta1) == 0) {
            int opcion;
            do {
                printf("\n¿Que desea actualizar?: ");
                printf("\n1. Nombre");
                printf("\n2. Correo electronico");
                printf("\n3. Direccion");
                printf("\n4. Numero de telefono");
                printf("\n5. Saldo inicial");
                printf("\n0. Salir");
                printf("\nSeleccione una opción: ");
                scanf("%d", &opcion);

                switch (opcion) {
                    case 1:
                        printf("\nIntroduzca el nuevo nombre: ");
                        scanf(" %[^\n]", nombre1);
                        strcpy(nombre, nombre1);
                        limpiarPantalla();
                        break;
                    case 2:
                        printf("\nIntroduzca el nuevo correo electronico: ");
                        scanf("%s", email1);
                        strcpy(email, email1);
                        limpiarPantalla();
                        break;
                    case 3:
                        printf("\nIntroduzca la nueva direccion: ");
                        scanf(" %[^\n]", direccion1);
                        strcpy(direccion, direccion1);
                        limpiarPantalla();
                        break;
                    case 4:
                        printf("\nIntroduzca el nuevo numero de telefono: ");
                        scanf("%s", numero1);
                        strcpy(numero, numero1);
                        limpiarPantalla();
                        break;
                    case 5:
                        printf("\nIntroduzca el nuevo saldo inicial: ");
                        scanf("%f", &saldo_inicial1);
                        saldo_inicial = saldo_inicial1;
                        limpiarPantalla();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opción invalida. Por favor intente nuevamente.\n");
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
        printf("Error al abrir el archivo\n");
        return;
    }

    char numero_cuenta[13];
    float saldo_inicial;

    printf("-------------------------------------------------------------\n");
    printf("%-20s| %-20s| %-20s\n", "Numero de Cuenta", "Saldo Inicial", "Saldo Actual");
    printf("-------------------------------------------------------------\n");
    
    while (fscanf(ptrF, "%s", numero_cuenta) != EOF) {
        fseek(ptrF, 50 + 50 + 100 + 9, SEEK_CUR); // Avanza el puntero del archivo para saltar los campos no necesarios
        fscanf(ptrF, "%f", &saldo_inicial);
        fseek(ptrF, 3 * sizeof(int), SEEK_CUR); // Avanza el puntero del archivo para saltar los campos no necesarios

        float saldo_actual = saldo_inicial; // Aquí puedes añadir cualquier lógica para calcular el saldo actual si es necesario
        printf("%-20s| %-20.2f| %-20.2f\n", numero_cuenta, saldo_inicial, saldo_actual);
    }

    printf("-------------------------------------------------------------\n");
    fclose(ptrF);
}

// Funciones de manejo de cuenta
void cuenta_ahorro() {
    double saldo_inicial;
    bool v_nombre = false, v_email = false, v_numero = false, v_saldo = false;

    printf("Ingrese su nombre completo --> ");
    scanf(" %[^\n]", cuenta.nombre);

    if(validacion_nombre(cuenta.nombre)) {
        v_nombre = true;
        printf("Nombre valido\n");
    } else {
        printf("Nombre invalido\n");
    }

    printf("Ingrese su correo electronico --> ");
    scanf("%s", cuenta.email);

    if(validacion_email(cuenta.email)) {
        v_email = true;
        printf("Correo electronico valido\n");
    } else {
        printf("Correo electronico invalido\n");
    }

    printf("Ingrese su direccion --> ");
    scanf(" %[^\n]", cuenta.direccion);

    printf("Ingrese su numero de telefono --> ");
    scanf("%s", cuenta.numero);

    if(validacion_numero(cuenta.numero)) {
        v_numero = true;
        printf("Numero valido\n");
    } else {
        printf("Numero invalido\n");
    }

    printf("Ingrese su saldo inicial --> ");
    scanf("%lf", &saldo_inicial);

    if(saldo_inicial >= 0) {
        v_saldo = true;
        printf("Saldo inicial valido\n");
    } else {
        printf("Saldo inicial invalido\n");
    }

    printf("Ingrese su fecha de nacimiento (dd mm aaaa) --> ");
    int d_nacimiento, m_nacimiento, a_nacimiento;
    scanf("%d %d %d", &d_nacimiento, &m_nacimiento, &a_nacimiento);
    sprintf(cuenta.f_nacimiento, "%02d/%02d/%04d", d_nacimiento, m_nacimiento, a_nacimiento);

    if (v_nombre && v_email && v_numero && v_saldo) {
        char numero_cuenta[13];
        char contrasena[6];
        generar_numero_cuenta(numero_cuenta);
        generar_contraseña(cuenta.nombre, d_nacimiento, contrasena);

        printf("Cuenta generada exitosamente!\n");
        printf("Numero de cuenta: %s\n", numero_cuenta);
        printf("Contraseña: %s\n", contrasena);

        ptrF = fopen("cuenta_ahorro.txt", "a");
        if(ptrF == NULL) {
            printf("Error al abrir el archivo\n");
        } else {
            fprintf(ptrF, "%s %s %s %s %s %.2f %d %d %d\n", numero_cuenta, cuenta.nombre, cuenta.email, cuenta.direccion, cuenta.numero, saldo_inicial, d_nacimiento, m_nacimiento, a_nacimiento);
            printf("Cuenta guardada exitosamente en el archivo!\n");
            printf("Numero de cuenta: %s\n", numero_cuenta);
            printf("Contraseña: %s\n", contrasena);
            fclose(ptrF);
        }
    } else {
        printf("Verifique los campos ingresados\n");
    }
}

void cuenta_chiqui() {
    // Lógica para la cuenta chiqui
}

void cuenta_universitaria() {
    // Lógica para la cuenta universitaria
}

int main() {
    int opcion;

    do {
        printf("\nSeleccione el tipo de cuenta que desea abrir:\n");
        printf("1. Cuenta de Ahorro\n");
        printf("2. Cuenta Chiqui\n");
        printf("3. Cuenta Universitaria\n");
        printf("4. Actualizar cuenta\n");
        printf("5. Generar informe\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                cuenta_ahorro();
                break;
            case 2:
                cuenta_chiqui();
                break;
            case 3:
                cuenta_universitaria();
                break;
            case 4:
                actualizar_cuenta("cuenta_ahorro.txt");
                break;
            case 5:
                generar_informe("cuenta_ahorro.txt");
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción invalida. Por favor intente nuevamente.\n");
        }
    } while(opcion != 0);

    return 0;
}
 
 //FIN CUENTA

//INICIO PRESTAMO

void limpiarPantalla() {
    system("cls");  // Cambia esto a "clear" si estás en un sistema Unix/Linux
}

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

void solicitarPrestamo(Prestamo &prestamo, double monto, double tasaInteresAnual, int plazoMeses) {
    prestamo.saldoPrestamo = monto;
    prestamo.saldoInicial = monto;
    cout << "Has solicitado un prestamo de $" << monto << ".\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Has solicitado un prestamo de $%.2f.\n", monto);
    escribirEnArchivo(buffer);
    
    double pagoMensual = calcularPagoMensual(monto, tasaInteresAnual, plazoMeses);
    cout << "El pago mensual sera de $" << pagoMensual << " durante " << plazoMeses << " meses.\n";
    snprintf(buffer, sizeof(buffer), "El pago mensual sera de $%.2f durante %d meses.\n", pagoMensual, plazoMeses);
    escribirEnArchivo(buffer);
    prestamo.plazoMeses = plazoMeses;
}

void consultarSaldoPrestamo(const Prestamo &prestamo) {
    cout << "Saldo actual del prestamo: $" << prestamo.saldoPrestamo << ".\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Saldo actual del prestamo: $%.2f.\n", prestamo.saldoPrestamo);
    escribirEnArchivo(buffer);
}

void realizarPagoPrestamo(Prestamo &prestamo, double cantidad) {
    if (cantidad > 0 && cantidad <= prestamo.saldoPrestamo) {
        double saldoAnterior = prestamo.saldoPrestamo;
        prestamo.saldoPrestamo -= cantidad;
        cout << "Has realizado un pago de $" << cantidad << " del prestamo.\n";
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Has realizado un pago de $%.2f del prestamo.\n", cantidad);
        escribirEnArchivo(buffer);
        escribirResumen(saldoAnterior, cantidad, prestamo.saldoPrestamo);
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
    Prestamo prestamo = {0.0, 0.05, 0, 0.0};

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
                    solicitarPrestamo(prestamo, monto, prestamo.tasaInteresAnual, plazo);
                }
                limpiarPantalla();
                break;
            case 2:
                consultarSaldoPrestamo(prestamo);
                limpiarPantalla();
                break;
            case 3:
                cout << "Introduce la cantidad a pagar del prestamo: ";
                cin >> cantidad;
                realizarPagoPrestamo(prestamo, cantidad);
                limpiarPantalla();
                break;
            case 4:
                if (prestamo.saldoInicial > 0) {
                    escribirResumen(prestamo.saldoInicial, 0, prestamo.saldoPrestamo);
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


//INICIO DE SESION
#include <iostream>
#include <regex>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

 //INICIO DE SESION
 struct Cuenta {
    char numero_cuenta[13];
    string contrasena;
};

// Función para generar una contraseña basada en el nombre y día de nacimiento
string generar_contraseña(const string& nombre, int dia_nacimiento) {
    string primera_parte = nombre.substr(0, 3);  // Obtiene los primeros 3 caracteres del nombre
    string segunda_parte = to_string(dia_nacimiento);  // Convierte el día de nacimiento a string
    return primera_parte + segunda_parte;  // Concatena las dos partes
}

// Función para validar el inicio de sesión de empleados
bool iniciar_sesion_empleado(const string& numero_cuenta, const string& contrasena) {
    // Aquí podrías implementar la lógica para validar el inicio de sesión del empleado
    // Por ejemplo, podrías verificar en una lista de cuentas de empleados autorizados
    // En este caso, por simplicidad, devolvemos true si el número de cuenta y la contraseña coinciden
    return (numero_cuenta == "empleado" && contrasena == "contraseña_empleado");
}

// Función para validar el inicio de sesión de clientes
bool iniciar_sesion_cliente(const string& numero_cuenta, const string& contrasena) {
    ifstream archivo("clientes.txt");  // Archivo donde se guardan los datos de clientes
    if (!archivo) {
        cerr << "Error al abrir el archivo de clientes." << endl;
        return false;
    }

    Cuenta cuenta_cliente;
    bool encontrado = false;

    // Leer datos de cliente del archivo
    while (archivo >> cuenta_cliente.numero_cuenta >> cuenta_cliente.contrasena) {
        if (numero_cuenta == cuenta_cliente.numero_cuenta && contrasena == cuenta_cliente.contrasena) {
            encontrado = true;
            break;
        }
    }

    archivo.close();
    return encontrado;
}

void limpiarPantalla() {
    system("cls");  // Cambia esto a "clear" si estás en un sistema Unix/Linux
}

int main() {
    int opcion;
    bool salir = false;

    do {
        cout << "Bienvenido al sistema de inicio de sesion" << endl;
        cout << "1. Inicio de sesion para empleados" << endl;
        cout << "2. Inicio de sesion para clientes" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                string numero_cuenta, contrasena;
                cout << "Inicio de sesion para empleados" << endl;
                cout << "Ingrese el numero de cuenta: ";
                getline(cin, numero_cuenta);
                cout << "Ingrese la contrasena: ";
                getline(cin, contrasena);

                if (iniciar_sesion_empleado(numero_cuenta, contrasena)) {
                    cout << "Inicio de sesion exitoso como empleado." << endl;
                    // Aquí puedes agregar las acciones que pueden realizar los empleados
                    // Por ejemplo, llamar a funciones para actualizar cuentas o generar informes
                } else {
                    cout << "Error: Numero de cuenta o contrasena incorrectos." << endl;
                }
                break;
            }
            case 2: {
                string numero_cuenta, contrasena;
                cout << "Inicio de sesion para clientes" << endl;
                cout << "Ingrese el numero de cuenta: ";
                getline(cin, numero_cuenta);
                cout << "Ingrese la contrasena: ";
                getline(cin, contrasena);

                if (iniciar_sesion_cliente(numero_cuenta, contrasena)) {
                    cout << "Inicio de sesion exitoso como cliente." << endl;
                    // Aquí puedes agregar las acciones que pueden realizar los clientes
                    // Por ejemplo, llamar a funciones para actualizar cuentas o generar informes
                } else {
                    cout << "Error: Numero de cuenta o contrasena incorrectos." << endl;
                }
                break;
            }
            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida, por favor intente nuevamente." << endl;
        }
    } while (!salir);

    cout << "Gracias por usar nuestro sistema de inicio de sesion." << endl;

    return 0;
}

