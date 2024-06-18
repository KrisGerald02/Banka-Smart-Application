// Archivo: M�dulo_Informes
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Mi�rcoles 12 de Junio de 2024
//Versi�n: 1.0
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
    
    // Obtener informaci�n de pr�stamos y transacciones
    Escribir "Ingrese la informaci�n de los pr�stamos y transacciones:"
    Mientras Verdadero Hacer
        Escribir "Ingrese P para pr�stamo, A para abono:"
        Leer tipo_transaccion
        
        Si tipo_transaccion = 'P' Entonces
            Escribir "Monto del pr�stamo:"
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
			Escribir "Resumen del m�dulo de pr�stamos y transacciones:"
			Escribir "Total de pr�stamos:", total_prestamos
			Escribir "Total de abonos:", total_abonos
			Escribir "Saldo actual:", saldo_actual
			Escribir "N�mero de pr�stamos:", num_prestamos
			Escribir "N�mero de abonos:", num_abonos
FinAlgoritmo