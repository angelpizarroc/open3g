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
 * Capture and threats the SIGINT (ctrl+c)
 **
 * @author	diego pessanha
 * @since	2009-02-01
 * @desc	ends the connection, child process and exit
 **/
void catch_int(int sig_num)
{
    signal(SIGINT, catch_int);
    desconectar();
    fflush(stdout);
    exit(0);
}

/**
 * Monitors the connection and try to reconnect
 **
 * @author	diego pessanha
 * @since	2009-02-01
 * @desc	check if ppp0 is up and:
 * - keeps monitoring ppd and call trafego() to monitor data transfer and catch_int() to monitor ctrl+c
 * - when disconnected kill child process and try to reconnect using conectar()
 **/
int monitorar(int persist){
    int i;
    i=fork();
    if(i==0)
    {
       //printf("Processo Filho\n");
       signal(SIGINT, catch_int);
       // entrando em um looping infinito para fazer nada.
       for ( ;; )
            pause();
    }
    else if(i>0)
    {
    char line[201]="vazio",*re=NULL;
    FILE *mon;
    int alive =1;
    printf("\n@ Data: %s Hora: %s\n",__DATE__,__TIME__);
    logger("Inicializando Monitor. (monitor.monitorar)");
    //sleep(10);
    //IPGET:
    system("echo \"`ifconfig ppp0 | grep inet | cut -d \":\" -f 2 | tr -d a-z,A-Z,-`\" > /var/log/open3g.log &");
    sleep(3);
    logger("IP escrito no log. (monitor.monitorar)");
    mon=fopen("/var/log/open3g.log","r");
    fgets(line, 16, mon);
    logger("Recuperado IP gravado no log. (monitor.monitorar)");
    printf("@ Seu IP é: %s\n",line);
    printf("@ pppd PIP: %d",pppID);
    fclose(mon);
    printf("\n\nTic-tac... Monitorando conexao...\n\n\n\n");
    logger("Monitorando Conexão. (monitor.monitorar)");
    while(alive==1){
        system("ps aux | grep pppd > /var/log/open3g.log &");
        sleep(5);
        mon=fopen("/var/log/open3g.log","r");
        if(mon==NULL){
            printf("\n\nNao foi possivel abrir o log.\n\n");
            logger("ERRO: Não possível abrir o log. (monitor.monitorar)");
        }
        else{
            fgets(line,201,mon);
            sleep(5);
            re = strstr(line,"tty");
            sleep(5);
            if(re==NULL){
                printf("\n@A conexao caiu.\n");
                logger("A conexão caiu. (monitor.monitorar)");
                if(persist==1) {
                	kill(i,SIGTERM);
                    alive=0;
                    exit(1);
                } else {
                    printf("@Tentando conectar novamente...\n\n");
                    kill(i,SIGTERM); //SIGKILL
                    conectar(0);
                }
            } else {
                trafego();
                sleep(10);
                alive=1;
                fclose(mon);
            }
        }
    }
    }
    return 0;
}
