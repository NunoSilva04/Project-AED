#include "quests.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct quests_t{
    char string[10];
    int cityA;
    int cityB;
    int time;
}quests_t;

void quest1(mapHead_t *, quests_t, FILE *);

bool readQuests(const char *questsFileName, const char *resultFileName, mapHead_t *mapHead){
    FILE *quests_f = fopen(questsFileName, "r");
    if(quests_f == NULL){
        return false;
    }
    FILE *result_f = fopen(resultFileName, "w");

    quests_t currQuest;
    memset(&currQuest, 0, sizeof(quests_t));
    while(fscanf(quests_f, "%s %d %d", currQuest.string, &currQuest.cityA, &currQuest.cityB) == 3){
        printf("%s %d %d\n", currQuest.string, currQuest.cityA, currQuest.cityB);
        /*
        TODO:: add a condition to then check time later for task 4
        */

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
                    /*
                    TODO:: Quest2
                    */
                    break;
                case 3:
                    /*
                    TODO:: Quest3
                    */
                    break;
                case 4:
                    /*
                    TODO:: Quest4
                    */
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