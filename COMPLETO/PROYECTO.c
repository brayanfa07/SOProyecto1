//File that includes yhe methods related with the manipulation of directories and files

#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "threadpool.h"


struct arg_structure args;
/*
	Manejar Archivos.
*/		
/*Compile method
ENTRY:  regex, regular expression
Output: a integer 1: Invalid.
				  2: Correct.
*/

void* readLine(void* p_args)
{
	struct arg_structure *args = (struct arg_structure *) p_args;
	match_regex(args.reg, args.line, args.expresionRegular);
    
}


/*
	Regular Expression.
*/		
/*Compile method
ENTRY:  regex, regular expression
Output: a integer 1: Invalid.
				  2: Correct.
*/
static int compile_regex (regex_t* r, const char* regex_text){
    int status = regcomp (r, regex_text, REG_EXTENDED);
    if (status != 0) {
  char error_message[MAX_ERROR_MSG];
  regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n", regex_text, error_message);
        return 1;
    }
    return 0;
}

/*Match method
ENTRY:  regex, text, regular expression.  
Output: a integer 1: FOUND.
				  2: NO FOUND.
*/
static int match_regex (regex_t* r, const char* to_match, const char* er){
  int res = regexec(r, to_match, 0, NULL, 0); 
    if (!res){
      printf ("Encontrada....'%s' in '%s'\n", er, to_match);
      return 1;
      /* code */
    }
    else{
      printf ("No Encontrada....'%s' in '%s'\n", er, to_match);
      return 0;
      /* code */
    }
}



/*
	Directories.
*/	

/*Open a directory method L
ENTRY:  A directory
Output: a DIR* Pointer
*/
struct dirent* openDirectoryForL(char* directory, char* expresion){

	DIR* direction;
	struct dirent *dp;
	char newDirectory[100];
	//struct arg_structure args;

	if ((direction= opendir(directory)) != NULL){

		while ((dp = readdir(direction)) != NULL){

			//Compare if the dp--> d_type is a file
			if (dp->d_type == DT_REG){
				printf ("File found --> %s\n", dp->d_name);
				args.filename = directory;
				args.expresionRegular = expresion;	
				int fd;
			    char * line = NULL;
			    size_t len = 0;
			    ssize_t read;                 
			    struct flock lock;      //Bloqueador del archivo

			    fd = open(args.filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);  
			    /* Inicializar la estructura del flock*/
			    memset(&lock, 0, sizeof(lock));
			    lock.l_type = F_WRLCK;
			    
			    /* Colocar la cerradura de escritura al archivo*/
			    fcntl (fd, F_SETLKW, &lock);

			    while ((read = getline(&line, &len, fp)) != -1) {
			    	args.line = line;
			    	add_job_request(i, (void*) readLine, (void *)&args, &got_job_request, &request_mutex);
			        printf("Reading: %zu :\n", read);
			        printf("%s", line);
			    }

			    /*Soltar la cerradura*/
			    lock.l_type = F_UNLCK;
			    fcntl (fd, F_SETLKW, &lock);
			    
			    close(fd);
				add_job_request(i, (void*) file_process, (void *)&args, &got_job_request, &request_mutex);
				//CÓDIGO para llamar a abrir archivo
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

/*Open a directory method R
ENTRY:  A directory
Output: a DIR* Pointer
*/
struct dirent* openDirectoryForR(char* directory, char* expresion){

	DIR* direction;
	struct dirent *dp;
	char newDirectory[100];
	//struct arg_structure args;

	if ((direction= opendir(directory)) != NULL){

		while ((dp = readdir(direction)) != NULL){

			//Compare if the dp--> d_type is a file
			if (dp->d_type == DT_REG){
				printf ("File found --> %s\n", dp->d_name);
				args.filename = directory;
				add_job_request(i, (void*) file_process, (void *)&args, &got_job_request, &request_mutex);
				//CÓDIGO para llamar a abrir archivo
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
		int rc;
        rc = pthread_mutex_lock(&request_mutex);
        done_creating_jobRequests = 1;
        rc = pthread_cond_broadcast(&got_job_request);
        rc = pthread_mutex_unlock(&request_mutex);
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
	regex_t r;

	//Creación del POOL de Hilos.
	int  i;                               
    int thr_id[NUM_THREADS_IN_POOL];      
    pthread_t  threadPool[NUM_THREADS_IN_POOL];
    args.reg = r;

    for (i = 0; i < NUM_THREADS_IN_POOL; i ++)
    {
    	thr_id[i] = i;
    	pthread_create(&threadPool[i], NULL, handle_Job_Requests, (void*)&thr_id[i]);
    }

	scanf(" %s %s %s", typeMethod, regularExpression, directory);

	printf("\n======> Values entered. TYPE METHOD: %s . REGULAR EXPRESSION: %s . DIRECTORY: %s\n\n", typeMethod, regularExpression, directory);

	printf ("Verifying Regular Expression '%s' \n", regularExpression);
    int compilado = compile_regex (& r, regularExpression);
    args.reg = r;
    if(compilado == 0)
    {
        //match_regex (& r, cadena, regularExpression);

		if (strcmp(typeMethod, "-l") == 0){

			printf("-l: Method that search in a file until find a match with the regular expression \n\n" );
			openDirectoryForL(directory);

		}
		else{
			if (strcmp(typeMethod, "-r") == 0){

			printf("-r: Method that search in all the files and directories printing all the matches of the regular expression \n\n" );
			openDirectoryForR(directory);

			}
		}
    }
    else{
        printf ("Regular Expression is invalid. \n");
    }
	


	//printf("It is possible run openDirectory method\n\n");
	//openDirectory(directory);
	for (i = 0; i < NUM_THREADS_IN_POOL; i ++) 
	{
	   	void* thr_retval;
	  	pthread_join(threadPool[i], &thr_retval);
	}

	return 0;
}