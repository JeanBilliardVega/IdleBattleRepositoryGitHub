# Idle Battle
## Descripción
Idle Battle es un juego indie y por niveles. El jugador conseguirá diversos campeones con objetivo de derrotar a los enemigos peligrosos. Idle Battle consiste un sistema de gacha, el jugador puede gastar un monetario especial que se denomina **Deseo**, para conseguir los campeones. Buena suerte jugador! Junto con tus campeones, vence a los imposibles y hacia más allá!
## Cómo compilar y ejecutar
1. Crear una cuenta de [Replit](https://replit.com/)
2. Apretar el botón **Create Repl**
3. Importar este repositorio con el botón **Import from github**
4. Importar atráves de URL **From URL**
5. Pegar el enlace de este repositorio luego, apreta el botón **Import from gituhub**
```
https://github.com/JeanBilliardVega/IdleBattleRepositoryGitHub
```
6. Apreta el botón **Run** y puedes jugar!
## Funcionalidades
### Funcionando correctamente:
* Sistema combate del juego
* Sistema gacha del juego
* Examinar los campeones obtenidos
* Eliminar el progreso del juego
### Funcionalidades no implementados (A mejorar):
* Ordenar los campeones por orden de adquirimiento o por nombre
* Opción para guardar el progreso del juego
* Galería de campeones
## Ejemplo de uso
**Menu de bienvenida**
 
Al comienzo del programa, El sistema dará la bienvenida al jugador, apreta cualquier tecla para comenzar
```
         --------------------------------
         |   Bienvenido a Idle battle   |
         |  Apreta ENTER para Comenzar  |
         --------------------------------
```
**Menú Pricipal**

  En el menú principal el jugador debera seleccionar una opción apretando la tecla del 1 al 4
  para acceder al apartado del juego que quiera ir.
  ````
    IDLE BATTLE
    1. Aventura
    2. Summon
    3. Campeones
    4. Borrar Mi cuenta
  ````
**1. Menú aventura**

El jugador accederá al menú de combate cuando este aprete la tecla 1 en el menú principal,
  y después accederá a esta pantalla.
  ````
                 Nivel 2
  Anteriores(A)          Siguiente(D)
  -----------------------------------
  | Zombie                          |
  -----------------------------------
  | Tipo     | Planta               |
  | PV       | 11                   |
  | ATQ      | 15                   |
  -----------------------------------
  ````

  En este menú encontraremos diferentes opciones, entre las cuáles se encuentran:

    Anteriores(A) : Con esta opción permite al jugador volver al nivel anterior, para esto
    juegador solo debe presionar la tecla a o A.
  
  ````
                 Nivel 1
                         Siguiente(D)
  -----------------------------------
  | Slime                           |
  -----------------------------------
  | Tipo     | Agua                 |
  | PV       | 5                    |
  | ATQ      | 10                   |
  -----------------------------------
  Salir(0)             Seleccionar(X)
  ````
    Siguiente(D) : Con esta opción permite al jugador avanzar al siguiente nivel, el jugador
    tendrá apretar la tecla D o d para así ocupar esta función.
  ````
                 Nivel 3
  Anteriores(A)          Siguiente(D)
  -----------------------------------
  | Saqueador del vacio             |
  -----------------------------------
  | Tipo     | Fuego                |
  | PV       | 23                   |
  | ATQ      | 15                   |
  -----------------------------------
  Salir(0)             Seleccionar(X)
  ````
    Salir (0) : Con esta opción permite al jugador volver al menú principal, solamente el jugador
    tendrá que apretar la tecla 0
  ````
        IDLE BATTLE
        1. Aventura
        2. Summon
        3. Campeones
        4. Borrar Mi cuenta
  ````
    Seleccionar(X) : Con esta opción permitirá al jugador seleccionar el nivel, para luego
    ir una pantalla en donde podrá seleccionar un personaje antes de empezar el combate, Para esto
    el jugador solo tendrá que apretar la tecla x o X.
  ````
   Elige un campeón para el combate

   Campeones                  Salir(0)
   -----------------------------------
   | 1 ) Fernanfloo                  |
   -----------------------------------
   | 2 ) Ellie                       |
   -----------------------------------
   | 3 ) Arale                       |
   -----------------------------------
   | 4 ) Karma                       |
   -----------------------------------
  ````
    Luego dentro de esta opción podremos elegir un personaje simplemente Ingresando el número
    correspondiente al personaje dentro de la lista.
  ````
      Elige un campeón para el combate

      Campeones                  Salir(0)
      -----------------------------------
      | 1 ) Fernanfloo                  |
      -----------------------------------
      | 2 ) Ellie                       |
      -----------------------------------
      | 3 ) Arale                       |
      -----------------------------------
      | 4 ) Karma                       |
      -----------------------------------
      Ingrese su opción(Enter para confirmar): 3
      Seleccionaste a Arale
  ````
    Después de haber seleccionado a un personaje, el jugador deberá apretar enter para entrar
    al combate y mostrará el escenario de combate:

  ````
                   Turno: 1
     ______________________________________   Abandonar(0)
    |                                Slime |
    |                                 PV 5 |
    |                               ATQ 10 |
    |                                      |  ATACAR(A)
    |-----------------VS-------------------|
    |                                      |  Esquivar(E)
    | Arale                                |
    | PV 5                                 |
    | ATQ 20                               |
    | PDE 0                                |
     ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
  ````
    Durante el combate tendremós estas diferentes opciones:

       ATACAR(A): Con esta opción el jugador podrá atacar al enemigo , para estó simplemente 
       debe presionar la tecla A O a.

  ````
      ATAQUE INEFICAZ!! Slime -10 PV
                     Turno: 1
       ______________________________________   Abandonar(0)
      |                                Slime |
      |                                 PV 0 |
      |                               ATQ 10 |
      |                                      |  ATACAR(A)
      |-----------------VS-------------------|
      |                                      |  Esquivar(E)
      | Arale                                |
      | PV 5                                 |
      | ATQ 20                               |
      | PDE 0                                |
       ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
      Ganaste la partida!! FELICIDADES!!
      +1 Deseos
  ````
      Esquivar(E): Con esta opción el jugador podrá esquivar el enemigo y contratacar , si es
      que el enemigo no esquivo también, para esta opción el jugador solo tendrá que apretar la
      tecla e o E.
  ````
        SIENTE MI FURIA!!
        Slime -5 PV
                       Turno: 1
         ______________________________________   Abandonar(0)
        |                                Slime |
        |                                 PV 0 |
        |                               ATQ 10 |
        |                                      |  ATACAR(A)
        |-----------------VS-------------------|
        |                                      |  Esquivar(E)
        | Fernanfloo                           |
        | PV 1                                 |
        | ATQ 0                                |
        | PDE 4                                |
         ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
  ````
      Abandonar(0): Con esta opción el jugador podrá abandonar el combate y volver al menú de aventura.
  
  ````
                       Nivel 1
                               Siguiente(D)
        -----------------------------------
        | Slime                           |
        -----------------------------------
        | Tipo     | Agua                 |
        | PV       | 5                    |
        | ATQ      | 10                   |
        -----------------------------------
        Salir(0)             Seleccionar(X)
        
   ````
   Cada vez que se gané un nivel saldrá un mensaje "Ganaste la partida!! FELICIDADES!!
   +n Deseos" , y depués tendremos apretar el número 0 para volver al menú de aventura.


**2. Menú Summon**

  Para acceder a este el jugador deberá apretar la tecla 2 en el menú principal. En este se
  mostrará lo siguiente.
  ````
  Deseos: 2                  Salir(0)
  -----------------------------------
  |              Summon             |
  -----------------------------------
  Detalles(2)              Invocar(1)
  ````
  En esta pantalla encontraremos dos opciones sin contar el salir, las cuáles son:

        Detalles(2) : Esta opción permitirá al jugador ver la probabilidad de obtener un
        campeón según su rareza , para ver esto solo tendremos presionar la tecla del número
        2.
  
   ````
        **Detalles**
        Este gachapón contiene 14 campeones comunes y 1 campeón legendario.
        Las probalidades se desmuestra en la siguiente tabla:
        -----------------------------------
        |    Rareza     |   Probabilidad  |
        -----------------------------------
        |     Común     |      7.14 %     |
        |   Legendario  |      0.10 %     |
        -----------------------------------
   ````
        Invocar(1): Esta opción permitrá al jugador obtener un personaje aleatorio del banner
        , para estó simplemente tendrá que apretar la tecla 1.

  ````
        Obtuviste: Deku
        Presione una tecla para continuar...
  ````
        Si el campeón obtenido esta repetido osea que si el jugador ya lo tiene saldrá el
        siguiente mensaje "Ya tienes este personaje", por lo que el jugador no obtendrá nada.

        Por otro caso si el jugador no tiene ningun deseo saldrá el siguiente mensaje 
        "No tienes deseos suficientes", por lo que no podrá invocar.
        
**3. Menú de campeones**

    Para acceder a este menú el jugador tendrá apretar el número 3 en el menú principal. En
    el menú de combate se mostrará lo siguiente:

   ````
   Campeones                  Salir(0)
   -----------------------------------
   | 1 ) Bob Esponja                 |
   -----------------------------------
   | 2 ) Escanor                     |
   -----------------------------------
   | 3 ) Jake                        |
   -----------------------------------
   | 4 ) Deku                        |
   -----------------------------------
   ````
    En este tendremós la opción salir y además opciones para mostrar la información del
    personaje que dependerá del personaje que seleccionemos según su numero.

    Como información mostrará lo siguiente:
  ````
    -----------------------------------
    | Bob Esponja                     |
    -----------------------------------
    | Tipo     | Agua                 |
    | PV       | 30                   |
    | ATQ      | 3                    |
    | PDE      | 6                    |
    -----------------------------------
  ````

**4. Menú Borrar Cuenta**

  Para acceder a este menú el jugador tendrá que apretar la tecla número 4 en el menú pricipal
  y se  mostrará la siguiente información
  ````
    ¿Estas seguro de querer eliminar la cuenta?
    Si(S)         No(otras teclas)
  ````
  Dentro de las opciones encontramos el Si que apretando la tecla S eliminaremos la cuenta
  y se cerrá el programa , por otró lado si apretamos cualquier otra tecla conservaremos la
  cuenta y regresaremos al menú principal.

## Tip del juego
Cada campeón tiene su respectivo **tipo de elemento**, selecciona campeon adecuado para vencer a los enemigos. Relación de los elementos:
````
Fuego -> Planta
Planta -> Agua
Agua -> Fuego
````
Suertes jugador!! Que tenga buena experiencia!!

