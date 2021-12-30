#include "functions.h"

void freeStruct(diffLines* t, int length) {
	int i;
	for (i = 0; i < length; ++i)
		free(t[i].line);
	free(t);
}

void freeArray(char** t, int length) {
	int i;
	for (i = 0; i < length; ++i) {
		free(t[i]);
	}
	free(t);
}

void printStruct(diffLines inputs[], int length) {
	int i;
	for (i = 0; i < length; ++i) {
		printf("%d %s", inputs[i].number, inputs[i].line);
	}

}

void bubbleOnStruct(diffLines* inputs, int length) {
	int i;
	for(i = 0; i < length; ++i) {
		int j;
		for(j = length-1; j > i; --j) {
			if (inputs[j].number > inputs[j-1].number) {
				diffLines term;
				/*term.number = inputs[j].number;
				term.line = (char*)malloc(sizeof(inputs[j].line));
				strcpy(term.line, inputs[j].line);
				inputs[j].number = inputs[j-i].number;
				strcpy(inputs[j].line, inputs[j-1].line);
				inputs[j-1].number = term.number;
				strcpy(inputs[j-1].line, term.line);
				free(term.line);*/
				term = inputs[j];
				inputs[j] = inputs[j-1];
				inputs[j-1] = term;
			}
		}
	}
}


void countSimilarLines(char** inputs, int allLines) {
	diffLines* inputsStruct;
	inputsStruct = (diffLines*)malloc(sizeof(diffLines));
	inputsStruct[0].number = 1;
	inputsStruct[0].line = (char*)malloc(sizeof(inputs[0])*sizeof(char));
	strcpy(inputsStruct[0].line, inputs[0]);
	int length = 1;
	int k;
	for (k = 1; k < allLines; ++k) {
		int l;
		for(l = 0; l < length; ++l) {
			int p = strcmp(inputsStruct[l].line, inputs[k]);
			if (p == 0) {
				break;
			}
		}
		if (l == length) {
			inputsStruct = realloc(inputsStruct, (length+1)*sizeof(diffLines));
			inputsStruct[length].number = 1;
			inputsStruct[length].line = (char*)malloc(sizeof(inputs[k])*sizeof(char));
			strcpy(inputsStruct[length].line, inputs[k]);
			length++;
		}
		else {
			inputsStruct[l].number += 1;
		}
	}

	bubbleOnStruct(inputsStruct, length);

	printStruct(inputsStruct, length);

	freeArray(inputs, allLines);
	freeStruct(inputsStruct, length);


}


void readFile(int argc, char* argv[])
{	
	int j = 0;
	char ** inputs;
	inputs = (char**)malloc(buffer*sizeof(char*)); // FELSZABADÍTÁS
	if (inputs == NULL) {
		printf("Not enough memory!");
		exit(1);
	}
	int numberOfFiles = 1;
	while (numberOfFiles < argc) {
		FILE* fp;
		char* line = NULL;
		size_t len = 0;
		ssize_t read;

		fp = fopen(argv[numberOfFiles], "r");
		if (fp == NULL) {
			printf("File opening unsuccessful!");
		} else {
			while ((read = getline(&line, &len, fp)) != -1) {
				if (j >= buffer) {
					inputs = realloc(inputs, (j+1)*sizeof(char*));
					if (inputs == NULL) {
						printf("Not enough memory!");
						exit(1);
					}
				}
				inputs[j] = malloc(len*sizeof(char));
				if (inputs[j] == NULL) {
					printf("Not enough memory!");
					exit(1);
				}
			strcpy(inputs[j], line);	
			++j;	
			}
		free(line);
		fclose(fp);
		}
		++numberOfFiles;
	}
	countSimilarLines(inputs, j);
}



void readInput()
{

	int j = 0;
	char ** inputs;
	inputs = (char**)malloc(buffer*sizeof(char*)); // FELSZABADÍTÁS
	if (inputs == NULL) {
		printf("Not enough memory!");
		exit(1);
	}

		char* line = NULL;
		size_t len = 0;
		ssize_t read;

		while ((read = getline(&line, &len, stdin)) != -1) {
			if (j >= buffer) {
				inputs = realloc(inputs, (j+1)*sizeof(char*));
				if (inputs == NULL) {
					printf("Not enough memory!");
					exit(1);
				}
			}
			inputs[j] = malloc(len*sizeof(char));
			if (inputs[j] == NULL) {
				printf("Not enough memory!");
				exit(1);
			}
			strcpy(inputs[j], line);
		++j;	
		}
		free(line);
	countSimilarLines(inputs, j);
}
