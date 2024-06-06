#include <stdio.h>
#include <stdlib.h>

typedef struct{
  char nombre[50];
  int atq; //Ataque
  int pde; //Puntos De Esquiva
  int hp; //Puntos De Vida
  int tipo; //(1: fuego, 2: agua, 3: planta)
}Personajes;

void limpiarPantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void mostrarMenu()
{
  limpiarPantalla();
  puts("Ingresa tu opción:");
  puts("1. Pelear");
  puts("2. Summon");
  puts("3. Personajes");
  puts("4. Borrar Cuenta Definitivamente (No se puede deshacer)");
}


int main(void) {
  char opcion;
  do
  {
    mostrarMenu();
    scanf(" %c", &opcion);
    getchar();
    switch(opcion)
    {
      case '1':
        printf("peleando\n");
        break;
      case '2':
        printf("summoneando\n");
        break;
      case '3':
        printf("personajes\n");
        break;
      case '4':
        printf("eliminando cuenta\n");
        break;
    }
    printf("Presiona enter para continuar...");
    getchar();
  }while(opcion != '4');
  return 0;
}