#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>

typedef struct mapHead_t{
    int numCidades;
    int numLigacoes;
    struct city_t *map; 
}mapHead_t;

mapHead_t *createMap(const char *);
bool createMapConnections(const char *, mapHead_t *);
void printMap(mapHead_t *);
void freeMapHead(mapHead_t *);

//Quests
int findNumDirectPaths(mapHead_t *, const int, const int);
int findShortestTimeBetweenCities(mapHead_t *, const int, const int);
int findShortestPriceBetweenCities(mapHead_t *, const int, const int);
int findEarliestTimeOfDeparture(mapHead_t *, const int, const int, const int);

#endif