//File that includes yhe methods related with the manipulation of directories and files


#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <string.h>

/*Read a directory
Input: DIR pointer, returned from openDirectory
Output: A printing 
*/
char* readADirectory(DIR* directory){

	struct dirent *dp = readdir(directory);

	if (dp->d_type != 0) {

		if(dp->d_type == DT_REG){
			printf("The directory stream sent is a directory\n");
		}
		else{
			printf("The directory stream sent is a file\n");
		}
		return "FOUND";
	}
	else{
	    printf("File or directory not found\n");

	    return "NOTFOUND";
	}
}

//Open a directory
DIR* openDirectory (char* directory){

	if (opendir(directory)){

		DIR* direction = opendir(directory);

		readADirectory(direction);
		return direction;
	}
	else{
		printf("ERROR: Could not open directory\n");
	}
}


//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory\n");
	openDirectory("/home/brayan/SOProyecto1");

	return 0;
}