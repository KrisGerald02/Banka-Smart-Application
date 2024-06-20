// Archivo: Módulo_Prestamos
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Miércoles 12 de Junio de 2024
//Versión: 1.0
//Modificaciones: N/A

Algoritmo Prestamos
Definir nombre, tipo_prestamo, cuenta Como Cadena
Definir monto, plazo, cuota Como Real
Definir saldo, interes Como Real
Definir aprobado Como Logico

Escribir "Bienvenido al Sistema de Préstamos del Banco"
Escribir "Ingrese su nombre:"
Leer nombre
Escribir "Ingrese el tipo de préstamo (personal, hipotecario, automotriz):"
Leer tipo_prestamo
Escribir "Ingrese el monto del préstamo:"
Leer monto
Escribir "Ingrese el plazo del préstamo en meses:"
Leer plazo
Escribir "Ingrese el número de cuenta:"
Leer cuenta

// Cálculo de los datos del préstamo
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

// Aprobación del préstamo
Si monto <= 100000 Entonces
    aprobado <- Verdadero
    Escribir "¡Préstamo aprobado!"
Sino
    aprobado <- Falso
    Escribir "Lo sentimos, su préstamo no ha sido aprobado."
FinSi

Si aprobado Entonces
    Escribir "Detalles del préstamo:"
    Escribir "Nombre: ", nombre
    Escribir "Tipo de préstamo: ", tipo_prestamo
    Escribir "Monto: ", monto
    Escribir "Plazo: ", plazo, " meses"
    Escribir "Tasa de interés: ", interes * 100, "%"
    Escribir "Cuota mensual: ", cuota
    Escribir "Número de cuenta: ", cuenta
FinSi
FinAlgoritmo
