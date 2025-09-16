#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"
#include "map.h"
#include "quests.h"

//Numero grupo 141

//Seria possível no mapa darem-nos dois caminhos para entre cidade 4 e 3 e terem o mesmo meio de transporte mas depois variarem no custo?

typedef struct quests_t{
    char taskNumber[20];
    int cityA;
    int cityB;
    int time;
}quests_t;

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Not enough arguments\n");
        printf("The command line should be %s <nome1>.map <nome2>.quests\n", argv[0]);
        return 0;
    }

    //Files
    if(!createFiles(argv[1], argv[2])){
        printf("Couldn't create files\n");
        return 0;
    }
    
    //Map 
    mapHead_t *map = createMap(getFileName(Map));
    if(map == NULL){
        printf("Couldn't create map head\n");
        return 0;
    }

    if(!createMapConnections(getFileName(Map), map)){
        printf("Couldn't create map Connections\n");
        return 0;
    }
    printMap(map);

    //Quests
    if(!readQuests(getFileName(Quests), getFileName(Result), map)){
        printf("Couldn't read quests\n");
        return 0;
    }

    freeMapHead(map);
    freeFiles();

    return 0;
}