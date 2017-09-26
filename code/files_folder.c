//File that includes yhe methods related with the manipulation of directories and files


#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


/*Read a directory
Input: DIR pointer, returned from openDirectory
Output: A printing 
*/


/*Open a directory method
ENTRY:  A directory
Output: a DIR* Pointer
*/
struct dirent* openDirectory (char* directory){

	DIR* direction;
	struct dirent *dp;

	if ((direction= opendir(directory)) != NULL){

		while ((dp = readdir(direction)) != NULL){

			printf ("%s\n", dp->d_name);	
		}
		closedir(direction);
		return dp;
	}
	else{
		printf("Its not possible open the directory\n");
	}
		return dp;
}


//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory\n");
	openDirectory("/home/brayan/SOProyecto1/code");

	return 0;
}