// Archivo: M�dulo_Prestamos
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Mi�rcoles 12 de Junio de 2024
//Versi�n: 1.0
//Modificaciones: N/A

Algoritmo Prestamos
Definir nombre, tipo_prestamo, cuenta Como Cadena
Definir monto, plazo, cuota Como Real
Definir saldo, interes Como Real
Definir aprobado Como Logico

Escribir "Bienvenido al Sistema de Pr�stamos del Banco"
Escribir "Ingrese su nombre:"
Leer nombre
Escribir "Ingrese el tipo de pr�stamo (personal, hipotecario, automotriz):"
Leer tipo_prestamo
Escribir "Ingrese el monto del pr�stamo:"
Leer monto
Escribir "Ingrese el plazo del pr�stamo en meses:"
Leer plazo
Escribir "Ingrese el n�mero de cuenta:"
Leer cuenta

// C�lculo de los datos del pr�stamo
Segun tipo_prestamo Hacer
    "personal":
        interes <- 0.15
    "hipotecario":
        interes <- 0.12
    "automotriz":
        interes <- 0.10
FinSegun
cuota <- monto * (interes / (1 - (1 + interes) ^ (-plazo)))
saldo <- monto

// Aprobaci�n del pr�stamo
Si monto <= 100000 Entonces
    aprobado <- Verdadero
    Escribir "�Pr�stamo aprobado!"
Sino
    aprobado <- Falso
    Escribir "Lo sentimos, su pr�stamo no ha sido aprobado."
FinSi

Si aprobado Entonces
    Escribir "Detalles del pr�stamo:"
    Escribir "Nombre: ", nombre
    Escribir "Tipo de pr�stamo: ", tipo_prestamo
    Escribir "Monto: ", monto
    Escribir "Plazo: ", plazo, " meses"
    Escribir "Tasa de inter�s: ", interes * 100, "%"
    Escribir "Cuota mensual: ", cuota
    Escribir "N�mero de cuenta: ", cuenta
FinSi
FinAlgoritmo
