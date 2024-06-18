// Archivo: Módulo_Informes
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Miércoles 12 de Junio de 2024
//Versión: 1.0
//Modificaciones: N/A

Algoritmo ResumenModuloPrestamosTransacciones
    Definir total_prestamos, total_abonos, saldo_actual Como Real
    Definir num_prestamos, num_abonos Como Entero
	Definir tipo_transaccion como cadena
    
    // Inicializar variables
    total_prestamos <- 0
    total_abonos <- 0
    saldo_actual <- 0
    num_prestamos <- 0
    num_abonos <- 0
    
    // Obtener información de préstamos y transacciones
    Escribir "Ingrese la información de los préstamos y transacciones:"
    Mientras Verdadero Hacer
        Escribir "Ingrese P para préstamo, A para abono:"
        Leer tipo_transaccion
        
        Si tipo_transaccion = 'P' Entonces
            Escribir "Monto del préstamo:"
            Leer monto_prestamo
            total_prestamos <- total_prestamos + monto_prestamo
            num_prestamos <- num_prestamos + 1
            saldo_actual <- saldo_actual + monto_prestamo
			FinSi
		Si tipo_transaccion = 'A' Entonces
				Escribir "Monto del abono:"
				Leer monto_abono
				total_abonos <- total_abonos + monto_abono
				num_abonos <- num_abonos + 1
				saldo_actual <- saldo_actual - monto_abono
			FinSi
	FinMientras
			
			// Mostrar resumen
			Escribir "Resumen del módulo de préstamos y transacciones:"
			Escribir "Total de préstamos:", total_prestamos
			Escribir "Total de abonos:", total_abonos
			Escribir "Saldo actual:", saldo_actual
			Escribir "Número de préstamos:", num_prestamos
			Escribir "Número de abonos:", num_abonos
FinAlgoritmo