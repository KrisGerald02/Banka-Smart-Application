// Archivo: Módulo_Seguridad
//Autor: Kristel Geraldine Villalta Porras
//Fecha: Miércoles 12 de Junio de 2024
//Versión: 1.0
//Modificaciones: N/A

Algoritmo Modulo_Seguridad
	// Definir variables
	Definir longitudes, i Como Entero
	Definir contrasena Como Cadena
	
	// Pedir al usuario la longitud de la contraseña
	Escribir "Introduce la longitud de la contraseña (mínimo 6 caracteres):"
	Leer longitudes
	
	// Validar que la longitud sea al menos 6 caracteres
	Mientras longitudes < 6 Hacer
		Escribir "La longitud debe ser de al menos 6 caracteres. Inténtalo de nuevo:"
		Leer longitudes
	Fin Mientras
	
	// Generar la contraseña
	contrasena = ""
	Para i = 1 Hasta longitudes Hacer
		contrasena = contrasena + ConvertirATexto(Aleatorio(0, 9))
	Fin Para
	
	// Mostrar la contraseña generada
	Escribir "La contraseña generada es: ", contrasena
FinAlgoritmo