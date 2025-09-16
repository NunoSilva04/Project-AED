#include "quests.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct quests_t{
    char string[10];
    int cityA;
    int cityB;
    int startTime;
}quests_t;

void quest1(mapHead_t *, quests_t, FILE *);
void quest2(mapHead_t *, quests_t, FILE *);
void quest3(mapHead_t *, quests_t, FILE *);
void quest4(mapHead_t *, quests_t, FILE *);

bool readQuests(const char *questsFileName, const char *resultFileName, mapHead_t *mapHead){
    FILE *quests_f = fopen(questsFileName, "r");
    if(quests_f == NULL){
        return false;
    }
    FILE *result_f = fopen(resultFileName, "w");

    quests_t currQuest;
    memset(&currQuest, 0, sizeof(quests_t));
    while(fscanf(quests_f, "%s %d %d", currQuest.string, &currQuest.cityA, &currQuest.cityB) == 3){
        if(fscanf(quests_f, "%d", &currQuest.startTime) == 1){
            printf("%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, currQuest.startTime);
        }else{
            printf("%s %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB);
        }

        //Excract the number
        int taskNumber = 0;
        for(int currChar = 0; currChar < 10; currChar++){
            if(currQuest.string[currChar] == '\0'){
                break;
            }
            else if(currQuest.string[currChar] > '0' && currQuest.string[currChar] < '9'){
                taskNumber = currQuest.string[currChar] - '0';
                switch(taskNumber){
                case 1:
                    quest1(mapHead, currQuest, result_f);
                    break;
                case 2:
                    quest2(mapHead, currQuest, result_f);
                    break;
                case 3:
                    quest3(mapHead, currQuest, result_f);
                    break;
                case 4:
                    quest4(mapHead, currQuest, result_f);
                    break;
                case 5:
                    /*
                    TODO:: Quest5
                    */
                    break;

                default:
                    printf("Not a task\n");
                    fclose(quests_f);
                    return false;
                }
            }
        }
    }

    fclose(result_f);
    fclose(quests_f);
    return true;
}

void quest1(mapHead_t *mapHead, quests_t currQuest, FILE *result_f){
    int result = findNumDirectPaths(mapHead, currQuest.cityA, currQuest.cityB);
    fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    printf("%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
}

void quest2(mapHead_t *mapHead, quests_t currQuest, FILE *result_f){
    int result = findShortestTimeBetweenCities(mapHead, currQuest.cityA, currQuest.cityB);
    if(result == 1){
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }else if(result == 0){
        fprintf(result_f, "%s %d %d %s\n", currQuest.string, currQuest.cityA, currQuest.cityB, "infinito");
    }else {
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }
}

void quest3(mapHead_t *mapHead, quests_t currQuest, FILE *result_f){
    int result = findShortestPriceBetweenCities(mapHead, currQuest.cityA, currQuest.cityB);
    if(result == 1){
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }else if(result == 0){
        fprintf(result_f, "%s %d %d %s\n", currQuest.string, currQuest.cityA, currQuest.cityB, "infinito");
    }else {
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }
}

void quest4(mapHead_t *mapHead, quests_t currQuest, FILE *result_f){
    /*
    
    City A: 9
City B: 7
Transporte: autocarro
Tempo Ligacao: 1221
Custo Ligacao: 90
Ti: 0
Tf: 1000
Periodicidade: 200

    Aqui o tempo de ligaçao e 1221 o que é maior que 0-1000 portanto demoraria mais tempo que o próprio dia, mesmo se avançarmos um dia. Neste caso
    consideramos o quê? Um erro -1? Ou uma string "infinito"? Ou até mesmo considera-se outra opção como um caminho diferente?

    */

     int result = findEarliestTimeOfDeparture(mapHead, currQuest.cityA, currQuest.cityB, currQuest.startTime);
    if(result == 1){
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }else if(result == 0){
        fprintf(result_f, "%s %d %d %s\n", currQuest.string, currQuest.cityA, currQuest.cityB, "infinito");
    }else {
        fprintf(result_f, "%s %d %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB, result);
    }  
}