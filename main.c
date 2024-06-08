#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "map.h"

//=========================Bloque de estructura===========================
typedef struct
{
  int deseo;
  List* charac;
}account;

typedef struct{
  char nombre[50];
  char code;
  int hp; //Puntos De Vida
  int atq; //Ataque
  int pde; //Puntos De Esquiva
  int tipo; //(1: fuego, 2: agua, 3: planta)
}personaje;

typedef struct
{
  char nombre[50];
  char code;
  int hp;
  int atq;
  int tipo;
}enemigo;

typedef struct
{
  enemigo enemy;
  bool defeat;
}enemyState;

//========================================================================

//========================================================================

//=========================Control del panel==============================
void limpiarPantalla() { system("clear"); }

void presioneParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Espera a que el usuario presione una tecla
}

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}
//========================================================================

//===========================Inicializaciones=============================
void inicializeBanners(HashMap* banners)
{
  personaje* charizard = (personaje*)malloc(sizeof(personaje));
  strcpy(charizard->nombre, "Charizard");
  charizard->code = 1;
  charizard->hp = 60;
  charizard->atq = 3;
  charizard->pde = 2;
  charizard->tipo = 1;

  personaje* goku = (personaje*)malloc(sizeof(personaje));
  strcpy(goku->nombre, "Goku");
  goku->code = 2;
  goku->hp = 50;
  goku->atq = 4;
  goku->pde = 2;
  goku->tipo = 1;

  personaje* hutao = (personaje*)malloc(sizeof(personaje));
  strcpy(hutao->nombre, "Hutao");
  hutao->code = 3;
  hutao->hp = 30;
  hutao->atq = 6;
  hutao->pde = 1;
  hutao->tipo = 1;

  personaje* escanor = (personaje*)malloc(sizeof(personaje));
  strcpy(escanor->nombre, "Escanor");
  escanor->code = 4;
  escanor->hp = 80;
  escanor->atq = 4;
  escanor->pde = 0;
  escanor->tipo = 1;

  personaje* sieteDeMarzo = (personaje*)malloc(sizeof(personaje));
  strcpy(sieteDeMarzo->nombre, "Siete de marzo");
  sieteDeMarzo->code = 5;
  sieteDeMarzo->hp = 30;
  sieteDeMarzo->atq = 3;
  sieteDeMarzo->pde = 5;
  sieteDeMarzo->tipo = 2;

  personaje* ellie = (personaje*)malloc(sizeof(personaje));
  strcpy(ellie->nombre, "Ellie");
  ellie->code = 6;
  ellie->hp = 30;
  ellie->atq = 3;
  ellie->pde = 4;
  ellie->tipo = 3;

  personaje* leonKennedy = (personaje*)malloc(sizeof(personaje));
  strcpy(leonKennedy->nombre, "Leon Kennedy");
  leonKennedy->code = 7;
  leonKennedy->hp = 50;
  leonKennedy->atq = 3;
  leonKennedy->pde = 2;
  leonKennedy->tipo = 2;

  personaje* karma = (personaje*)malloc(sizeof(personaje));
  strcpy(karma->nombre, "Karma");
  karma->code = 8;
  karma->hp = 40;
  karma->atq = 3;
  karma->pde = 2;
  karma->tipo = 3;

  personaje* hatsuneMiku = (personaje*)malloc(sizeof(personaje));
  strcpy(hatsuneMiku->nombre, "Hatsune Miku");
  hatsuneMiku->code = 9;
  hatsuneMiku->hp = 70;
  hatsuneMiku->atq = 2;
  hatsuneMiku->pde = 5;
  hatsuneMiku->tipo = 2;

  personaje* jake = (personaje*)malloc(sizeof(personaje));
  strcpy(jake->nombre, "Jake");
  jake->code = 10;
  jake->hp = 80;
  jake->atq = 4;
  jake->pde = 0;
  jake->tipo = 3;

  personaje* bobEsponja = (personaje*)malloc(sizeof(personaje));
  strcpy(bobEsponja->nombre, "Bob Esponja");
  bobEsponja->code = 11;
  bobEsponja->hp = 30;
  bobEsponja->atq = 3;
  bobEsponja->pde = 6;
  bobEsponja->tipo = 2;

  personaje* arale = (personaje*)malloc(sizeof(personaje));
  strcpy(arale->nombre, "Arale");
  arale->code = 12;
  arale->hp = 5;
  arale->atq = 20;
  arale->pde = 0;
  arale->tipo = 1;

  personaje* fernanfloo = (personaje*)malloc(sizeof(personaje));
  strcpy(fernanfloo->nombre, "Fernanfloo");
  fernanfloo->code = 13;
  fernanfloo->hp = 1;
  fernanfloo->atq = 0;
  fernanfloo->pde = 5;
  fernanfloo->tipo = 1;

  personaje* deku = (personaje*)malloc(sizeof(personaje));
  strcpy(deku->nombre, "Deku");
  deku->code = 14;
  deku->hp = 40;
  deku->atq = 4;
  deku->pde = 4;
  deku->tipo = 1;

  personaje* dios = (personaje*)malloc(sizeof(personaje));
  strcpy(dios->nombre, "Dios");
  dios->code = 15;
  dios->hp = 999;
  dios->atq = 999;
  dios->pde = 0;
  dios->tipo = 1;
  
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
}

void inicializeEnemies(List* enemies)
{
  enemyState* slime = (enemyState*)malloc(sizeof(enemyState));
  slime->defeat = false;
  
  return;
}

void inicializeYo(account* yo)
{
  return;
}
//========================================================================

//============================Herramientas================================

//========================================================================

//==========================Funciones de menu=============================
void menuCombate(account* yo, List* enemies)
{
  return;
}

void menuSummon(account* yo, HashMap* banners)
{
  return;
}

void menuPersonajes(account* yo)
{
  return;
}

void menuEliminar()
{
  return;
}
//========================================================================


void mostrarMenu()
{
  limpiarPantalla();
  puts("                    IDLE BATTLE");
  puts("                    1. Combate");
  puts("                    2. Summon");
  puts("                    3. Personajes");
  puts("                    4. Borrar Mi cuenta");
}


int main(void) {
  HashMap* banners = createMap(50);
  List* enemies = createList();
  account* yo;
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
    scanf("%c", &opcion);
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
        menuEliminar();
        break;
    }
    limpiarPantalla();
    presioneParaContinuar();
  }while(opcion != '4');
  return 0;
}




