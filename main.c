#include <stdio.h>

void mostrarMenu()
{
  puts("Ingresa tu opción:\n");
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
    scanf("%c", &opcion);
    switch(opcion)
    {
      case '1':
        printf("peleando");
        break;
      case '2':
        printf("summoneando");
        break;
      case '3':
        printf("personajes");
        break;
      case '4':
        printf("eliminando cuenta");
        break;
    }
  }while(opcion != 4);
  
}