//File that includes yhe methods related with the manipulation of directories and files

#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


/*Open a directory method
ENTRY:  A directory
Output: a DIR* Pointer
*/
struct dirent* openDirectory (char* directory){

	DIR* direction;
	struct dirent *dp;
	char nuevaRuta[100];

	if ((direction= opendir(directory)) != NULL){

		while ((dp = readdir(direction)) != NULL){

			if (dp->d_type == DT_DIR){

				printf("Directory found 1 --> %s\n", directory);

				if (!((strcmp(dp->d_name, ".")) || !(strcmp(dp->d_name,"..")) || !(strcmp(dp->d_name,"/.")))) {

					printf("With . or .. --> %s\n", dp->d_name);			
	                strcpy(nuevaRuta, directory);
	                strcat(nuevaRuta, "/");
	                strcat(nuevaRuta, dp->d_name);

	                printf("New Route found --> %s\n", nuevaRuta);
	            }

                //openDirectory(nuevaRuta);
            }
            else{
            	if (dp->d_type == DT_REG){
					printf ("File found --> %s\n", dp->d_name);
				}
			}
		}
		closedir(direction);
		return dp;
	}
	else{
		printf("Its not possible open the directory\n\n");
	}
		return dp;
}


//Main function
int main(int argc, char const *argv[])
{
	printf("It is possible run openDirectory method\n\n");
	openDirectory("/home/brayan/SOProyecto1/code");

	return 0;
}