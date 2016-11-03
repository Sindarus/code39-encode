#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "code39.h"

int main(){
    char* line = NULL;
    size_t n_to_read = 0;
    char* converted_str = NULL;
    while(1){
        n_to_read = 0;
        printf("Entrez une chaine de charactère a encoder en code39, ou 0 pour quitter.\n");
        getline(&line, &n_to_read, stdin);
        line[strlen(line)-1] = '\0';        //remove terminating \n
        printf("Vous avez entré : %s\n", line);
        if(strcmp(line, "0") == 0){
            printf("Au revoir.");
            free(line);
            exit(EXIT_SUCCESS);
        }
        else if(is_codable(line)){
            converted_str = prepare_for_coding(line);
            printf("Votre chaine à encoder est : %s\n", converted_str);
            free(converted_str);
            converted_str = NULL;
        }
        else{
            printf("Votre chaine ne peut pas être encodée en code39.\n");
        }
        free(line);
        line = NULL;
    }
    return EXIT_SUCCESS;
}
