//File that includes yhe methods related with the manioulation of directories and files


#include "dirent.h"
#include "stdio.h"


//Open a directory
int openDirectory (){

	if (opendir("/home/brayan/SOProyecto1")){

		DIR* direction = opendir("/home/brayan/SOProyecto1");
		printf("%s\n", (char*) direction);
		return 0;
	}
	else{
		printf("ERROR: Could not open directory");
	}
}



int main(int argc, char const *argv[])
{
	openDirectory();



	return 0;
}