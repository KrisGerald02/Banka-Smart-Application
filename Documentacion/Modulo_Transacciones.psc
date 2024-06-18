Algoritmo MenuPrincipal
    Definir opcion Como Entero
	
    Repetir
        Escribir "Seleccione una opci�n:"
        Escribir "1. Dep�sitos y Retiros de Dinero"
        Escribir "2. Transferencias Entre Cuentas"
        Escribir "3. Pagos de Facturas"
        Escribir "4. Datos del Servicio de Luz"
        Escribir "5. Datos del Servicio de Agua"
        Escribir "6. Datos del Servicio de Internet"
        Escribir "7. Pagos de Tarjetas de Cr�dito"
        Escribir "0. Salir"
        Leer opcion
		
        Segun opcion Hacer
            Caso 1:
                // Dep�sitos y Retiros de Dinero
                Definir tipo, monto, cuenta, fecha Como Caracter
                Escribir "Ingrese el tipo de transacci�n (dep�sito/retiro): "
                Leer tipo
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese la cuenta: "
                Leer cuenta
                Escribir "Ingrese la fecha (dd/mm/aaaa): "
                Leer fecha
                Escribir "Detalle de la transacci�n: Tipo: ", tipo, ", Monto: ", monto, ", Cuenta: ", cuenta, ", Fecha: ", fecha
            Caso 2:
                // Transferencias Entre Cuentas
                Definir origen, destino, monto, fecha Como Caracter
                Escribir "Ingrese la cuenta de origen: "
                Leer origen
                Escribir "Ingrese la cuenta de destino: "
                Leer destino
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese la fecha (dd/mm/aaaa): "
                Leer fecha
                Escribir "Detalle de la transferencia: Origen: ", origen, ", Destino: ", destino, ", Monto: ", monto, ", Fecha: ", fecha
          
            Caso 3:
                // Pagos de Facturas
                Definir servicio, monto, fecha, numeroCliente, saldoPendiente Como Caracter
                Escribir "Ingrese el servicio: "
                Leer servicio
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese la fecha: "
                Leer fecha
                Escribir "Ingrese el n�mero de cliente: "
                Leer numeroCliente
                Escribir "Ingrese el saldo pendiente: "
                Leer saldoPendiente
                Escribir "Detalle del pago: Servicio: ", servicio, ", Monto: ", monto, ", Fecha: ", fecha, ", N�mero de cliente: ", numeroCliente, ", Saldo pendiente: ", saldoPendiente
            Caso 4:
                // Datos del Servicio de Luz
                Definir numeroCliente, monto, saldoPendiente, fechaVencimiento Como Caracter
                Escribir "Ingrese el n�mero de cliente: "
                Leer numeroCliente
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese el saldo pendiente: "
                Leer saldoPendiente
                Escribir "Ingrese la fecha de vencimiento: "
                Leer fechaVencimiento
                Escribir "Datos del servicio de luz: N�mero de cliente: ", numeroCliente, ", Monto: ", monto, ", Saldo pendiente: ", saldoPendiente, ", Fecha de vencimiento: ", fechaVencimiento
            Caso 5:
                // Datos del Servicio de Agua
                Definir numeroCliente, monto, saldoPendiente, fechaVencimiento Como Caracter
                Escribir "Ingrese el n�mero de cliente: "
                Leer numeroCliente
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese el saldo pendiente: "
                Leer saldoPendiente
                Escribir "Ingrese la fecha de vencimiento: "
                Leer fechaVencimiento
                Escribir "Datos del servicio de agua: N�mero de cliente: ", numeroCliente, ", Monto: ", monto, ", Saldo pendiente: ", saldoPendiente, ", Fecha de vencimiento: ", fechaVencimiento
            Caso 6:
                // Datos del Servicio de Internet
                Definir numeroCliente, monto, saldoPendiente, fechaVencimiento Como Caracter
                Escribir "Ingrese el n�mero de cliente: "
                Leer numeroCliente
                Escribir "Ingrese el monto: "
                Leer monto
                Escribir "Ingrese el saldo pendiente: "
                Leer saldoPendiente
                Escribir "Ingrese la fecha de vencimiento: "
                Leer fechaVencimiento
                Escribir "Datos del servicio de internet: N�mero de cliente: ", numeroCliente, ", Monto: ", monto, ", Saldo pendiente: ", saldoPendiente, ", Fecha de vencimiento: ", fechaVencimiento
            Caso 7:
                // Pagos de Tarjetas de Cr�dito
                Definir limiteCredito, fechaVencimiento, numeroTarjeta, codigoSeguridad, historialCompras Como Caracter
                Escribir "Ingrese el l�mite de cr�dito: "
                Leer limiteCredito
                Escribir "Ingrese la fecha de vencimiento: "
                Leer fechaVencimiento
                Escribir "Ingrese el n�mero de tarjeta: "
                Leer numeroTarjeta
                Escribir "Ingrese el c�digo de seguridad: "
                Leer codigoSeguridad
                Escribir "Ingrese el historial de compras: "
                Leer historialCompras
                Escribir "Datos del pago de tarjeta de cr�dito: L�mite de cr�dito: ", limiteCredito, ", Fecha de vencimiento: ", fechaVencimiento, ", N�mero de tarjeta: ", numeroTarjeta, ", C�digo de seguridad: ", codigoSeguridad, ", Historial de compras: ", historialCompras
            Caso 0:
                Escribir "Saliendo del programa..."
            De Otro Modo:
                Escribir "Opci�n no v�lida. Intente nuevamente."
        FinSegun
    Hasta Que opcion = 0
FinAlgoritmo