#include<iostream>
#include<regex>
using namespace std;

bool validacion_email(const string& email) {
    const regex patron_email(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, patron_email);
}

bool validacion_numero(const string& numero) {
    const regex patron_telefono(R"(\d{8}$)");
    return regex_match(numero, patron_telefono);
}

bool validacion_nombre(const string& nombre) {
    const regex patron_nombre(R"(^[A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+$)");
    return regex_match(nombre, patron_nombre);
}

void cuenta_chiqui() {
    string nombre, email, direccion, numero;
    int d_nacimiento, m_nacimiento, a_nacimiento;
    bool v_nombre = false, v_email = false, v_numero = false, v_fnacimiento = false;
    int mes_a[7] = {1, 3, 5, 7, 8, 10, 12};
    int mes_b[5] = {4, 6, 9, 11};

    cout << "Ingrese su nombre completo --> ";
    cin.ignore();  
    getline(cin, nombre);
    cout << endl;

    if(validacion_nombre(nombre)){
        v_nombre = true;
        cout << "Nombre valido" << endl;
    }
    else{
        cout << "Nombre invalido" << endl;
    }

    cout << "Ingrese su correo electronico --> ";
    cin >> email;
    cout << endl;

    if(validacion_email(email)){
        v_email = true;
        cout << "Correo electronico valido" << endl;
    }
    else{
        cout << "Correo electronico invalido" << endl;
    }

    cout << "Ingrese su direccion --> ";
    cin.ignore();  
    getline(cin, direccion);
    cout << endl;

    cout << "Ingrese su numero de telefono" << endl;
    cout << "+505 ";
    cin >> numero;

    if(validacion_numero(numero)){
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
        cout << "Crear cuenta de ahorro --> 1" << endl;
        cout << "Crear una cuenta chiqui--> 2" << endl;
        cout << "Crear una cuenta universitaria --> 3" << endl; 
        cout << "Salir --> 4" << endl;
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
