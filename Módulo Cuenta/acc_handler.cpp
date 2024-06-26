#include<iostream>
#include<regex>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
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

void update(){
    
}
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
            do{
                cout << "Cuenta chiqui" << endl;
                cout << "1.Editar cuenta" << endl;
                cin >> opcion;

                switch (opcion)
                {
                case 1:
                    update();
                    break;
                
                default:
                    break;
                }
            }while(opcion != 1);
        } 
        else {
            cout << "Correo electronico incorrecto" << endl;
        }
    }
}


void log_in_menu(){
    int opcion1;
    do{
        cout << "Cuenta chiqui" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Volver al menu principal" << endl;
        cin >> opcion1;
                
        switch(opcion1)
        {
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


struct acc_handler
{
    string nombre, email, direccion, numero, f_nacimiento;
}cc;


void cuenta_chiqui() {
    int d_nacimiento, m_nacimiento, a_nacimiento;
    bool v_nombre = false, v_email = false, v_numero = false, v_fnacimiento = false;
    int mes_a[7] = {1, 3, 5, 7, 8, 10, 12};
    int mes_b[5] = {4, 6, 9, 11};

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();  
    getline(cin, cc.nombre);
    cout << endl;

    if(validacion_nombre(cc.nombre)){
        v_nombre = true;
        cout << "Nombre valido" << endl;
    }
    else{
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> cc.email;
    cout << endl;

    if(validacion_email(cc.email)){
        v_email = true;
        cout << "Correo electronico valido" << endl;
    }
    else{
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();  
    getline(cin, cc.direccion);
    cout << endl;

    cout << "Ingrese su numero de telefono" << endl;
    cout << "+505 ";
    cin >> cc.numero;

    if(validacion_numero(cc.numero)){
        v_numero = true;
        cout << "Numero de telefono valido" << endl;
    }
    else{
        cout << "Numero de telefono invalido" << endl;
    }

    cout << "Ingrese su fecha de nacimiento" << endl;
    cout << "Dia --> ";
    cin >> d_nacimiento;
    cout << "Mes --> ";
    cin >> m_nacimiento;
    cout << "Año --> ";
    cin >> a_nacimiento;

    bool fecha_valida = false;
    for(int i = 0; i < 7; i++){
        if(mes_a[i] == m_nacimiento && d_nacimiento > 0 && d_nacimiento <= 31){
            fecha_valida = true;
            break;
        }
    }

    if(!fecha_valida){
        for(int i = 0; i < 5; i++){
            if(mes_b[i] == m_nacimiento && d_nacimiento > 0 && d_nacimiento <= 30){
                fecha_valida = true;
                break;
            }
        }
    }

    if(m_nacimiento == 2 && d_nacimiento > 0 && d_nacimiento <= 28){
        fecha_valida = true;
    }

    if(!fecha_valida){
        cout << "Fecha de nacimiento invalida" << endl;
    }
    else{
        v_fnacimiento = true;
    }

    if(v_nombre && v_email && v_numero && v_fnacimiento){
        cout << "La cuenta ha sido creada con exito" << endl;

        if((ptrF= fopen("cuenta_chiqui","w"))== NULL){
            cout << "Error al abrir el archivo" << endl;
        }
        else{
            cout << "Sus datos han sido guardados exitosamente";
            fprintf(ptrF, "Correo: %s\n", cc.email.c_str());
            fprintf(ptrF, "Nombre: %s\n", cc.nombre.c_str());
            fprintf(ptrF, "Direccion: %s\n", cc.direccion.c_str());
            fprintf(ptrF, "Numero de telefono: %s\n", cc.numero.c_str());
            fprintf(ptrF, "Fecha de nacimiento: %02d/%02d/%04d\n", d_nacimiento, m_nacimiento, a_nacimiento);
            fclose(ptrF);
        }

        log_in_menu();
    }
    else{
        cout << "No se ha podido crear la cuenta" << endl;
    }
}


int main(){
    int opcion;

    do
    {
        cout << "Bienvenido a Banka-Smart" << endl;
        cout << "Elige una opcion" << endl;
        cout << "1) Crear cuenta de ahorro" << endl;
        cout << "2) Crear una cuenta chiqui" << endl;
        cout << "3) Crear una cuenta universitaria" << endl; 
        cout << "4) Salir" << endl;
        cin >> opcion;

        switch(opcion){
            case 1:
                break;
            case 2:
                cuenta_chiqui();
                break;
            case 3:
                break;
            case 4:
                cout << "Saliendo...";
                break;
            default:
                cout << "Elige una opción valida" << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
