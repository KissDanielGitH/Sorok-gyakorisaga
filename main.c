#include <stdio.h>
#include "functions.h"


int main(int argc, char* argv[]) {
	
	if (argc < 2) {
		readInput();
	}
	else {
		readFile(argc, argv);
	}


	return 0;
}
