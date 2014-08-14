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

int main(int argc, char *argv[]){

	//verifica número de argumentos
	if(argc>3){
		printf("\nErro: Muitos argumentos.\nConsulte open3g -h.\n\n");
		return(1);
	}

	//ignora um processo filho para nao virar zumbi
	signal(SIGCLD,SIG_IGN);

	//verifica se deve utilizar o log
	//if(strcmp("l",argv[2])==0) makelog=1;
	//if(strcmp("l",argv[2])==0) makelog=1;
	//if(strcmp("l",argv[3])==0) makelog=1;

	//verifica o arquivo de configuração
	//configCheck();
	//verifica se existem processos
	//processCheck();

	//verifica se o LOG atingiu o tamanho limite
	logCheck();

	logger("------------------------------------------------");
	title();

	//verifica se o usuário é o root
	usuario();
	logger("Verificou usuário.");

	char c = 0;
	int i;
	char *this_ip;
	for(i=0;i<argc;i++){
            c = getopt(argc, argv, "icrdtmpzuhg");
            if(c == -1) 
            {
                help();
                break;
            }
            switch(c){
                case 'h':
                        help();
                        break;
                case 'c':
                    conectar(1);
                    break;
                case 'r':
                    instalar(2);
                    break;
                case 'i':
                    instalar(1);
                    break;
                case 'z':
                    zerar();
                    break;
                case 'u':
                    limpar();
                    break;
                case 'd':
                    desconectar();
                    break;
                case 't':
                    trafegoTotal();
                    break;
                case 'm':
                    findModem(2);
                    break;
                case 'p':
                    conectar(0);
                    break;
                case 'g':
                    this_ip = ipGet();
                    printf("@ Seu IP é: \n");
                    printf("@ > %s  \n\n", this_ip);
                    break;
                default:
                    printf("%c : Parâmetro desconhecido.\n", c);
                    help();
                    exit(1);
            }
	}
    return 0;
}
