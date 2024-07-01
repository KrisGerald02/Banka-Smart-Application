#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>

using namespace std;

FILE *ptrF;

bool validacion_email(const string& email) {
    const regex patron_email(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, patron_email);
}

bool validacion_numero(const string& numero) {
    const regex patron_telefono(R"(\d{8}$)");
    return regex_match(numero, patron_telefono);
}

bool validacion_nombre(const string& nombre) {
    const regex patron_nombre(R"(^[A-Z][a-z]*(\s[A-Z][a-z]*)*$)");
    return regex_match(nombre, patron_nombre);
}

string generar_numero_cuenta() {
    string numero_cuenta;
    for (int i = 0; i < 12; ++i) {
        numero_cuenta += to_string(rand() % 10);
    }
    return numero_cuenta;
}

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
            cout << "\n¿Qué desea actualizar?: ";
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
                    break;
                case 2:
                    cout << "\nIntroduzca el nuevo correo electronico: ";
                    cin >> email1;
                    strcpy(email, email1);
                    break;
                case 3:
                    cout << "\nIntroduzca la nueva direccion: ";
                    cin.ignore();
                    cin.getline(direccion1, 100);
                    strcpy(direccion, direccion1);
                    break;
                case 4:
                    cout << "\nIntroduzca el nuevo numero de telefono: ";
                    cin >> numero1;
                    strcpy(numero, numero1);
                    break;
                case 5:
                    cout << "\nIntroduzca el nuevo saldo inicial: ";
                    cin >> saldo_inicial1;
                    saldo_inicial = saldo_inicial1;
                    break;
                default:
                    break;
            }
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

void log_in();
void log_in_menu();
void cuenta_ahorro();
void cuenta_chiqui();
void cuenta_universitaria();

void log_in() {
    string email, email_v;
    int opcion;
    cout << "Ingrese su correo electronico --> ";
    cin >> email;

    if ((ptrF = fopen("cuenta_chiqui", "r")) == NULL) {
        cout << "Error al abrir el archivo" << endl;
    } else {
        char buffer[256];
        bool email_found = false;
        
        while (fgets(buffer, sizeof(buffer), ptrF) != NULL) {
            string line(buffer);
            if (line.find("Correo: ") == 0) {
                email_v = line.substr(8); 
                email_v.erase(email_v.find_last_not_of("\n") + 1); 
                if (email == email_v) {
                    email_found = true;
                    break;
                }
            }
        }

        fclose(ptrF);

        if (email_found) {
            cout << "Inicio de sesion exitosa" << endl;
            do {
                cout << "Cuenta chiqui" << endl;
                cout << "1. Editar cuenta" << endl;
                cout << "2. Salir" << endl;
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        actualizar_cuenta("cuenta_chiqui");
                        break;
                    case 2:
                        break;
                    default:
                        break;
                }
            } while (opcion != 2);
        } else {
            cout << "Correo electronico incorrecto" << endl;
        }
    }
}

void log_in_menu() {
    int opcion1;
    do {
        cout << "Cuenta chiqui" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Volver al menu principal" << endl;
        cin >> opcion1;
                
        switch(opcion1) {
            case 1:
                log_in();
                break;
            case 2:
                break;
            default:
                break;
        }
    } while(opcion1 != 2);
}

struct acc_handler {
    string nombre, email, direccion, numero, f_nacimiento;
} cc;

void cuenta_ahorro() {
    double saldo_inicial;
    bool v_nombre = false, v_email = false, v_numero = false, v_saldo = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    getline(cin, cc.nombre);
    cout << endl;

    if(validacion_nombre(cc.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cc.email;
    cout << endl;

    if(validacion_email(cc.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    getline(cin, cc.direccion);
    cout << endl;

    cout << "Ingrese su numero de telefono" << endl;
    cout << "+505 ";
    cin >> cc.numero;

    if(validacion_numero(cc.numero)) {
        v_numero = true;
        cout << "Numero de telefono valido" << endl;
    } else {
        cout << "Numero de telefono invalido" << endl;
    }

    cout << "Ingrese el saldo inicial de la cuenta --> ";
    cin >> saldo_inicial;

    if(saldo_inicial > 0) {
        v_saldo = true;
        cout << "Saldo inicial valido" << endl;
    } else {
        cout << "Saldo inicial invalido" << endl;
    }

    if(v_nombre && v_email && v_numero && v_saldo) {
        cout << "La cuenta de ahorro ha sido creada con exito" << endl;

        string numero_cuenta = generar_numero_cuenta();
        cout << "Su numero de cuenta es: " << numero_cuenta << endl;

        if((ptrF = fopen("cuenta_ahorro", "w")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            cout << "Sus datos han sido guardados exitosamente" << endl;
            fprintf(ptrF, "Numero de cuenta: %s\n", numero_cuenta.c_str());
            fprintf(ptrF, "Correo: %s\n", cc.email.c_str());
            fprintf(ptrF, "Nombre: %s\n", cc.nombre.c_str());
            fprintf(ptrF, "Direccion: %s\n", cc.direccion.c_str());
            fprintf(ptrF, "Numero de telefono: %s\n", cc.numero.c_str());
            fprintf(ptrF, "Saldo inicial: %.2f\n", saldo_inicial);
            fclose(ptrF);
        }
    } else {
        cout << "No se ha podido crear la cuenta de ahorro" << endl;
    }
}

void cuenta_chiqui() {
    int d_nacimiento, m_nacimiento, a_nacimiento;
    bool v_nombre = false, v_email = false, v_numero = false, v_fnacimiento = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    getline(cin, cc.nombre);
    cout << endl;

    if(validacion_nombre(cc.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cc.email;
    cout << endl;

    if(validacion_email(cc.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    getline(cin, cc.direccion);
    cout << endl;

    cout << "Ingrese su numero de telefono" << endl;
    cout << "+505 ";
    cin >> cc.numero;

    if(validacion_numero(cc.numero)) {
        v_numero = true;
        cout << "Numero de telefono valido" << endl;
    } else {
        cout << "Numero de telefono invalido" << endl;
    }

    cout << "Ingrese su fecha de nacimiento (dd mm yyyy) --> ";
    cin >> d_nacimiento >> m_nacimiento >> a_nacimiento;
    if((d_nacimiento >= 1 && d_nacimiento <= 31) && (m_nacimiento >= 1 && m_nacimiento <= 12) && (a_nacimiento >= 1900 && a_nacimiento <= 2100)) {
        v_fnacimiento = true;
        cout << "Fecha de nacimiento valida" << endl;
    } else {
        cout << "Fecha de nacimiento invalida" << endl;
    }

    if(v_nombre && v_email && v_numero && v_fnacimiento) {
        cout << "La cuenta chiqui ha sido creada con exito" << endl;

        string numero_cuenta = generar_numero_cuenta();
        cout << "Su numero de cuenta es: " << numero_cuenta << endl;

        if((ptrF = fopen("cuenta_chiqui", "w")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            cout << "Sus datos han sido guardados exitosamente" << endl;
            fprintf(ptrF, "Numero de cuenta: %s\n", numero_cuenta.c_str());
            fprintf(ptrF, "Correo: %s\n", cc.email.c_str());
            fprintf(ptrF, "Nombre: %s\n", cc.nombre.c_str());
            fprintf(ptrF, "Direccion: %s\n", cc.direccion.c_str());
            fprintf(ptrF, "Numero de telefono: %s\n", cc.numero.c_str());
            fprintf(ptrF, "Fecha de nacimiento: %02d/%02d/%04d\n", d_nacimiento, m_nacimiento, a_nacimiento);
            fclose(ptrF);
        }

        log_in_menu();
    } else {
        cout << "No se ha podido crear la cuenta" << endl;
    }
}

void cuenta_universitaria() {
    string universidad, carrera;
    bool v_nombre = false, v_email = false, v_numero = false, v_universidad = false, v_carrera = false;

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();
    getline(cin, cc.nombre);
    cout << endl;

    if(validacion_nombre(cc.nombre)) {
        v_nombre = true;
        cout << "Nombre valido" << endl;
    } else {
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cc.email;
    cout << endl;

    if(validacion_email(cc.email)) {
        v_email = true;
        cout << "Correo electronico valido" << endl;
    } else {
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();
    getline(cin, cc.direccion);
    cout << endl;

    cout << "Ingrese su numero de telefono" << endl;
    cout << "+505 ";
    cin >> cc.numero;

    if(validacion_numero(cc.numero)) {
        v_numero = true;
        cout << "Numero de telefono valido" << endl;
    } else {
        cout << "Numero de telefono invalido" << endl;
    }

    cout << "Ingrese la universidad a la que asiste --> ";
    cin.ignore();
    getline(cin, universidad);
    cout << endl;

    if(!universidad.empty()) {
        v_universidad = true;
        cout << "Nombre de universidad valido" << endl;
    } else {
        cout << "Nombre de universidad invalido" << endl;
    }

    cout << "Ingrese la carrera que estudia --> ";
    getline(cin, carrera);
    cout << endl;

    if(!carrera.empty()) {
        v_carrera = true;
        cout << "Nombre de carrera valido" << endl;
    } else {
        cout << "Nombre de carrera invalido" << endl;
    }

    if(v_nombre && v_email && v_numero && v_universidad && v_carrera) {
        cout << "La cuenta universitaria ha sido creada con exito" << endl;

        string numero_cuenta = generar_numero_cuenta();
        cout << "Su numero de cuenta es: " << numero_cuenta << endl;

        if((ptrF = fopen("cuenta_universitaria", "w")) == NULL) {
            cout << "Error al abrir el archivo" << endl;
        } else {
            cout << "Sus datos han sido guardados exitosamente" << endl;
            fprintf(ptrF, "Numero de cuenta: %s\n", numero_cuenta.c_str());
            fprintf(ptrF, "Correo: %s\n", cc.email.c_str());
            fprintf(ptrF, "Nombre: %s\n", cc.nombre.c_str());
            fprintf(ptrF, "Direccion: %s\n", cc.direccion.c_str());
            fprintf(ptrF, "Numero de telefono: %s\n", cc.numero.c_str());
            fprintf(ptrF, "Universidad: %s\n", universidad.c_str());
            fprintf(ptrF, "Carrera: %s\n", carrera.c_str());
            fclose(ptrF);
        }
    } else {
        cout << "No se ha podido crear la cuenta universitaria" << endl;
    }
}

int main() {
    srand(time(0)); // Seed for random number generation
    int opcion;

    do {
        cout << "Bienvenido a Banka-Smart" << endl;
        cout << "Elige una opcion" << endl;
        cout << "1) Crear cuenta de ahorro" << endl;
        cout << "2) Crear una cuenta chiqui" << endl;
        cout << "3) Crear una cuenta universitaria" << endl;
        cout << "4) Modificar cuenta existente" << endl;
        cout << "5) Salir" << endl;
        cin >> opcion;

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
                int sub_opcion;
                cout << "Seleccione el tipo de cuenta a modificar:" << endl;
                cout << "1) Cuenta de ahorro" << endl;
                cout << "2) Cuenta chiqui" << endl;
                cout << "3) Cuenta universitaria" << endl;
                cin >> sub_opcion;
                
                switch (sub_opcion) {
                    case 1:
                        actualizar_cuenta("cuenta_ahorro");
                        break;
                    case 2:
                        actualizar_cuenta("cuenta_chiqui");
                        break;
                    case 3:
                        actualizar_cuenta("cuenta_universitaria");
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        break;
                }
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Elige una opción valida" << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}
