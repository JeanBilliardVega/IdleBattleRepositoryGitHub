#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "hashMap.h"
#include <time.h>

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
  //========================inicializar cada personaje====================
  campeon* charizard = (campeon*)malloc(sizeof(campeon));
  strcpy(charizard->nombre, "Charizard");
  charizard->code = 1;
  charizard->hp = 60;
  charizard->atq = 3;
  charizard->pde = 2;
  charizard->tipo = 1;

  campeon* goku = (campeon*)malloc(sizeof(campeon));
  strcpy(goku->nombre, "Goku");
  goku->code = 2;
  goku->hp = 50;
  goku->atq = 4;
  goku->pde = 2;
  goku->tipo = 1;

  campeon* hutao = (campeon*)malloc(sizeof(campeon));
  strcpy(hutao->nombre, "Hutao");
  hutao->code = 3;
  hutao->hp = 30;
  hutao->atq = 6;
  hutao->pde = 1;
  hutao->tipo = 1;

  campeon* escanor = (campeon*)malloc(sizeof(campeon));
  strcpy(escanor->nombre, "Escanor");
  escanor->code = 4;
  escanor->hp = 80;
  escanor->atq = 4;
  escanor->pde = 0;
  escanor->tipo = 1;

  campeon* sieteDeMarzo = (campeon*)malloc(sizeof(campeon));
  strcpy(sieteDeMarzo->nombre, "Siete de marzo");
  sieteDeMarzo->code = 5;
  sieteDeMarzo->hp = 30;
  sieteDeMarzo->atq = 3;
  sieteDeMarzo->pde = 5;
  sieteDeMarzo->tipo = 2;

  campeon* ellie = (campeon*)malloc(sizeof(campeon));
  strcpy(ellie->nombre, "Ellie");
  ellie->code = 6;
  ellie->hp = 30;
  ellie->atq = 3;
  ellie->pde = 4;
  ellie->tipo = 3;

  campeon* leonKennedy = (campeon*)malloc(sizeof(campeon));
  strcpy(leonKennedy->nombre, "Leon Kennedy");
  leonKennedy->code = 7;
  leonKennedy->hp = 50;
  leonKennedy->atq = 3;
  leonKennedy->pde = 2;
  leonKennedy->tipo = 2;

  campeon* karma = (campeon*)malloc(sizeof(campeon));
  strcpy(karma->nombre, "Karma");
  karma->code = 8;
  karma->hp = 40;
  karma->atq = 3;
  karma->pde = 2;
  karma->tipo = 3;

  campeon* hatsuneMiku = (campeon*)malloc(sizeof(campeon));
  strcpy(hatsuneMiku->nombre, "Hatsune Miku");
  hatsuneMiku->code = 9;
  hatsuneMiku->hp = 70;
  hatsuneMiku->atq = 2;
  hatsuneMiku->pde = 5;
  hatsuneMiku->tipo = 2;

  campeon* jake = (campeon*)malloc(sizeof(campeon));
  strcpy(jake->nombre, "Jake");
  jake->code = 10;
  jake->hp = 80;
  jake->atq = 4;
  jake->pde = 0;
  jake->tipo = 3;

  campeon* bobEsponja = (campeon*)malloc(sizeof(campeon));
  strcpy(bobEsponja->nombre, "Bob Esponja");
  bobEsponja->code = 11;
  bobEsponja->hp = 30;
  bobEsponja->atq = 3;
  bobEsponja->pde = 6;
  bobEsponja->tipo = 2;

  campeon* arale = (campeon*)malloc(sizeof(campeon));
  strcpy(arale->nombre, "Arale");
  arale->code = 12;
  arale->hp = 5;
  arale->atq = 20;
  arale->pde = 0;
  arale->tipo = 1;

  campeon* fernanfloo = (campeon*)malloc(sizeof(campeon));
  strcpy(fernanfloo->nombre, "Fernanfloo");
  fernanfloo->code = 13;
  fernanfloo->hp = 1;
  fernanfloo->atq = 0;
  fernanfloo->pde = 5;
  fernanfloo->tipo = 1;

  campeon* deku = (campeon*)malloc(sizeof(campeon));
  strcpy(deku->nombre, "Deku");
  deku->code = 14;
  deku->hp = 40;
  deku->atq = 4;
  deku->pde = 4;
  deku->tipo = 1;

  campeon* dios = (campeon*)malloc(sizeof(campeon));
  strcpy(dios->nombre, "Dios");
  dios->code = 15;
  dios->hp = 999;
  dios->atq = 999;
  dios->pde = 0;
  dios->tipo = 1;
  //======================================================================

  //=================insertar cada personaje en el mapa===================
  insertMap(banners, &charizard->code, charizard);
  insertMap(banners, &goku->code, goku);
  insertMap(banners, &hutao->code, hutao);
  insertMap(banners, &escanor->code, escanor);
  insertMap(banners, &sieteDeMarzo->code, sieteDeMarzo);
  insertMap(banners, &ellie->code, ellie);
  insertMap(banners, &leonKennedy->code, leonKennedy);
  insertMap(banners, &karma->code, karma);
  insertMap(banners, &hatsuneMiku->code, hatsuneMiku);
  insertMap(banners, &jake->code, jake);
  insertMap(banners, &bobEsponja->code, bobEsponja);
  insertMap(banners, &arale->code, arale);
  insertMap(banners, &fernanfloo->code, fernanfloo);
  insertMap(banners, &deku->code, deku);
  insertMap(banners, &dios->code, dios);
  //======================================================================
}
//Lei  08/06/24
void inicializeEnemies(List* enemies)      //inicializar los enemigos
{
  //========================inicializar cada enemigo======================
  enemyState* slime = (enemyState*)malloc(sizeof(enemyState));
  slime->defeat = false;
  slime->type = 1;
  strcpy(slime->enemy.nombre, "Slime");
  slime->enemy.hp = 5;
  slime->enemy.atq = 10;
  slime->enemy.tipo = 2;

  enemyState* zombie = (enemyState*)malloc(sizeof(enemyState));
  zombie->defeat = false;
  zombie->type = 1;
  strcpy(zombie->enemy.nombre, "Zombie");
  zombie->enemy.hp = 11;
  zombie->enemy.atq = 15;
  zombie->enemy.tipo = 3;

  enemyState* sdv = (enemyState*)malloc(sizeof(enemyState));
  sdv->defeat = false;
  sdv->type = 1;
  strcpy(sdv->enemy.nombre, "Saqueador del vacío");
  sdv->enemy.hp = 5;
  sdv->enemy.atq = 10;
  sdv->enemy.tipo = 2;

  enemyState* creeper = (enemyState*)malloc(sizeof(enemyState));
  creeper->defeat = false;
  creeper->type = 1;
  strcpy(creeper->enemy.nombre, "Creeper");
  creeper->enemy.hp = 12;
  creeper->enemy.atq = 30;
  creeper->enemy.tipo = 1;

  enemyState* teemo = (enemyState*)malloc(sizeof(enemyState));
  teemo->defeat = false;
  teemo->type = 2;
  strcpy(teemo->enemy.nombre, "Teemo");
  teemo->enemy.hp = 5;
  teemo->enemy.atq = 10;
  teemo->enemy.tipo = 2;

  enemyState* saibaMan = (enemyState*)malloc(sizeof(enemyState));
  saibaMan->defeat = false;
  saibaMan->type = 1;
  strcpy(saibaMan->enemy.nombre, "Saibaman");
  saibaMan->enemy.hp = 30;
  saibaMan->enemy.atq = 10;
  saibaMan->enemy.tipo = 3;

  enemyState* limonagrio = (enemyState*)malloc(sizeof(enemyState));
  limonagrio->defeat = false;
  limonagrio->type = 1;
  strcpy(limonagrio->enemy.nombre, "Limonagrio");
  limonagrio->enemy.hp = 30;
  limonagrio->enemy.atq = 10;
  limonagrio->enemy.tipo = 2;

  enemyState* patricio = (enemyState*)malloc(sizeof(enemyState));
  patricio->defeat = false;
  patricio->type = 1;
  strcpy(patricio->enemy.nombre, "Patricio");
  patricio->enemy.hp = 50;
  patricio->enemy.atq = 5;
  patricio->enemy.tipo = 2;

  enemyState* barbaro = (enemyState*)malloc(sizeof(enemyState));
  barbaro->defeat = false;
  barbaro->type = 1;
  strcpy(barbaro->enemy.nombre, "Bárbaro");
  barbaro->enemy.hp = 20;
  barbaro->enemy.atq = 20;
  barbaro->enemy.tipo = 3;

  enemyState* juanGuarnizo = (enemyState*)malloc(sizeof(enemyState));
  juanGuarnizo->defeat = false;
  juanGuarnizo->type = 2;
  strcpy(juanGuarnizo->enemy.nombre, "Juanguarnizo");
  juanGuarnizo->enemy.hp = 30;
  juanGuarnizo->enemy.atq = 15;
  juanGuarnizo->enemy.tipo = 1;

  enemyState* rakkun = (enemyState*)malloc(sizeof(enemyState));
  rakkun->defeat = false;
  rakkun->type = 1;
  strcpy(rakkun->enemy.nombre, "Rakkun");
  rakkun->enemy.hp = 40;
  rakkun->enemy.atq = 20;
  rakkun->enemy.tipo = 3;

  enemyState* kratos = (enemyState*)malloc(sizeof(enemyState));
  kratos->defeat = false;
  kratos->type = 1;
  strcpy(kratos->enemy.nombre, "Kratos");
  kratos->enemy.hp = 30;
  kratos->enemy.atq = 10;
  kratos->enemy.tipo = 1;

  enemyState* dotorre = (enemyState*)malloc(sizeof(enemyState));
  dotorre->defeat = false;
  dotorre->type = 1;
  strcpy(dotorre->enemy.nombre, "Dotorre");
  dotorre->enemy.hp = 30;
  dotorre->enemy.atq = 10;
  dotorre->enemy.tipo = 2;

  enemyState* sans = (enemyState*)malloc(sizeof(enemyState));
  sans->defeat = false;
  sans->type = 1;
  strcpy(sans->enemy.nombre, "Sans");
  sans->enemy.hp = 10;
  sans->enemy.atq = 50;
  sans->enemy.tipo = 1;

  enemyState* sukuna = (enemyState*)malloc(sizeof(enemyState));
  sukuna->defeat = false;
  sukuna->type = 3;
  strcpy(sukuna->enemy.nombre, "Sukuna");
  sukuna->enemy.hp = 50;
  sukuna->enemy.atq = 40;
  sukuna->enemy.tipo = 1;
  //======================================================================
  
  //=================insertar cada enemigo en la lista====================
  pushBack(enemies, slime);
  pushBack(enemies, zombie);
  pushBack(enemies, sdv);
  pushBack(enemies, creeper);
  pushBack(enemies, teemo);
  pushBack(enemies, saibaMan);
  pushBack(enemies, limonagrio);
  pushBack(enemies, patricio);
  pushBack(enemies, barbaro);
  pushBack(enemies, juanGuarnizo);
  pushBack(enemies, rakkun);
  pushBack(enemies, kratos);
  pushBack(enemies, dotorre);
  pushBack(enemies, sans);
  pushBack(enemies, sukuna);
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
int gachacomun()
{
  return (rand()%13) + 1;
}



int tirarBanner(account* yo, HashMap*  banners)
{
  int prob = rand()%999;
  printf("Probabilidad: %i\n", prob);
  if(prob == 0) return 15;
  else return gachacomun();
}


//========================================================================

//==========================Funciones de menu=============================
void menuCombate(account* yo, List* enemies)
{
  printf("Combate");
  return;
}

void mostrarInfoProbalidades()                //Jose 09/06/24
{
  printf("Infomacion de la probabilidad para sacar un personaje por rareza\n\n");
  printf("Rareza común : 7,07%%\n");
  printf("Rareza legendaria : 1%%\n");
  printf("\n");
}

void menuSummon(account* yo, HashMap* banners)
{
  int num;
  int opcion;
  while (1)
    {
      printf("%d\n\n", yo->deseos);
      printf("Menú Summon\n");
      printf("1) Tirar Banner\n");
      printf("2) Mostrar Información del banner\n");
      printf("3) Volver al Menú principal\n");
      scanf("%i",&opcion);
      switch(opcion)
        {
          
          case 1:
            limpiarPantalla();
            if(yo->deseos > 0)
            {
              yo->deseos -= 1;
              num = tirarBanner(yo, banners);
              campeon *obtenido = searchMap(banners, &num)->value;
              printf("Obtuviste: %s\n", obtenido->nombre);
              pushBack(yo->charac, obtenido);
            }
            else printf("No tienes deseos suficientes\n");
            break;

          case 2:
            limpiarPantalla();
            mostrarInfoProbalidades();
            break;

          case 3:
            limpiarPantalla();
            printf("Volviendo al menu principal\n");
            return;

          default:
            limpiarPantalla();
            printf("Opcion invalida vuelva a elegir otra opción del 1 al 3\n");
            break;

        }
    }
}

void mostrarListaPersonajes(List* charac) //Jean Billiard  08/06/24
{
  puts("Personajes:");
  for (campeon* current = firstList(charac); current != NULL; current = nextList(charac))
  {
    printf("%s\n", current->nombre);
  }
}

void mostrarPersonaje(int opcion, List* charac)
{
  campeon* current = firstList(charac);
  int avance = 1;
  while(avance < opcion)
  {
    current = nextList(charac);
    avance += 1;
  }
  printf("Nombre: %s\n", current->nombre);
  printf("Tipo: ");
  if(current->tipo == 1)
  {
    printf("Fuego\n");
  }
  else if(current->tipo == 2)
  {
    printf("Agua\n");
  }
  else if(current->tipo == 3)
  {
    printf("Planta\n");
  }
  printf("Puntos de Vida: %i\n", current->hp);
  printf("Ataque: %i\n", current->atq);
  printf("Puntos de Esquiva: %i\n", current->pde);
  presioneParaContinuar();
}

void menuPersonajes(account* yo)
{
  //printf("Personajes");
  campeon* hi;
  int opcion;
  do
  {
    mostrarListaPersonajes(yo->charac);
    puts("Elige el número de personaje para ver sus estadísticas");
    puts("o presiona 0 para volver al menú principal");
    scanf(" %i", &opcion);
    if(opcion != 0)
    {
      limpiarPantalla();
      hi = firstList(yo->charac);
      while(hi != NULL)
        {
          printf("Nombre: %s\n", hi->nombre);
          nextList(yo->charac);
        }
      mostrarPersonaje(opcion, yo->charac);
    }
  }while(opcion != 0);
}

bool menuEliminar()  //Jose Mena  09/06/24
{
  char opcion;
  bool notEliminar = false;
  while (!notEliminar)
    {
      printf("¿Estas seguro de querer eliminar la cuenta?\n");
      puts("1) Si marcas es opción eliminaras tu cuenta , perdiendo todo el progreso de esta\n");
      puts("2) Si marcas esta opción volverás al menú inicio sin eliminar la cuenta\n");
      scanf(" %c",&opcion);

      switch (opcion)
        {
          case '1':
            printf("Eliminando cuenta y cerrando el juego\n");
            return true;

          case '2':
            notEliminar = true;
            break;

          default:
            printf("Opción no valida ingrese 1 si quiere eliminar o 2 para conservar\n");
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
  puts("                    1. Combate");
  puts("                    2. Summon");
  puts("                    3. Personajes");
  puts("                    4. Borrar Mi cuenta");
}


int main(void) {
  srand(time(NULL));
  bool eliminar = false;
  HashMap* banners = createMap(22);
  List* enemies = createList();
  account* yo = (account*)malloc(sizeof(account));
  inicializeBanners(banners);
  inicializeEnemies(enemies);
    
  while(true)
    {
      int input;
      scanf("%d", &input);
      if(input == 0) break;
      int num = tirarBanner(yo, banners);
      campeon *obtenido = searchMap(banners, &num)->value;
      printf("Obtuviste: %s\n", obtenido->nombre);
    }

  
  /*
  int i = 1;
  personaje* teemp = searchMap(banners, &i)->value;
  printf("%s\n", teemp->nombre);
  printf(" %i\n", teemp->hp);
  printf(" %i\n", teemp->atq);
  printf(" %i\n", teemp->pde);
*/
  /*
  enemyState* teeemp = firstList(enemies);
  while(teeemp != NULL)
    {
      printf("%s\n", teeemp->enemy.nombre);
      printf("%i\n", teeemp->enemy.hp);
      printf("%i\n", teeemp->enemy.atq);
      printf("%i\n", teeemp->enemy.tipo);
      printf("\n");
      teeemp = nextList(enemies);
    }
  */
  //Jean Billiard  06/06/24
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
    getchar();
    switch(opcion)
    {
      case '1':
        menuCombate(yo, enemies);
        break;
      case '2':
        menuSummon(yo, banners);
        break;
      case '3':
        menuPersonajes(yo);
        break;
      case '4':
        eliminar = menuEliminar();
        break;
    }
    limpiarPantalla();
    presioneParaContinuar();
  }while(!eliminar);
  return 0;
}




