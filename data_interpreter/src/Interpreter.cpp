#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "General.h"

using namespace std;

// usage
// ./Interpreter < "sdcardfile" > ouput.txt

/*
 * We will work off redirected input
 */
int main(int argc, char* argv[]){
	vector<struct Reading*> *readings = new vector<struct Reading*>();
	while(!feof(stdin))
		readings->push_back( (struct Reading*) getInput(10) );

    //(*readings)[0]->date.year();
	/*
	int size = readings->size();
	printf("Number of readings: %d\n", size);
	printf("-------------------\n");
	printf("Last five readings;\n");
	printf("First reading = %3.2f at time = %2d/%2d %2d:%2d:%2d\n",
	(*readings)[ 0 ]->temperature, (*readings)[0]->date.month(), (*readings)[0]->date.day(), (*readings)[0]->date.hour(), (*readings)[0]->date.minute(), (*readings)[0]->date.second());
	for(int i = 0; i < 5; i++)
		printf("Temperature = %3.2f at time = %2d/%2d %2d:%2d:%2d\n",
		(*readings)[ size-i-1 ]->temperature, (*readings)[size-i-1]->date.month(), (*readings)[size-i-1]->date.day(), (*readings)[size-i-1]->date.hour(), (*readings)[size-i-1]->date.minute(), (*readings)[size-i-1]->date.second());

	for(int i = 1; i < argc; i++)
		printf("Temperature = %3.2f at time = %2d/%2d %2d:%2d:%2d\n",
		(*readings)[ atoi(argv[i]) ]->temperature, (*readings)[atoi(argv[i])]->date.month(), (*readings)[atoi(argv[i])]->date.day(), (*readings)[atoi(argv[i])]->date.hour(), (*readings)[atoi(argv[i])]->date.minute(), (*readings)[atoi(argv[i])]->date.second());*/

	for(int i = 0; i < readings->size()-1; i++)
		printf("%f\n", (*readings)[i]->temperature);
		//printf("%3.2f %2d/%2d %2d:%2d:%2d\n",
		//(*readings)[i]->temperature, (*readings)[i]->date.month(), (*readings)[i]->date.day(), (*readings)[i]->date.hour(), (*readings)[i]->date.minute(), (*readings)[i]->date.second());
};
