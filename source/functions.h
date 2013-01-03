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

#ifndef _FUNCTIONS_H
#define	_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

//corebase.c - CoreBase
int conectar (int reconectar);
int desconectar ();
int findMod();
int findModem(int par);
int instalar(int option);
int usuario();
int zerar();
int limpar();
int help();
int info();
int title();

//monitor.c - Monitoring Module
void catch_int(int sig_num);
int monitorar(int persist);
//void processCheck(void);
char *ipGet();

//mainlog.c - Log System
void log(char *strlog);
int logCheck();

//coninfo.c - Connections information
int trafego();
int trafegoTotal();
int sinal();

#ifdef	__cplusplus
}
#endif

#endif	/* _FUNCTIONS_H */
