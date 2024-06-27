#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <ctype.h>
#include "list.h"
#include "hashMap.h"


#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 300
//======================Configuración del terminal========================

struct termios original;

void save_original_terminal_mode() 
{
    tcgetattr(STDIN_FILENO, &original);
}

void restore_original_terminal_mode() 
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

void set_conio_terminal_mode() {
    struct termios newTermios;
    tcgetattr(STDIN_FILENO, &newTermios);
    newTermios.c_lflag &= ~ICANON; 
    newTermios.c_lflag &= ~ECHO;   
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
}

void hide_cursor() 
{
  printf("\033[?25l");
  fflush(stdout);
}
void show_cursor() 
{
  printf("\033[?25h");
  fflush(stdout);
}

char **leer_linea_csv(FILE *archivo, char separador) {
  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  char *ptr, *start;
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
    return NULL; // No hay más líneas para leer
  }

  // Eliminar salto de linea
  linea[strcspn(linea, "\n")] = '\0';

  ptr = start = linea;
  while (*ptr) {
    if (idx >= MAX_FIELDS - 1)
      break;

    if (*ptr == '\"') { // Inicio de un campo entrecomillado
      start = ++ptr;    // Saltar la comilla inicial
      while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador))
        ptr++;
    } else { // Campo sin comillas
      start = ptr;
      while (*ptr && *ptr != separador)
        ptr++;
    }

    if (*ptr) {
      *ptr = '\0'; // Reemplazar comilla final o separador por terminación
      ptr++;
      if (*ptr == separador)
        ptr++;
    }

    // Quitar comilla final si existe
    if (*(ptr - 2) == '\"') {
      *(ptr - 2) = '\0';
    }

    campos[idx++] = start;
  }

  campos[idx] = NULL; // Marcar el final del array
  return campos;
}
//========================================================================







//Jean Billiard  06/06/24
//=========================Bloque de estructura===========================
typedef struct          //Estrutura de datos del jugador
{
  int deseos;           //deseos para invocar personajes
  List* charac;        //lista de personajes obtenido
}account;

typedef struct{                //estructura de datos de los personajes
  char nombre[50];             //nombre del personaje
  int code;                    //codigo del personaje en el mapa
  int hp;                      //Puntos De Vida
  int atq;                     //Ataque
  int pde;                     //Puntos De Esquiva
  int tipo;                    //(1: fuego, 2: agua, 3: planta)
}campeon;

typedef struct               //estructura de datos de los enemigos
{
  char nombre[50];           //nombre del enemigo
  int hp;                    
  int atq;
  int tipo;                    //(1: fuego, 2: agua, 3: planta)
}enemigo;

typedef struct
{
  enemigo enemy;              //datos del enemigo
  bool defeat;                //indica si ha sido derrotado
  int type;                   //1. normal, 2.Elite, 3.Jefe
}enemyState;

//========================================================================

//========================================================================

//=========================Control del panel==============================
void limpiarPantalla() { system("clear"); } //Limpia la pantalla

void presioneParaContinuar() {              
  puts("Presione una tecla para continuar...");
  getchar(); // Espera a que el usuario presione una tecla
}

int is_equal_str(void *key1, void *key2) {           //comparar string
  return strcmp((char *)key1, (char *)key2) == 0;
}

int is_equal_int(void *key1, void *key2) {           //comparar int
  return *(int *)key1 == *(int *)key2;
}
//========================================================================
//Lei 08/06/24
//===========================Inicializaciones=============================
void inicializeBanners(HashMap* banners)     //inicializa los banners
{
  FILE *bannersFile = fopen("banners.csv", "r"); //Abrir el archivo banners.csv
  if(bannersFile == NULL)
  {
    printf("error\n");
    return;
  }
  char **campos;
  campos = leer_linea_csv(bannersFile, ',');  //saltar la primera linea

  //leer cada linea del archivo e insertando en el mapa
  while((campos = leer_linea_csv(bannersFile, ',')) != NULL)
    {
      campeon* candidato = (campeon*) malloc(sizeof(campeon));
      strcpy(candidato->nombre, campos[0]);
      candidato->code = atoi(campos[1]);
      candidato->hp = atoi(campos[2]);
      candidato->atq = atoi(campos[3]);
      candidato->pde = atoi(campos[4]);
      candidato->tipo = atoi(campos[5]);

      insertMap(banners, &candidato->code, candidato);
    }
  fclose(bannersFile);
  //======================================================================
}

void inicializeEnemies(List* enemies)      //inicializar los enemigos
{
  FILE *enemiesFile = fopen("enemies.csv", "r"); //Abrir el archivo enemies.csv
  if(enemiesFile == NULL)
  {
    printf("error\n");
    return;
  }
  char **campos;
  campos = leer_linea_csv(enemiesFile, ',');  //saltar la primera linea

  //leer cada linea del archivo e insertando en el mapa
  while((campos = leer_linea_csv(enemiesFile, ',')) != NULL)
    {
      enemyState* candidato = (enemyState*) malloc(sizeof(enemyState));
      strcpy(candidato->enemy.nombre, campos[0]);
      candidato->enemy.hp = atoi(campos[1]);
      candidato->enemy.atq = atoi(campos[2]);
      candidato->enemy.tipo = atoi(campos[3]);
      candidato->defeat = 0;
      candidato->type = atoi(campos[4]);
      pushBack(enemies, candidato);
    }
  fclose(enemiesFile);
  //======================================================================
}


void inicializeYo(account* yo)     //inicializar el jugador
{
  //yo = (account*)malloc(sizeof(account));    //reserva memoria
  yo->deseos = 5;                          //5 deseos gratis al comenzar
  yo->charac = createList();       //crea una lista vacía de personajes
}
//========================================================================

//============================Herramientas================================
int gachaComun()
{
  return rand()%14 + 1;
}

int invocar()
{
  int prob = rand()%999;
  if(prob == 0) return 15;
  else return gachaComun();
}

void mostrarNivel(enemyState* level)
{
  /*
  char estado[65];
  if (level->defeat == false) strcpy(estado, "   (No derrotado)");
  else strcpy(estado, "   (Derrotado)");
  */
  
  printf("-----------------------------------\n");
  printf("| %-*s|\n", 32, level->enemy.nombre);
  if(level->type == 2)printf("| %-*s|\n", 32, "(Elite)");
  else if(level->type == 3)printf("| %-*s|\n", 32, "(Jefe)");
  printf("-----------------------------------\n");
  printf("| Tipo     |");
  if(level->enemy.tipo == 1)
  {
    printf(" %-*s|\n", 21, "Fuego");
  }
  else if(level->enemy.tipo == 2)
  {
    printf(" %-*s|\n", 21, "Agua");
  }
  else if(level->enemy.tipo == 3)
  {
    printf(" %-*s|\n", 21, "Planta");
  }
  printf("| PV       | %-*i|\n", 21, level->enemy.hp);
  printf("| ATQ      | %-*i|\n", 21, level->enemy.atq);
  printf("-----------------------------------\n");
}

void selectEnemy(int nivel, enemyState* level)
{
  if(nivel == 1) printf("%35s", "Siguiente(D)");
  else if(nivel == 15) printf("Anteriores(A)");
  else printf("Anteriores(A)          Siguiente(D)");
  printf("\n");
}

void mostrarListaPersonajes(List* charac) //Jean Billiard  08/06/24
{
  puts("Campeones                  Salir(0)");
  puts("-----------------------------------");
  int numero = 0;
  for (campeon* current = firstList(charac); current != NULL; current = nextList(charac))
  {
    numero++;
    printf("| %d )", numero);
    printf(" %-*s|\n",28,current->nombre);
    printf("-----------------------------------\n");
  }
  if(numero == 0)
  {
    printf("| No tienes personajes            |\n");
    printf("-----------------------------------\n");
  }
}

void mostrarInfoProbalidades()                //Jose 09/06/24
{
  printf("**Detalles**\n");
  printf("Este gachapón contiene 14 campeones comunes y 1 campeón legendario.\n");
  printf("Las probalidades se desmuestra en la siguiente tabla:\n");
  printf("-----------------------------------\n");
  printf("|    Rareza     |   Probabilidad  |\n");
  printf("-----------------------------------\n");
  printf("|     Común     |      7.14 %%     |\n");
  printf("|   Legendario  |      0.10 %%     |\n");
  printf("-----------------------------------\n");
  printf("\n");
}

void mostrarPersonaje(int opcion, List* charac)
{
  campeon* current = firstList(charac);
  int avance = 1;
  while(avance < opcion && current != NULL)
  {
    current = nextList(charac);
    avance++;
  }
  if(current != NULL)
  {
    printf("-----------------------------------\n");
    printf("| %-*s|\n", 32,current->nombre);
    printf("-----------------------------------\n");

    printf("| Tipo     |");
    if(current->tipo == 1)
    {
      printf(" %-*s|\n", 21, "Fuego");
    }
    else if(current->tipo == 2)
    {
      printf(" %-*s|\n", 21, "Agua");
    }
    else if(current->tipo == 3)
    {
      printf(" %-*s|\n", 21, "Planta");
    }
    printf("| PV       | %-*i|\n", 21,current->hp);
    printf("| ATQ      | %-*i|\n", 21,current->atq);
    printf("| PDE      | %-*i|\n", 21,current->pde);
    printf("-----------------------------------\n");
    getchar();
    presioneParaContinuar();
  }
}

int unit(int data)
{
  if(data == 0) return 1;
  int count = 0;
  while(data != 0)
    {
      data /= 10;
      count++;
    }
  return count;
}

void info(campeon you, enemyState ene)
{
  int longitud = strlen(ene.enemy.nombre);
  printf(" ______________________________________   Abandonar(0)\n");
  printf("| %-*s%s |\n", 36 - longitud, "",ene.enemy.nombre);
  printf("| %-*sPV %d |\n", 33 - unit(ene.enemy.hp), "", ene.enemy.hp);
  printf("| %-*sATQ %d |\n", 32 - unit(ene.enemy.atq), "", ene.enemy.atq);
  printf("|                                      |  ATACAR(A)");
  printf("\n|-----------------VS-------------------|\n");
  printf("|                                      |  Esquivar(E)\n");
  printf("| %-*s|\n", 37, you.nombre);
  printf("| PV %-*d|\n", 34,you.hp);
  printf("| ATQ %-*d|\n", 33, you.atq);
  printf("| PDE %-*d|\n", 33, you.pde);
  printf(" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}

int atack(campeon you, enemyState ene, int i)
{
  switch(i)
  {
    case 1:
      if(you.tipo == 1)
      {
        if(ene.enemy.tipo == 1) return you.atq;
        else if(ene.enemy.tipo == 2) return you.atq / 2;
        else if(ene.enemy.tipo == 3) return you.atq * 2;
      }
      else if(you.tipo == 2)
      {
        if(ene.enemy.tipo == 1) return you.atq * 2;
        else if(ene.enemy.tipo == 2) return you.atq;
        else if(ene.enemy.tipo == 3) return you.atq / 2;
      }
      else if(you.tipo == 3)
      {
        if(ene.enemy.tipo == 1) return you.atq / 2;
        else if(ene.enemy.tipo == 2) return you.atq * 2;
        else if(ene.enemy.tipo == 3) return you.atq;
      }
      break;
    case 2:
      if(ene.enemy.tipo == 1)
      {
        if(you.tipo == 1) return ene.enemy.atq;
        else if(you.tipo == 2) return ene.enemy.atq / 2;
        else if(you.tipo == 3) return ene.enemy.atq * 2;
      }
      else if(ene.enemy.tipo == 2)
      {
        if(you.tipo == 1) return ene.enemy.atq * 2;
        else if(you.tipo == 2) return ene.enemy.atq;
        else if(you.tipo == 3) return ene.enemy.atq / 2;
      }
      else if(ene.enemy.tipo == 3)
      {
        if(you.tipo == 1) return ene.enemy.atq / 2;
        else if(you.tipo == 2) return ene.enemy.atq * 2;
        else if(you.tipo == 3) return ene.enemy.atq;
      }
      break;
  }
  return 0;
}

void batalla(campeon* you, enemyState* ene, int *deseos, int nivel)
{
  limpiarPantalla();
  bool fernanMode = false;
  bool teemode = false;
  bool slimeMode = false;
  char actionJugador;
  int enemyMove;
  int dmg;
  if(strcmp(ene->enemy.nombre, "Slime") == 0) slimeMode = true;
  if(strcmp(ene->enemy.nombre, "Teemo") == 0) teemode = true;
  if(strcmp(you->nombre, "Fernanfloo") == 0) fernanMode = true;
  campeon tempYou = *you;
  enemyState tempEne = *ene;
  int turno = 1;
  while(true)
    {
      srand(time(NULL));
      printf("%15sTurno: %d\n", "",turno);
      info(tempYou, tempEne);
      actionJugador = getchar();
      limpiarPantalla();
      if(actionJugador == '0') return;
      if(teemode)
      {
        if(turno % 3 == 0) enemyMove = 1;  // 1: atacar
        else enemyMove = 0;                // 0: esquivar
      }
      else
      {
        if(slimeMode) enemyMove = 1;
        else
        {
          int action = rand()%4;
          if(action != 0) enemyMove = 1;  // 1: atacar
          else enemyMove = 0;             // 0: esquivar
        }
      }
      
      switch(actionJugador)
        {
          case 'A':
          case 'a':
            if(tempYou.pde < you->pde) tempYou.pde++;
            if(enemyMove == 0)
            {
              printf("Enemigo esquivó tu ataque\n");
              printf("¡¡CONTRAATAQUE DEL ENEMIGO!!\n");
              if(teemode)
              {
                dmg = tempEne.enemy.atq;
              }
              else dmg = tempEne.enemy.atq / 2;
              printf("%s -%d PV\n", tempYou.nombre, dmg);
              tempYou.hp -= dmg;
              if(tempYou.hp <= 0)
                {
                  tempYou.hp = 0;
                  while(true)
                    {
                      printf("%15sTurno: %d\n", "",turno);
                      info(tempYou, tempEne);
                      printf("Perdiste!! Buen intento\n");
                      printf("Confirmar(0)");
                      if(getchar() == '0') return;
                      limpiarPantalla();
                    }
                  return;
                }
            }
            else
            {
              dmg = atack(tempYou, tempEne, 1); // indica quienes atacante
              if(dmg == tempYou.atq)
                printf("ATACAR!! %s -%d PV\n", tempEne.enemy.nombre, dmg);
              else if(dmg > tempYou.atq)
                printf("ATAQUE EFICAZ!! %s -%d PV\n", tempEne.enemy.nombre, dmg);
              else
                printf("ATAQUE INEFICAZ!! %s -%d PV\n", tempEne.enemy.nombre, dmg);
              tempEne.enemy.hp -= dmg;
              if(tempEne.enemy.hp <= 0)
              {
                tempEne.enemy.hp = 0;
                ene->defeat = true;
                while(true)
                  {
                    printf("%15sTurno: %d\n", "",turno);
                    info(tempYou, tempEne);
                    printf("Ganaste la partida!! FELICIDADES!!\n");
                    if(nivel < 5) printf("+1 Deseos\n");
                    else if (nivel >= 5 && nivel < 10) printf("+2 Deseos\n");
                    else if(nivel >= 10 && nivel < 15) printf("+3 Deseos\n");
                    else if(nivel == 15) printf("+5 Deseos\n");
                    printf("Confirmar(0)\n");
                    if(getchar() == '0')
                    {
                      if(nivel < 5) *deseos += 1;
                      else if (nivel >= 5 && nivel < 10) *deseos += 2;
                      else if(nivel >= 10 && nivel < 15) *deseos += 3;
                      else if(nivel == 15) *deseos += 5;
                      return;
                    }
                    limpiarPantalla();
                  }
              }
              printf("Luego...\n");
              dmg = atack(tempYou, tempEne, 2);
              if(dmg == tempEne.enemy.atq)
                printf("Enemigo te atacó!! %s -%d PV\n", tempYou.nombre, dmg);
              else if(dmg > tempEne.enemy.atq)
                printf("Enemigo te atacó de forma eficaz!! %s -%d PV\n", tempYou.nombre, dmg);
              else
                printf("Enemigo te atacó de forma ineficaz!! %s -%d PV\n", tempYou.nombre, dmg);
              tempYou.hp -= dmg;
              if(tempYou.hp <= 0)
              {
                tempYou.hp = 0;
                while(true)
                  {
                    printf("%15sTurno: %d\n", "",turno);
                    info(tempYou, tempEne);
                    printf("Perdiste!! Buen intento\n");
                    printf("Confirmar(0)");
                    if(getchar() == '0') return;
                    limpiarPantalla();
                  }
                return;
              }
            }
            break;
          case 'E':
          case 'e':
            if(tempYou.pde > 0)
            {
              tempYou.pde--;
              if(fernanMode)
              {
                printf("SIENTE MI FURIA!!\n");
                printf("%s -5 PV\n", tempEne.enemy.nombre);
                tempEne.enemy.hp -= 5;
              }
              else
              {
                printf("ESQUIVAR!!\n");
                if(enemyMove == 0) 
                  printf("El enemigo no atacó...\n");
                else if(enemyMove == 1)
                {
                  dmg = tempYou.atq / 2;
                  printf("Esquivaste el ataque del enemigo!!\n");
                  printf("CONTRAATAQUE!!\n");
                  printf("%s -%d PV\n", tempEne.enemy.nombre, dmg);
                  tempEne.enemy.hp -= dmg;
                }
              }
              if(tempEne.enemy.hp <= 0)
              {
                tempEne.enemy.hp = 0;
                ene->defeat = true;
                while(true)
                  {
                    printf("%15sTurno: %d\n", "",turno);
                    info(tempYou, tempEne);
                    printf("Ganaste la partida!! FELICIDADES!!\n");
                    if(nivel < 5) printf("+1 Deseos\n");
                    else if (nivel >= 5 && nivel < 10) printf("+2 Deseos\n");
                    else if(nivel >= 10 && nivel < 15) printf("+3 Deseos\n");
                    else if(nivel == 15) printf("+5 Deseos\n");
                    printf("Confirmar(0)\n");
                    if(getchar() == '0')
                    {
                      if(nivel < 5) *deseos += 1;
                      else if (nivel >= 5 && nivel < 10) *deseos += 2;
                      else if(nivel >= 10 && nivel < 15) *deseos += 3;
                      else if(nivel == 15) *deseos += 5;
                      return;
                    }
                    limpiarPantalla();
                  }
              }
            }
            else
            {
              printf("PDE Insuficiente\n");
              continue;
            }
            break;
          default:
            continue;
        }
      turno++;
    }
}

campeon* selectPersonaje(int opcion, List * charac)
{
  
  campeon* current = firstList(charac);
  campeon* next = nextList(charac);
  int avance = 1;
  while(avance < opcion && next != NULL)
  {
    current = next;
    next = nextList(charac);
    avance++;
  }
  return current;
}

void prepararCombate(account* yo, enemyState *level, int nivel)
{
  restore_original_terminal_mode();
  show_cursor();
  int opcion;
  while(true)
  {
    limpiarPantalla();
    printf("Elige un campeón para el combate\n\n");
    mostrarListaPersonajes(yo->charac);
    printf("Ingrese su opción(Enter para confirmar): ");
    if(scanf("%i", &opcion) != 1 || opcion < 0 || opcion > 15)
    {
      while(getchar() != '\n');
      printf("Opción inválida\n");
    }
    else if(opcion == 0) 
    {
      set_conio_terminal_mode();
      hide_cursor();
      return;
    }
    else if(opcion >= 1 && opcion <= 15 && selectPersonaje(opcion, yo->charac) != NULL)
    {
      while(getchar() != '\n');
      break;
    }
    
  }
  set_conio_terminal_mode();
  hide_cursor();
  printf("Seleccionaste a %s\n", selectPersonaje(opcion, yo->charac)->nombre);
  getchar();
  batalla(selectPersonaje(opcion, yo->charac), level, &yo->deseos, nivel);
}

//========================================================================

//==========================Funciones de menu=============================


void menuCombate(account* yo, List* enemies)
{
  limpiarPantalla();
  int nivel = 1;
  char opcion;
  enemyState *nivelActual = firstList(enemies);
  while(true)
  {
    printf("%*sNivel %i\n", 15, "", nivel);
    selectEnemy(nivel, nivelActual);
    mostrarNivel(nivelActual);
    printf("Salir(0)             Seleccionar(X)\n");
    scanf(" %c", &opcion);
    limpiarPantalla();
    if(opcion == '0') return;
    switch(opcion)
    {
      case 'D':
      case 'd':
        
        if(nivel <= 14)
        {
          if(nivelActual->defeat)
          {
            nivel++;
            nivelActual = nextList(enemies);
          }
          else
          {
            printf("Aún no has derrotado a %s\n", nivelActual->enemy.nombre);
          }
        }
        break;
      case 'A':
      case 'a':
        
        if(nivel >= 2)
        {
          nivel--;
          nivelActual = prevList(enemies);
        }
        break;
      case 'X':
      case 'x':
        prepararCombate(yo, nivelActual, nivel);
        limpiarPantalla();
        break;
    }
    if(nivel == 15 && nivelActual->defeat)
    {
      limpiarPantalla();
      printf("         ¡¡FELICIDADES!!\n");
      printf("Has derrotado a todos los enemigos\n");
      printf("      ¡¡Gracias por jugar!!\n");
      nivelActual->defeat = false;
      getchar();
      limpiarPantalla();
    }
  }
}

void menuSummon(account* yo, HashMap* banners)
{
  limpiarPantalla();
  int num;
  char opcion;
  while (1)
    {
      limpiarPantalla();
      printf("Deseos: %d                  Salir(0)\n", yo->deseos);
      printf("-----------------------------------\n");
      printf("|              Summon             |\n");
      printf("-----------------------------------\n");
      printf("Detalles(2)              Invocar(1)\n");
      scanf("%c",&opcion);
      switch(opcion)
        {
          case '1':
            limpiarPantalla();
            if(yo->deseos > 0)
            {
              yo->deseos -= 1;
              num = invocar();
              campeon *obtenido = searchMap(banners, &num)->value;
              if(num != 15)
              {
                printf("Obtuviste: %s\n", obtenido->nombre);
              }
              else
              {
                while(true)
                  {
                    limpiarPantalla();
                    printf("Obtuviste campeón LEGENDARIO: %s\n", obtenido->nombre);
                    printf("Confirmar(0)\n");
                    opcion = getchar();
                    if(opcion == '0') break;
                  }
              }
              if(!isIn(yo->charac, obtenido)) pushBack(yo->charac, obtenido);
              else printf("Ya tienes este personaje\n");
              presioneParaContinuar();
            }
            else
            {
              printf("No tienes deseos suficientes\n");
              getchar();
            }
            break;

          case '2':
            limpiarPantalla();
            mostrarInfoProbalidades();
            presioneParaContinuar();
            break;
          case '0':
            return;
        }
    }
}

void menuPersonajes(account* yo)
{
  restore_original_terminal_mode();
  int opcion;
  while(true)
  {
    limpiarPantalla();
    mostrarListaPersonajes(yo->charac);
    printf("Ingrese su opción(Enter para confirmar): ");
    if(scanf("%i", &opcion) != 1 || opcion < 0 || opcion > 15)
    {
      while(getchar() != '\n');
      printf("Opción inválida\n");
    }
    if(opcion == 0) return;

    limpiarPantalla();
    mostrarPersonaje(opcion, yo->charac);
  }
}

bool menuEliminar()
{
  limpiarPantalla();
  char opcion;
  bool notEliminar = false;
  while (!notEliminar)
    {
      printf("¿Estas seguro de querer eliminar la cuenta?\n");
      printf("          Si(S)         No(otras teclas)\n");
      scanf(" %c",&opcion);

      switch (opcion)
        {
          case 'S':
          case 's':
            printf("Eliminando cuenta y cerrando el juego\n");
            return true;
            break;
          default:
            return false;
        }
    }
  return false;
}
//========================================================================


void mostrarMenu()
{
  //Jean Billiard  06/06/24
  limpiarPantalla();
  puts("                    IDLE BATTLE");
  puts("                    1. Aventura");
  puts("                    2. Summon");
  puts("                    3. Campeones");
  puts("                    4. Borrar Mi cuenta");
}


int main(void) {
  //=================================
  save_original_terminal_mode();
  srand(time(NULL));
  set_conio_terminal_mode();
  hide_cursor();
  //=================================
  
  bool eliminar = false;
  HashMap* banners = createMap(22);
  List* enemies = createList();
  account* yo = (account*)malloc(sizeof(account));
  inicializeBanners(banners);
  inicializeEnemies(enemies);

  puts("         --------------------------------");
  puts("         |   Bienvenido a Idle battle   |");
  puts("         |  Apreta ENTER para Comenzar  |");
  puts("         --------------------------------");
  getchar();

  inicializeYo(yo);
  
  char opcion;
  do
  {
    mostrarMenu();
    opcion = getchar();
    switch(opcion)
    {
      case '1':
        menuCombate(yo, enemies);
        break;
      case '2':
        menuSummon(yo, banners);
        break;
      case '3':
        show_cursor();
        menuPersonajes(yo);
        set_conio_terminal_mode();
        hide_cursor();
        break;
      case '4':
        eliminar = menuEliminar();
        break;
    }
    limpiarPantalla();
  }while(!eliminar);
  return 0;
}




