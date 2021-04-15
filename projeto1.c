#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char codigo[4];
    char nome[26];
    char endereco[26];
    char cidade[21];
    char estado[3];
}cadastro;

char *trimstring(char *string){
    char *fim;

    fim = string + strlen(string) - 1;
    while(fim > string && isspace((unsigned char)*fim))
        fim--;

    fim[1] = '\0';

    return string;
}

/*
 * 
 */
int main(int argc, char** argv) {
    cadastro pessoa[500];
    
    FILE * entrada;
    entrada = fopen("cadastro.txt", "r");
    if(entrada == NULL){
        printf("ERRO ABERTURA");
        return 1;
    }
    
    FILE * escritadelim;
    escritadelim = fopen("cad_delimitador.txt", "w");
    if(escritadelim == NULL){
        printf("ERRO ABERTURA");
        return 1;
    }
    
    FILE * escritaindic;
    escritaindic = fopen("cad_ind_tamanho.txt", "w");
    if(escritaindic == NULL){
        printf("ERRO ABERTURA");
        return 1;
    }
    
    char aux;
    for(int id=0; id<500; id++){
        for(int i=0; i<3; i++){
            aux = fgetc(entrada);
            pessoa[id].codigo[i] = aux;
        }
        pessoa[id].codigo[3] = '\0';
        trimstring(pessoa[id].codigo);
        
        for(int i=0; i<25; i++){
            aux = fgetc(entrada);
            pessoa[id].nome[i] = aux;
        }
        pessoa[id].nome[25] = '\0';
        trimstring(pessoa[id].nome);

        for(int i=0; i<25; i++){
            aux = fgetc(entrada);
            pessoa[id].endereco[i] = aux;
        }
        pessoa[id].endereco[25] = '\0';
        trimstring(pessoa[id].endereco);
        
        for(int i=0; i<20; i++){
            aux = fgetc(entrada);
            pessoa[id].cidade[i] = aux;
        }
        pessoa[id].cidade[20] = '\0';
        trimstring(pessoa[id].cidade);
        
        for(int i=0; i<2; i++){
            aux = fgetc(entrada);
            pessoa[id].estado[i] = aux;
        }
        pessoa[id].estado[2] = '\0';
        trimstring(pessoa[id].estado);
        
        fseek(entrada, 1, SEEK_CUR);
    }
    
    for(int i=0; i<500; i++){
        fprintf(escritadelim, "#%s|%s|%s|%s|%s|",   pessoa[i].codigo,
                                                    pessoa[i].nome,
                                                    pessoa[i].endereco,
                                                    pessoa[i].cidade,
                                                    pessoa[i].estado);
    }
    
    for(int i=0; i<500; i++){
        fprintf(escritaindic, "%03i%s%03i%s%03i%s%03i%s%03i%s", strlen(pessoa[i].codigo), pessoa[i].codigo,
                                                                strlen(pessoa[i].nome), pessoa[i].nome,
                                                                strlen(pessoa[i].endereco), pessoa[i].endereco,
                                                                strlen(pessoa[i].cidade), pessoa[i].cidade,
                                                                strlen(pessoa[i].estado), pessoa[i].estado);
    }
    
    fclose(entrada);
    fclose(escritadelim);
    fclose(escritaindic);
    
    return (EXIT_SUCCESS);
}
