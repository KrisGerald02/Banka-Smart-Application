#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iomanip>

using namespace std;


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
