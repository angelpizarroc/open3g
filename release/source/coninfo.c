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

#include <sys/unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "functions.h"
#include "contents.h"

int trafego(){
    char trbytes[101], tp1[10], tp2[10];
    int tx, tx2, rx, rx2;
    //dados enviados
    FILE *pppstat= fopen("/sys/class/net/ppp0/statistics/tx_bytes","r");
    if(pppstat==NULL){
        printf("\033[2A");
        printf("\033[K");
        printf("Erro ao abrir arquivo log de dados.");
        log("ERRO: Não foi possível abrir arquivo tx de log de dados do ppp. (coninfo.trafego)");
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
        log("ERRO: Não foi possível abrir arquivo tx de log de dados do discador. (coninfo.trafego)");
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
        log("ERRO: Não foi possível abrir arquivo rx de log de dados do ppp. (coninfo.trafego)");
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
        log("ERRO: Não foi possível abrir arquivo rx de log de dados do discador. (coninfo.trafego)");
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
    printf("\033[K");	//Erase the line
    printf("Enviados: ");
    printf("%d %s",tx,tp1);
    printf("     |     Recebidos: ");
    printf("%d %s\n\n",rx,tp2);
    return 0;
}

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

int ipget(){
	char hostname[128];
	int i;
	struct hostent *h;
	struct in_addr **addr_list;
	struct in_addr addr;

	gethostname(hostname, sizeof hostname);
	printf("My hostname: %s\n", hostname);

	h = gethostbyname(hostname);

	if (h == NULL) { // do some error checking
		herror("gethostbyname"); // herror(), NOT perror()
		return 1;
	}

	// print information about this host:
	printf("Official name is: %s\n", h->h_name);
	printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)h->h_addr));
	printf("\n");

	printf("All addresses: ");
	addr_list = (struct in_addr **)h->h_addr_list;


	for(i = 0; addr_list[i] != NULL; i++) {
	   printf("%s ", inet_ntoa(*addr_list[i]));
	 }




	return 0;
}
