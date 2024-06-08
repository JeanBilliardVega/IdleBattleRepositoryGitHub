/*
#ifndef MAP_H
#define MAP_H
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void *key;
  void *value;
} MapPair;

typedef struct Map Map;

Map *map_create(int (*is_equal)(void *key1, void *key2)); // unsorted map

Map *sorted_map_create(int (*lower_than)(void *key1, void *key2));

void map_insert(Map *map, void *key, void *value);

MapPair *map_remove(Map *map, void *key);

MapPair *map_search(Map *map, void *key);

MapPair *map_first(Map *map);

MapPair *map_next(Map *map);

void map_clean(Map *map);

*/

//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 2018 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair {
     char * key;
     void * value;
} Pair;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

#endif /* HashMap_h */
