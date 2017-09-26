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
char* readADirectory(DIR* directory){

	struct dirent *dp = readdir(directory);

	if (dp->d_type != 0) {

		if(dp->d_type == DT_DIR){
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

/*Open a directory method
ENTRY:  A directory
Output: a DIR* Pointer
*/

DIR* openDirectory (char* directory){

	if (opendir(directory)){

		DIR* direction = opendir(directory);

		readADirectory(direction);
		return direction;
	}
	else{
		printf("ERROR: Could not open directory. It could be trying to open a file :/ \n");

		int fd;
		fd = open(directory, O_WRONLY);

		DIR * direction = fdopendir (fd);
		readADirectory(direction);
		return direction;
	}
}


//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory\n");
	openDirectory("/home/brayan/SOProyecto1/code/files_folder.c");

	return 0;
}