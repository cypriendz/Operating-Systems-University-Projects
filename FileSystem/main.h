#ifndef MAIN_H
#define MAIN_H
//includes
#include"tree.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <errno.h>
//prototypes
int* allInputs(int argc, char* argv[], int* num);
int* allFiles(char **names, int num);
void printWords(struct map **map);
#endif
