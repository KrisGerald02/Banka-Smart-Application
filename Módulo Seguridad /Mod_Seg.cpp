#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Cuenta {
    char numero_cuenta[13];
    string contrasena;
};

string generar_contraseña(const string& nombre, int dia_nacimiento) {
    string primera_parte = nombre.substr(0, 3);
    string segunda_parte = to_string(dia_nacimiento);
    return primera_parte + segunda_parte;
}

bool iniciar_sesion_empleado(const string& numero_cuenta, const string& contrasena) {
    return (numero_cuenta == "empleado" && contrasena == "contraseña_empleado");
}

bool iniciar_sesion_cliente(const string& numero_cuenta, const string& contrasena) {
    ifstream archivo("clientes.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de clientes." << endl;
        return false;
    }

    Cuenta cuenta_cliente;
    bool encontrado = false;

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
    // Cambiar a "clear" si estás en un sistema Unix/Linux
    system("cls");
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
                cin.ignore(); // Limpiar el buffer de entrada antes de getline
                getline(cin, numero_cuenta);
                cout << "Ingrese la contrasena: ";
                getline(cin, contrasena);

                if (iniciar_sesion_empleado(numero_cuenta, contrasena)) {
                    cout << "Inicio de sesion exitoso como empleado." << endl;
                    // Acciones de empleados
                } else {
                    cout << "Error: Numero de cuenta o contrasena incorrectos." << endl;
                }
                break;
            }
            case 2: {
                string numero_cuenta, contrasena;
                cout << "Inicio de sesion para clientes" << endl;
                cout << "Ingrese el numero de cuenta: ";
                cin.ignore(); // Limpiar el buffer de entrada antes de getline
                getline(cin, numero_cuenta);
                cout << "Ingrese la contrasena: ";
                getline(cin, contrasena);

                if (iniciar_sesion_cliente(numero_cuenta, contrasena)) {
                    cout << "Inicio de sesion exitoso como cliente." << endl;
                    // Acciones de clientes
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
