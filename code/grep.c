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

				printf("\n");

				//Compare if the dp--> d_type is a directory or folder
				if (dp->d_type == DT_DIR){

					//Compare if the directory is . or ..
					if ( (strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0)) {
						printf("+++++++++++ Directory found with . or ..  %s\n\n", dp->d_name);
		            }

		            //Compare if the directory is not a . or ..
                    else{
		            	printf("Directory found --> %s\n", dp->d_name);			
		                strcpy(newDirectory, directory);
		                strcat(newDirectory, "/");
		                strcat(newDirectory, dp->d_name);

		                printf("New Route for new directory defined --> %s\n\n", newDirectory);

		                printf("====================  Introducing in other folder ... \n");
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

	printf("GREP method\n\n ========= Introduce variables like this:\n\ngrep [optiosn (-l or -r)] [regular expression] [file|folder] \n\n");
	
	printf("grep ");
	char typeMethod[20];
	char regularExpression [100];
	char directory [100];

	scanf(" %s %s %s", typeMethod, regularExpression, directory);

	printf("\n======> Values entered. TYPE METHOD: %s . REGULAR EXPRESSION: %s . DIRECTORY: %s\n\n", typeMethod, regularExpression, directory);
	
	if (strcmp(typeMethod, "-l") == 0){

		printf("-l: Method that search in a file until find a match with the regular expression \n\n" );

	}
	else{
		if (strcmp(typeMethod, "-r") == 0){

		printf("-r: Method that search in all the files and directories printing all the matches of the regular expression \n\n" );

		}
	}

	printf("It is possible run openDirectory method\n\n");
	openDirectory(directory);

	return 0;
}