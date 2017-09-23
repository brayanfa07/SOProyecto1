//File that includes yhe methods related with the manipulation of directories and files


#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"


//Open a directory
DIR* openDirectory (){
	printf("Printing a run test\n");

	if (opendir("/home/brayan/SOProyecto1/")){

		DIR* direction = opendir("/home/brayan/SOProyecto1/");
		printf("Printing a second run test\n");

		return direction;
	}
	else{
		printf("ERROR: Could not open directory");
	}
}


//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory\n");
	openDirectory();

	return 0;
}