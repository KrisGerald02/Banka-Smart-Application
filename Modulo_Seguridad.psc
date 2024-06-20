// Archivo: M�dulo_Seguridad
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Mi�rcoles 12 de Junio de 2024
//Versi�n: 1.0
//Modificaciones: N/A

Algoritmo Modulo_Seguridad
	// Definir variables
	Definir longitudes, i Como Entero
	Definir contrasena Como Cadena
	
	// Pedir al usuario la longitud de la contrase�a
	Escribir "Introduce la longitud de la contrase�a (m�nimo 6 caracteres):"
	Leer longitudes
	
	// Validar que la longitud sea al menos 6 caracteres
	Mientras longitudes < 6 Hacer
		Escribir "La longitud debe ser de al menos 6 caracteres. Int�ntalo de nuevo:"
		Leer longitudes
	Fin Mientras
	
	// Generar la contrase�a
	contrasena = ""
	Para i = 1 Hasta longitudes Hacer
		contrasena = contrasena + ConvertirATexto(Aleatorio(0, 9))
	Fin Para
	
	// Mostrar la contrase�a generada
	Escribir "La contrase�a generada es: ", contrasena
FinAlgoritmo