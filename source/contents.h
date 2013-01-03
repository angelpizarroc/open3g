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

#ifndef _CONTENTS_H
#define	_CONTENTS_H

#ifdef	__cplusplus
extern "C" {
#endif

//C headers
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>

int makelog;
int pppID;

#ifdef	__cplusplus
}
#endif

#endif	/* _CONTENTS_H */
