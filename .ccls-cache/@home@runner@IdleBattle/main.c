#include <stdio.h>

void mostrarMenu()
{
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
    fflush(stdin);
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
  }while(opcion != '4');
  return 0;
}