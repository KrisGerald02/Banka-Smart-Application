#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para generar una contraseña aleatoria
void generarContrasena(char* contrasena, int longitud) {
    const char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    int numCaracteres = sizeof(caracteres) - 1;
    
    srand(time(0)); // Inicializar la semilla para la aleatoriedad
    
    for (int i = 0; i < longitud; ++i) {
        contrasena[i] = caracteres[rand() % numCaracteres];
    }
    
    contrasena[longitud] = '\0'; // Añadir el carácter nulo al final
}

int main() {
    char usuario[50];
    int longitudContrasena = 12;
    char contrasena[longitudContrasena + 1];
    
    printf("Introduce el nombre del usuario: ");
    scanf("%49s", usuario);
    
    generarContrasena(contrasena, longitudContrasena);
    
    printf("Usuario: %s\n", usuario);
    printf("Contrasena generada: %s\n", contrasena);
    
    return 0;
}
