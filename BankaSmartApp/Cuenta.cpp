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

