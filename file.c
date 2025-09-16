#include "file.h"
#include <string.h>

typedef struct file_t{
    const char *map;
    const char *quests;
    const char *result;
} file_t;
file_t files;

const char *getOutputFileName(const char* filename);

bool createFiles(const char *mapFileName, const char *questsFileName){
    files.map = (char *) malloc((strlen(mapFileName) + 1) * sizeof(char));          //+1 pois precisa de espaço para o null terminator
    if(files.map == NULL){
        return false;
    }
    strcpy((char *)files.map, mapFileName);

    files.quests = (char *) malloc((strlen(questsFileName) + 1) * sizeof(char));    //+1 pois precisa de espaço para o null terminator
    if(files.quests == NULL){
        return false;
    }
    strcpy((char *)files.quests, questsFileName);

    const char *resultsFileName = getOutputFileName(questsFileName);
    if(resultsFileName == NULL){
        return false;
    }
    files.result = (char *) malloc((strlen(resultsFileName) + 1) * sizeof(char));   //+1 pois precisa de espaço para o null terminator
    if(files.result == NULL){
        return false;
    }
    strcpy((char *)files.result, resultsFileName);
    free((void *)resultsFileName);

    return true;
}

const char *getFileName(File nameFile){
    switch(nameFile){
    case Map:
        return files.map;
        break;

    case Quests:
        return files.quests;
        break;

    case Result:
        return files.result;
        break;

    default:
        return NULL;
    }
}

void freeFiles(void){
    if(files.map) free((void *)files.map);
    if(files.quests) free((void *)files.quests);
    if(files.result) free((void *)files.result);
}

bool createResultFile(void){
    FILE *resultFile = fopen(files.result, "w");
    if(resultFile == NULL){
        return false;
    }

    fclose(resultFile);
    return true;
}

const char *getOutputFileName(const char* filename){
    const char *firstPosition = strchr(filename, '/');
    int firstCharacter = firstPosition - filename + 1;

    const char *finalPosition = strrchr(filename, '.');
    int lastCharacter = finalPosition - filename + 1;
    
    char *output = (char *) malloc((lastCharacter - firstCharacter + 8) * sizeof(char));
    if(output == NULL) return NULL;
    
    int currOutputCharacter = 0, currFilenameCharacter = firstCharacter;
    for(; currFilenameCharacter < lastCharacter; currFilenameCharacter++, currOutputCharacter++){
        output[currOutputCharacter] = filename[currFilenameCharacter]; 
    }

    output[currOutputCharacter] = '\0';
    strcat(output, "results");
    return output;
}