// Archivo: M�dulo_Cuentas
//Autor: William Alberto Torres Moreira
//Fecha: Mi�rcoles 12 de Junio de 2024
//Versi�n: 1.0
//Modificaciones: N/A

SubProceso validacion_cuenta
    Definir tipo_cuenta Como Cadena
    Escribir "Ingrese el tipo de cuenta: "
    Leer tipo_cuenta
    Si tipo_cuenta = "Cuenta de ahorro" o tipo_cuenta = "cuenta chiqui" o tipo_cuenta = "cuenta universitaria" Entonces
        Escribir "El tipo de cuenta es v�lido"
    SiNo
        Escribir "El tipo de cuenta no es v�lido"
    FinSi
FinSubProceso

SubProceso gestion_inf_personal
    Definir nombre, direccion, correo_electronico Como Cadena
    Definir telefono, fecha_nacimiento Como Entero
    Escribir "Ingrese el nombre: "
    Leer nombre
    Escribir "Ingrese la direcci�n: "
    Leer direccion
    Escribir "Ingrese el tel�fono: "
    Leer telefono
    Escribir "Ingrese el correo electr�nico: "
    Leer correo_electronico
    Escribir "Ingrese la fecha de nacimiento: "
    Leer fecha_nacimiento
    Si nombre = "" o direccion = "" o telefono = 0 o correo_electronico = "" o fecha_nacimiento = 0 Entonces
        Escribir "Los datos del usuario no son v�lidos"
    SiNo
        Escribir "Los datos del usuario son v�lidos"
    FinSi
FinSubProceso

SubProceso cierre_cuenta
    Definir cuenta_existe Como Logico
    Escribir "Ingrese si la cuenta existe (VERDADERO/FALSO): "
    Leer cuenta_existe
    Si cuenta_existe Entonces
        Escribir "La cuenta se puede cerrar"
    SiNo
        Escribir "La cuenta no se puede cerrar"
    FinSi
FinSubProceso

SubProceso actualizacion_datos
    Definir cuenta_existe Como Logico
    Escribir "Ingrese si la cuenta existe (VERDADERO/FALSO): "
    Leer cuenta_existe
    Si cuenta_existe Entonces
        Escribir "Los datos de la cuenta se pueden actualizar"
    SiNo
        Escribir "Los datos de la cuenta no se pueden actualizar"
    FinSi
FinSubProceso

SubProceso retiro_dinero
    Definir retirar_dinero Como Real
    Escribir "Ingrese el monto a retirar: "
    Leer retirar_dinero
    Si retirar_dinero > 0 Entonces
        Escribir "El monto a retirar es v�lido"
    SiNo
        Escribir "El monto a retirar no es v�lido"
    FinSi
FinSubProceso

SubProceso maestro_cliente
    Definir registro_cliente, verificacion_id Como Logico
    Definir asignacion_num_cuenta Como Cadena
    Escribir "Ingrese si el registro del cliente es correcto (VERDADERO/FALSO): "
    Leer registro_cliente
    Escribir "Ingrese si la identificaci�n es v�lida (VERDADERO/FALSO): "
    Leer verificacion_id
    Escribir "Ingrese el n�mero de cuenta asignado: "
    Leer asignacion_num_cuenta
    Si registro_cliente Y verificacion_id Y asignacion_num_cuenta <> "" Entonces
        Escribir "El maestro cliente es v�lido"
    SiNo
        Escribir "El maestro cliente no es v�lido"
    FinSi
FinSubProceso

Proceso Principal
    validacion_cuenta
    gestion_inf_personal
    cierre_cuenta
    actualizacion_datos
    retiro_dinero
    maestro_cliente
FinProceso

