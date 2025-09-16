#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct file_t file_t;

typedef enum File{
    Map,
    Quests,
    Result,
} File;

bool createFiles(const char *mapFileName, const char *questsFileName);
const char *getFileName(File nameFile);
bool createResultFile(void);
void freeFiles(void);

#endif