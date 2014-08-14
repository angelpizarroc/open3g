/*
   open3G - 2009: João Batista Oliveira & Diego Pessanha

   Este é um software gratuito. Você pode redistribuir ou modificá-lo
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
 * Capture transmitted and received data
 **
 * @author	diego pessanha
 * @since	2009-02-01
 * @desc	get data info from pppd logs and stores in open3g logs
 **/
int trafego(){
    char trbytes[101], tp1[10], tp2[10];
    int tx, tx2, rx, rx2;
    //dados enviados
    FILE *pppstat= fopen("/sys/class/net/ppp0/statistics/tx_bytes","r");
    if(pppstat==NULL){
        printf("\033[2A");
        printf("\033[K");
        printf("Erro ao abrir arquivo log de dados.");
        logger("ERRO: Não foi possível abrir arquivo tx de log de dados do ppp. (coninfo.trafego)");
        return 0;
    }
    fgets(trbytes, 101, pppstat);
    tx = atoi(trbytes);
    fclose(pppstat);
    pppstat = fopen("/etc/open3g/open3g_tx","r");
    if(pppstat==NULL){
        printf("\033[2A");
        printf("\033[K");
        printf("\nErro ao abrir arquivo log de dados.\n\n");
        logger("ERRO: Não foi possível abrir arquivo tx de log de dados do discador. (coninfo.trafego)");
        return 0;
    }
    fgets(trbytes, 101, pppstat);
    tx2 = atoi(trbytes);
    fclose(pppstat);
    tx2 = tx + tx2;
    FILE *txb2=fopen("/etc/open3g/open3g_tx","w");
    fprintf(txb2,"%d",tx2);
    fclose(txb2);
    //dados recebidos
    pppstat = fopen("/sys/class/net/ppp0/statistics/rx_bytes","r");
    if(pppstat==NULL){
        printf("\033[2A");
        printf("\033[K");
        printf("\nErro ao abrir arquivo log de dados.\n\n");
        logger("ERRO: Não foi possível abrir arquivo rx de log de dados do ppp. (coninfo.trafego)");
        return 0;
    }
    fgets(trbytes,101,pppstat);
    rx = atoi(trbytes);
    fclose(pppstat);
    pppstat = fopen("/etc/open3g/open3g_rx","r");
    if(pppstat==NULL){
        printf("\033[2A");
        printf("\033[K");
        printf("\nErro ao abrir arquivo log de dados.\n\n");
        logger("ERRO: Não foi possível abrir arquivo rx de log de dados do discador. (coninfo.trafego)");
        return 0;
    }
    fgets(trbytes,101,pppstat);
    rx2 = atoi(trbytes);
    fclose(pppstat);
    rx2 = rx + rx2;
    txb2 = fopen("/etc/open3g/open3g_rx","w");
    fprintf(txb2,"%d",rx2);
    fclose(txb2);
    //converte
    sprintf(tp1,"bytes");
    sprintf(tp2,"bytes");
    if (tx>1024){
        tx=tx/1024;
        sprintf(tp1,"KB");
    }
    if (tx>1024){
        tx=tx/1024;
        sprintf(tp1,"MB");
    }
    if (rx>1024){
        rx=rx/1024;
        sprintf(tp2,"KB");
    }
    if (rx>1024){
        rx=rx/1024;
        sprintf(tp2,"MB");
    }
    //Print data on screen
    printf("\033[2A");	//Move 2 lines up
    printf("\033[1A");	//Move 2 lines up
    printf("\033[K");	//Erase the line
    printf("Enviados: ");
    printf("%d %s",tx,tp1);
    printf("     |     Recebidos: ");
    printf("%d %s\n\n",rx,tp2);
    char *args[] = {"get_signal","sig","-d","/dev/ttyUSB1"};
    get_signal(4,args); 
    return 0;
}

/**
 * Shows stored data transfer information
 **
 * @author	diego pessanha
 * @since	2009-02-05
 * @desc	get data info from open3g logs
 **/
int trafegoTotal(){
    char trbytes[101], tp1[10], tp2[10];
    int tx, rx;
    //dados enviados
    FILE *pppstat = fopen("/etc/open3g/open3g_tx","r");
    fgets(trbytes, 101, pppstat);
    tx = atoi(trbytes);
    fclose(pppstat);
    //dados recebidos
    pppstat = fopen("/etc/open3g/open3g_rx","r");
    fgets(trbytes,101,pppstat);
    rx = atoi(trbytes);
    fclose(pppstat);
    //converte
    sprintf(tp1,"bytes");
    sprintf(tp2,"bytes");
    if (tx>1024){
        tx=tx/1024;
        if (tx>1024){
            tx=tx/1024;
            sprintf(tp1,"MB");
        } else sprintf(tp1,"KB");
    }
    if (rx>1024){
        rx=rx/1024;
        if (rx>1024){
            rx=rx/1024;
            sprintf(tp2,"MB");
        } else sprintf(tp2,"KB");
    }
    //imprime
    printf("\nTráfego total de dados até o momento:\n\n");
    printf("Enviados: ");
    printf("%d %s",tx,tp1);
    printf("     |     Recebidos: ");
    printf("%d %s\n\n",rx,tp2);
    printf("Para zerar o contador execute 'open3G -z'.\n\n");
    exit(0);
}
//TODO: Read signal from modem
int sinal(){
    return 0;
}

/**
 * Get the actual IP from chosen interface
 **
 * @author	diego pessanha
 * @since	2009-05-30
 * @desc	uses a socket to retrieve the actual IP from an interface
 **/
char *ipGet(){
	int fd;
	struct ifreq ifr;
	struct sockaddr_in saddr;

	fd=socket(PF_INET,SOCK_STREAM,0);
	strcpy(ifr.ifr_name,"ppp0"); //	specify which interface
	ioctl(fd,SIOCGIFADDR,&ifr);
	saddr=*((struct sockaddr_in *)(&(ifr.ifr_addr))); // is the address

	// saddr.sin_addr.s_addr contains the IP as an integer value
	// inet_ntoa -> converts the integer IP address to the standard with points
	//printf("\nOpen3G IpGet :: Your Ip\n");
	//printf(">>>>>>>> %s \n\n",inet_ntoa(saddr.sin_addr));

	return inet_ntoa(saddr.sin_addr);
}
