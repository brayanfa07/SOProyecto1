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
	char newDirectory[100];

	if ((direction= opendir(directory)) != NULL){

		while ((dp = readdir(direction)) != NULL){

			//Compare if the dp--> d_type is a file
			if (dp->d_type == DT_REG){
				printf ("File found --> %s\n", dp->d_name);
			}

			else {
				//Compare if the dp--> d_type is a directory or folder

				printf("\n");
				if (dp->d_type == DT_DIR){

					//Compare if the directory is . or ..
					if ( (strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0) || (strcmp(dp->d_name,".git")) == 0) {
						printf("+++++++++++ Directory found with . or .. or .git %s\n\n", dp->d_name);
		            }

		            //Compare if the directory is not a . or ..
                    else{
		            	printf("Directory found --> %s\n", dp->d_name);			
		                strcpy(newDirectory, directory);
		                strcat(newDirectory, "/");
		                strcat(newDirectory, dp->d_name);

		                printf("New Route for new directory defined --> %s\n", newDirectory);

		                openDirectory(newDirectory);
					}
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
	openDirectory("/home/brayan/SOProyecto1");

	return 0;
}