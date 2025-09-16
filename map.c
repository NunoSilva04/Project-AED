#include "map.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct city_t;
struct ligacao_t;

typedef struct city_t{
    int cityNumber;
    int numLigacoes;
    int size;           //size of the array of ligaçoes       
    struct ligacao_t **ligacoes;     
}city_t;

typedef struct ligacao_t{
    int cityA;
    int cityB;
    char transporte[20];
    int tempoLigacao;
    int custoLigacao;
    int t_i;
    int t_f;
    int periodicidade;
}ligacao_t;

bool addConnectionToCity(const int, mapHead_t *, ligacao_t *);

mapHead_t *createMap(const char *mapFileName){
    mapHead_t *mapHead = (mapHead_t *) calloc(1, sizeof(mapHead_t));
    if(mapHead == NULL){
        return NULL;
    }

    FILE *map_f = fopen(mapFileName, "r");
    if(map_f == NULL){
        return NULL;
    }

    if(fscanf(map_f, "%d %d", &mapHead->numCidades, &mapHead->numLigacoes) != 2){
        return NULL;
    }

    mapHead->map = (city_t *) calloc(mapHead->numCidades, sizeof(city_t));
    if(mapHead->map == NULL){
        return NULL;
    }

    for(int currCity = 0; currCity < mapHead->numCidades; currCity++){
        mapHead->map[currCity].cityNumber = currCity + 1;  //+1 porque começa sempre em 0 e as cidades começam em 1
        mapHead->map[currCity].numLigacoes = 0;
        mapHead->map[currCity].size = 1;
        mapHead->map[currCity].ligacoes = (ligacao_t **) calloc(1, sizeof(ligacao_t *));
        if(mapHead->map[currCity].ligacoes == NULL){
            return NULL;
        }
    }

    fclose(map_f);
    return mapHead;
}

bool createMapConnections(const char *mapFileName, mapHead_t *mapHead){
    FILE *map_f = fopen(mapFileName, "r");

    int fileSize = mapHead->numLigacoes + 1;
    for(int currLine = 0; currLine < fileSize; currLine++){
        //Skip first line
        if(currLine == 0){
            char buffer[256];
            fgets(buffer, 256, map_f);
            continue;
        }

        ligacao_t *temp = (ligacao_t *) calloc(1, sizeof(ligacao_t));
        if(temp == NULL){
            return false;
        }
        if(fscanf(map_f, "%d %d %s %d %d %d %d %d", 
                        &temp->cityA, 
                        &temp->cityB,
                        temp->transporte,
                        &temp->tempoLigacao,
                        &temp->custoLigacao,
                        &temp->t_i,
                        &temp->t_f,
                        &temp->periodicidade) != 8){
            return false;
        }

        //Make 2 copies so no problems when freeing memory
        ligacao_t *copy1 = (ligacao_t *) calloc(1, sizeof(ligacao_t));
        if(copy1 == NULL){
            return false;
        }
        *copy1 = *temp;

        ligacao_t *copy2 = (ligacao_t *) calloc(1, sizeof(ligacao_t));
        if(copy2 == NULL){
            return false;
        }
        *copy2 = *temp;
        free(temp);

        //É menos 1 porque o array começa em 0 e a cidade começa em 1
        if(!addConnectionToCity(copy1->cityA - 1, mapHead, copy1)) return false;
        if(!addConnectionToCity(copy2->cityB - 1, mapHead, copy2)) return false;
    }

    fclose(map_f);

    return true;
}

bool addConnectionToCity(const int cityNumber, mapHead_t *mapHead, ligacao_t *newConnection){
    //Change the number of city if the first city in the new connection is not the current number of the city
    if(newConnection->cityA != mapHead->map[cityNumber].cityNumber){
        int temp = newConnection->cityA;
        newConnection->cityA = newConnection->cityB;
        newConnection->cityB = temp;
    }
    
    if(mapHead->map[cityNumber].numLigacoes >= mapHead->map[cityNumber].size){
        int newSize = mapHead->map[cityNumber].size * 2;
        mapHead->map[cityNumber].size = newSize;

        ligacao_t **ligacoesResized = (ligacao_t **) calloc(newSize, sizeof(ligacao_t *));
        if(ligacoesResized == NULL){
            return false;
        }

        for(int currConnection = 0; currConnection < mapHead->map[cityNumber].numLigacoes; currConnection++){
            ligacoesResized[currConnection] = mapHead->map[cityNumber].ligacoes[currConnection];
        }
        if(mapHead->map[cityNumber].ligacoes) free(mapHead->map[cityNumber].ligacoes);
        mapHead->map[cityNumber].ligacoes = ligacoesResized;

        int currConnection = mapHead->map[cityNumber].numLigacoes;
        mapHead->map[cityNumber].ligacoes[currConnection] = newConnection;
        mapHead->map[cityNumber].numLigacoes += 1;
        return true;
    }

    int currConnection = mapHead->map[cityNumber].numLigacoes;
    mapHead->map[cityNumber].ligacoes[currConnection] = newConnection;
    mapHead->map[cityNumber].numLigacoes += 1;
    return true;
}

void printMap(mapHead_t *mapHead){
    for(int currCity = 0; currCity < mapHead->numCidades; currCity++){
        printf("Cidade: %d com %d numero de ligacoes e tem size = %d\n", mapHead->map[currCity].cityNumber, mapHead->map[currCity].numLigacoes, mapHead->map[currCity].size);
        if(mapHead->map[currCity].numLigacoes == 0) continue;
        for(int currConnection = 0; currConnection < mapHead->map[currCity].numLigacoes; currConnection++){
            printf("Ligacao %d\n", currConnection);
            printf("City A: %d\nCity B: %d\nTransporte: %s\nTempo Ligacao: %d\nCusto Ligacao: %d\nTi: %d\nTf: %d\nPeriodicidade: %d\n\n", 
                    mapHead->map[currCity].ligacoes[currConnection]->cityA,
                    mapHead->map[currCity].ligacoes[currConnection]->cityB, 
                    mapHead->map[currCity].ligacoes[currConnection]->transporte,
                    mapHead->map[currCity].ligacoes[currConnection]->tempoLigacao,
                    mapHead->map[currCity].ligacoes[currConnection]->custoLigacao,
                    mapHead->map[currCity].ligacoes[currConnection]->t_i,
                    mapHead->map[currCity].ligacoes[currConnection]->t_f,
                    mapHead->map[currCity].ligacoes[currConnection]->periodicidade);
        }
    }
}

void freeMapHead(mapHead_t *mapHead){
    for(int currCity = 0; currCity < mapHead->numCidades; currCity++){
        for(int currConnection = 0; currConnection < mapHead->map[currCity].numLigacoes; currConnection++){
            if(mapHead->map[currCity].ligacoes[currConnection]) free(mapHead->map[currCity].ligacoes[currConnection]);
        }
        if(mapHead->map[currCity].ligacoes) free(mapHead->map[currCity].ligacoes);
    }

    if(mapHead->map) free(mapHead->map);
    if(mapHead) free(mapHead);
}

int findNumDirectPaths(mapHead_t *mapHead, const int cityA, const int cityB){
    if((cityA < 1 || cityA > 12) || (cityB < 1 || cityB > 12) ){
        return -1;
    }

    int startCity = cityA - 1;  //Menos 1 porque cidade 1 começa no índice 0

    int numConnections = 0;
    for(int currConnection = 0; currConnection < mapHead->map[startCity].numLigacoes; currConnection++){
        if(mapHead->map[startCity].ligacoes[currConnection]->cityA == cityA && mapHead->map[startCity].ligacoes[currConnection]->cityB == cityB){
            numConnections += 1;
        }
    }

    return numConnections;
}

/*
This function can return 3 values:
    - Returns 1 in case of success (an actual price)
    - Returns 0 in case there is no direct connection between the cities (string = infinito)
    - Returns - 1 for some other eventuality
*/

int findShortestTimeBetweenCities(mapHead_t *mapHead, const int cityA, const int cityB){
    if((cityA < 1 || cityA > 12) || (cityB < 1 || cityB > 12) ){
        return -1;
    }

    int startCity = cityA - 1;  //Menos 1 porque cidade 1 começa no índice 0

    int lowestTime = 5000;
    bool existConnection = false;
    for(int currConection = 0; currConection < mapHead->map[startCity].numLigacoes; currConection++){
        if(mapHead->map[startCity].ligacoes[currConection]->cityB == cityB){
            existConnection = true;
            if(mapHead->map[startCity].ligacoes[currConection]->tempoLigacao < lowestTime){
                lowestTime = mapHead->map[startCity].ligacoes[currConection]->tempoLigacao;
            }
        }
    }

    if(existConnection){
        return lowestTime;
    }

    return 0;
}

/*
This function can return 3 values:
    - Returns 1 in case of success (an actual price)
    - Returns 0 in case there is no direct connection between the cities (string = infinito)
    - Returns - 1 for some other eventuality
*/
int findShortestPriceBetweenCities(mapHead_t *mapHead, const int cityA, const int cityB){
    if((cityA < 1 || cityA > 12) || (cityB < 1 || cityB > 12) ){
        return -1;
    }

    int startCity = cityA - 1;  //Menos 1 porque cidade 1 começa no índice 0

    int lowestPrice = 5000;
    bool existConnection = false;
    for(int currConection = 0; currConection < mapHead->map[startCity].numLigacoes; currConection++){
        if(mapHead->map[startCity].ligacoes[currConection]->cityB == cityB){
            existConnection = true;
            if(mapHead->map[startCity].ligacoes[currConection]->custoLigacao < lowestPrice){
                lowestPrice = mapHead->map[startCity].ligacoes[currConection]->custoLigacao;
            }
        }
    }

    if(existConnection){
        return lowestPrice;
    }

    return 0;
}

/*
This function can return 3 values:
    - Returns 1 in case of success (an actual price)
    - Returns 0 in case there is no direct connection between the cities (string = infinito)
    - Returns - 1 for some other eventuality
*/
int findEarliestTimeOfDeparture(mapHead_t *mapHead, const int cityA, const int cityB, const int departureTime){
    if((cityA < 1 || cityA > 12) || (cityB < 1 || cityB > 12) ){
        return -1;
    }

    int startCity = cityA - 1;  //Menos 1 porque cidade 1 começa no índice 0

    int shortestTime = 50000;
    bool existConnection = false;
    for(int currConnection = 0; currConnection < mapHead->map[startCity].numLigacoes; currConnection++){
        if(mapHead->map[startCity].ligacoes[currConnection]->cityB == cityB){
            existConnection = true;
            
            //Find real departure time
            int realDeparture = mapHead->map[startCity].ligacoes[currConnection]->t_i;
            while(realDeparture < departureTime){
                realDeparture += mapHead->map[startCity].ligacoes[currConnection]->periodicidade;
            }
            if(realDeparture > mapHead->map[startCity].ligacoes[currConnection]->t_f){
                realDeparture = 1440 + mapHead->map[startCity].ligacoes[currConnection]->t_i;
            }

            int tempShortestTime = realDeparture + mapHead->map[startCity].ligacoes[currConnection]->tempoLigacao;
            if(tempShortestTime < shortestTime){
                shortestTime = tempShortestTime;
            }
        }   
    }

    if(existConnection){
        return shortestTime;
    }

    return 0;
}  