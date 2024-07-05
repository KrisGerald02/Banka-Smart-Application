#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <regex>
#include <cmath>
#include "contenedor_cuenta.h"
#include "contenedor_prestamo.h"
#include "contenedor_transacciones.h"

using namespace std;

// Estructura para manejar datos de préstamo
struct Prestamo {
    double saldoPrestamo;
    double tasaInteresAnual;
    int plazoMeses;
    double saldoInicial;
};

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
            fclose(ptrF);
        }
    } else {
        printf("No se pudo crear la cuenta debido a datos invalidos.\n");
    }
}

//INICIO PRESTAMOS
void calcularSaldoPrestamo(Prestamo& prestamo) {
    prestamo.saldoPrestamo = prestamo.saldoInicial;
    double tasaInteresMensual = prestamo.tasaInteresAnual / 12.0 / 100.0;

    for (int i = 0; i < prestamo.plazoMeses; ++i) {
        prestamo.saldoPrestamo *= (1 + tasaInteresMensual);
    }
}

void imprimirDetallePrestamo(const Prestamo& prestamo) {
    cout << fixed << setprecision(2);
    cout << "Saldo inicial del prestamo: $" << prestamo.saldoInicial << endl;
    cout << "Tasa de interes anual: " << prestamo.tasaInteresAnual << "%" << endl;
    cout << "Plazo del prestamo: " << prestamo.plazoMeses << " meses" << endl;
    cout << "Saldo total del prestamo despues del plazo: $" << prestamo.saldoPrestamo << endl;
}

void solicitarPrestamo() {
    Prestamo prestamo;
    cout << "Ingrese el saldo inicial del prestamo: ";
    cin >> prestamo.saldoInicial;
    cout << "Ingrese la tasa de interes anual (en porcentaje): ";
    cin >> prestamo.tasaInteresAnual;
    cout << "Ingrese el plazo del prestamo (en meses): ";
    cin >> prestamo.plazoMeses;

    calcularSaldoPrestamo(prestamo);
    imprimirDetallePrestamo(prestamo);

    // Guardar los datos del préstamo en un archivo
    FILE *archivoPrestamos = fopen("prestamos.txt", "a");
    if (archivoPrestamos == NULL) {
        cout << "Error al abrir el archivo de prestamos." << endl;
        return;
    }

    fprintf(archivoPrestamos, "%.2f %.2f %d %.2f\n", prestamo.saldoInicial, prestamo.tasaInteresAnual, prestamo.plazoMeses, prestamo.saldoPrestamo);
    fclose(archivoPrestamos);
}

void mostrarPrestamos() {
    FILE *archivoPrestamos = fopen("prestamos.txt", "r");
    if (archivoPrestamos == NULL) {
        cout << "No se encontraron datos de prestamos." << endl;
        return;
    }

    Prestamo prestamo;
    cout << "Detalles de los prestamos registrados:" << endl;
    cout << "--------------------------------------" << endl;
    while (fscanf(archivoPrestamos, "%lf %lf %d %lf", &prestamo.saldoInicial, &prestamo.tasaInteresAnual, &prestamo.plazoMeses, &prestamo.saldoPrestamo) != EOF) {
        imprimirDetallePrestamo(prestamo);
        cout << "--------------------------------------" << endl;
    }
    fclose(archivoPrestamos);
}

//INICIO TRANSACCIONES
struct Transaccion {
    char fecha[11];
    char descripcion[50];
    double monto;
    char tipo; // 'D' para depósito, 'R' para retiro
};

void registrarTransaccion(const char* cuenta, const char* descripcion, double monto, char tipo) {
    Transaccion transaccion;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(transaccion.fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strncpy(transaccion.descripcion, descripcion, sizeof(transaccion.descripcion) - 1);
    transaccion.monto = monto;
    transaccion.tipo = tipo;

    FILE *archivoTransacciones = fopen("transacciones.txt", "a");
    if (archivoTransacciones == NULL) {
        printf("Error al abrir el archivo de transacciones.\n");
        return;
    }

    fprintf(archivoTransacciones, "%s %s %.2f %c\n", transaccion.fecha, transaccion.descripcion, transaccion.monto, transaccion.tipo);
    fclose(archivoTransacciones);
}

void mostrarTransacciones() {
    FILE *archivoTransacciones = fopen("transacciones.txt", "r");
    if (archivoTransacciones == NULL) {
        printf("No se encontraron transacciones.\n");
        return;
    }

    Transaccion transaccion;
    printf("Detalles de las transacciones registradas:\n");
    printf("------------------------------------------\n");
    while (fscanf(archivoTransacciones, "%s %s %lf %c", transaccion.fecha, transaccion.descripcion, &transaccion.monto, &transaccion.tipo) != EOF) {
        printf("Fecha: %s\n", transaccion.fecha);
        printf("Descripcion: %s\n", transaccion.descripcion);
        printf("Monto: %.2f\n", transaccion.monto);
        printf("Tipo: %c\n", transaccion.tipo);
        printf("------------------------------------------\n");
    }
    fclose(archivoTransacciones);
}

void main_menu() {
    int opcion;
    do {
        cout << "Menu Principal\n";
        cout << "1. Opciones de Cuenta\n";
        cout << "2. Opciones de Prestamo\n";
        cout << "3. Opciones de Transacciones\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int opcion_cuenta;
                do {
                    cout << "\nOpciones de Cuenta\n";
                    cout << "1. Crear cuenta de ahorro\n";
                    cout << "2. Actualizar cuenta\n";
                    cout << "3. Generar informe de cuenta\n";
                    cout << "0. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opcion_cuenta;

                    switch (opcion_cuenta) {
                        case 1:
                            cuenta_ahorro();
                            break;
                        case 2:
                            actualizar_cuenta("cuenta_ahorro.txt");
                            break;
                        case 3:
                            generar_informe("cuenta_ahorro.txt");
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion invalida. Intente nuevamente.\n";
                    }
                } while (opcion_cuenta != 0);
                break;
            }
            case 2: {
                int opcion_prestamo;
                do {
                    cout << "\nOpciones de Prestamo\n";
                    cout << "1. Solicitar prestamo\n";
                    cout << "2. Mostrar prestamos\n";
                    cout << "0. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opcion_prestamo;

                    switch (opcion_prestamo) {
                        case 1:
                            solicitarPrestamo();
                            break;
                        case 2:
                            mostrarPrestamos();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion invalida. Intente nuevamente.\n";
                    }
                } while (opcion_prestamo != 0);
                break;
            }
            case 3: {
                int opcion_transaccion;
                do {
                    cout << "\nOpciones de Transacciones\n";
                    cout << "1. Registrar transaccion\n";
                    cout << "2. Mostrar transacciones\n";
                    cout << "0. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opcion_transaccion;

                    switch (opcion_transaccion) {
                        case 1: {
                            char cuenta[13], descripcion[50];
                            double monto;
                            char tipo;
                            cout << "Ingrese el numero de cuenta: ";
                            cin >> cuenta;
                            cout << "Ingrese la descripcion: ";
                            cin.ignore();
                            cin.getline(descripcion, 50);
                            cout << "Ingrese el monto: ";
                            cin >> monto;
                            cout << "Ingrese el tipo de transaccion (D para deposito, R para retiro): ";
                            cin >> tipo;
                            registrarTransaccion(cuenta, descripcion, monto, tipo);
                            break;
                        }
                        case 2:
                            mostrarTransacciones();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion invalida. Intente nuevamente.\n";
                    }
                } while (opcion_transaccion != 0);
                break;
            }
            case 4:
                cout << "Gracias por usar nuestro sistema. Adios!\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}

int main() {
    main_menu();
    return 0;
}
