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

	printf("%c\n", dp->d_type);

	if (dp != NULL) {

		printf("%d\n", dp->d_type);
        /*if (strcmp((char*)dp->d_type,"DT_DIR")) {
            closedir(directory);
            printf("Found as a directory\n");
            return "FOUND";
        }*/
        /*else{
	       if (strcmp((char*)dp->d_type,"DT_REG")) {
	            closedir(directory);
	            printf("Found as a file\n");

	            return "FOUND";
	        }
		}

*/
		return "FOUND";
	}
	else{
	    printf("File or directory not found\n");

	    return "NOTFOUND";
	}
}

//Open a directory
DIR* openDirectory (char* directory){
	printf("Printing a run test\n");

	if (opendir(directory)){

		DIR* direction = opendir(directory);
		printf("Printing a second run test\n");

		readADirectory(direction);
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
	openDirectory("/home/brayan/SOProyecto1/");

	return 0;
}