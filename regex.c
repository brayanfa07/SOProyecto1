#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 0x1000

const char* expresion;
const char* cadena;

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

/*
  Match the string in "to_match" against the compiled regular
  expression in "r".
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

int main (int argc, char *argv[]){
  expresion = "([[:digit:]]+)[^[:digit:]]+([[:digit:]]+)";
  cadena = "This 1 is nice 2 so 33 for 4254";

    regex_t r;
    const char* regex_text;
    
    printf ("Trying to find '%s' in '%s'\n", expresion, cadena);
    int compilado = compile_regex (& r, expresion);
    if(compilado == 0)
    {
      match_regex (& r, cadena, expresion);
      //regfree (& r);
    }
    else{
        printf ("No se pudo COMPILAR la ER.\n");
    }   
    
    regfree (& r);
    return 0;
}