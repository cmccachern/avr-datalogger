#include <stdlib.h>
#include <stdio.h>

#include "General.h"

char *getInput(int length){
	char *buffer = new char[length];
	for(int i = 0; i < length; i++)
		buffer[i] = getchar();
	return buffer;
};
