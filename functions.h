#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define buffer 4

typedef struct diffLines {
	int number;
	char* line;
} diffLines;

void freeStruct (diffLines* t, int length);

void freeArray(char** t, int length);

void printStruct (diffLines inputs[], int length);

void bubbleOnStruct(diffLines* inputs, int length);

void countSimilarLines(char** inputs, int allLines);

void readFile(int argc, char* argv[]);

void readInput();



#endif
