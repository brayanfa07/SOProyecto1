//File that includes yhe methods related with the manipulation of directories and files


#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"


//Open a directory
DIR* openDirectory (char directory){
	printf("Printing a run test\n");

	if (opendir(directory)){

		DIR* direction = opendir(directory);
		printf("Printing a second run test\n");

		return direction;
	}
	else{
		printf("ERROR: Could not open directory");
	}
}

//char* readADirectory(DIR* directory){




//}




//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory\n");
	openDirectory("/home/brayan/SOProyecto1/");

	return 0;
}