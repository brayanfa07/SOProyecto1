#include "dirent.h"
#include "stdio.h"


int printFile (){

	//opendir(/home/brayan/SOProyecto1);

	char direccion = readdir("/home/brayan/SOProyecto1");
	
	printf("%s\n", direccion);

	return 0;
}



int main(int argc, char const *argv[])
{
	printFile();



	return 0;
}