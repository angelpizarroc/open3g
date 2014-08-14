/*
   open3G - 2009: João Batista Oliveira & Diego Pessanha

   Este é um software livre. Você pode redistribuir ou modificá-lo
   sob os termos da GNU General Public License. Este programa é distribuído
   na esperança de que possa ser útil, mas SEM NENHUMA GARANTIA.
   Veja a GNU General Public License para maiores informações.

   This program is a free software. You can redistribute it and/or modify
   it under the terms of the GNU General Public License. This program is
   distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY.
   See the GNU General Public License for more details.
*/

#include "functions.h"
#include "contents.h"

/**
 * Logs many steps into main3g.log
 **
 * @author	diego pessanha
 * @since	2009-02-20
 * @desc	write to main3g.log using log('something')
 **/
void logger(char *strlog){
    if(makelog==0){
    FILE *logFile=fopen("/var/log/main3g.log","a");
    fprintf(logFile,"%s - %s: %s\n",__DATE__,__TIME__,strlog);
    fclose(logFile);
    }
}

/**
 * Control LOG size
 **
 * @author	diego pessanha
 * @since	2009-02-20
 * @desc	erases it when it reaches the max size
 * @TODO	Left a few lines at the end of the LOG
 **/
int logCheck(){
    FILE *arquivo=fopen("/var/log/main3g.log","r");
    int tamanho;
    if (arquivo != NULL) {
        //Movimenta a posição corrente de leitura no arquivo para o seu fim
        fseek(arquivo, 0, SEEK_END);
        //Pega a posição corrente de leitura no arquivo
        tamanho = ftell(arquivo);
        if(tamanho>3145728){ //03 MB
            remove("/var/log/main3g.log");
        }
        fclose(arquivo);
    }
    return 0;
}
