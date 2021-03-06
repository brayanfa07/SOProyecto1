/*
 * Laboratorio 6.
 * Gabriel Ramírez Ramírez.
 * 
 * Compilar: gcc ej2.c -o ej2
 * Ejecutar: ./ej1 nombreDirectorio
 *
 *Ejemplos nombreDirectorio:
            - .
            - ./ 
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>
#include <time.h>

char* ruta; // Almacena la dirección del directorio.  

int esArchivo(const char *pRuta)
{
    struct stat path_stat;
    stat(pRuta, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

/*void extraerSubCadena(char cadena[], char subCadena[], int largo)
{
    //printf(" LARGO: %i \n", largo);
    int i, posicion, j, caracteresNombre = 0;
    for(i = (largo-1); i >= 0; i--){
        if (cadena[i] == '/'){
            posicion = (i + 1);
            i = -1; //Para salir del for.
        }
        caracteresNombre++;
    }
    int count = 0;
    j = posicion;
    while(count < (caracteresNombre - 1)){
        subCadena[count] = cadena[j];
        count++;
        j++;
    }
}*/    


int tieneSubdirectorio(const char *pRuta)
{
    if ( !strcmp(".", pRuta) || !strcmp("..", pRuta)) //No encuentra carpetas ni subCarpetas.
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void escribirArchivo(char *file)
{
    int fd;                 
    struct flock lock;      //Bloqueador del archivo

    fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    char linea[40] = "ESCRIBIENDO EN TODOS....";
  
    /* Inicializar la estructura del flock*/
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    
    /* Colocar la cerradura de escritura al archivo*/
    fcntl (fd, F_SETLKW, &lock);
    
    // Se escribe
    size_t length = strlen(linea);
    /* Escribir en el archivo */
    write(fd, linea, length);
    //fprintf(fd, "%c\n",'.');
    
    /*Soltar la cerradura*/
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    
    close(fd);
}



int desplegarDirectorio(const char *pNombreDir)
{
    struct dirent* dp;                   
    DIR *dir = opendir (pNombreDir);   
    
    if (dir == NULL)
    {
        if (esArchivo(pNombreDir))
        {
            //char cadena[100];
            //strcpy(cadena, pNombreDir);
            //char subCadena[50];
            //size_t largoCadena = strlen(cadena);
            //extraerSubCadena(cadena, subCadena, largoCadena);
            struct stat st;
            stat(pNombreDir, &st);
            int size = st.st_size;
            char* date;
            date = ctime(&st.st_mtime); // El Fyle System de Linux no almacena la fecha de creación.
            escribirArchivo(pNombreDir);  
            printf(" NOMBRE DE ARCHIVO: %s -- TAMAÑO: %i bytes -- FECHA MODIFICACION: %s \n", pNombreDir, size, date);
        }
                        
        else
        {
            printf("No se pudo abrir el directorio\n");
        }
        
        return -1;
    }
    else
    {
        printf("%s \n",pNombreDir);
        while ((dp = readdir(dir)) != NULL)
        {
            if (tieneSubdirectorio(dp->d_name))
            {

                char nuevaRuta[100];
                strcpy(nuevaRuta, pNombreDir);
                strcat(nuevaRuta, "/");
                strcat(nuevaRuta, dp->d_name);

                desplegarDirectorio(nuevaRuta);
            }
        }
    }
    
    closedir(dir);
    printf("%s *******************FIN*******************\n",pNombreDir);
    
}

int main(int argc, char *argv[])
{
    ruta = argv[1]; 
    desplegarDirectorio(ruta);    
}