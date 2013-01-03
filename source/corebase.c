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

//Variables
char NAME[] = "open3G";
char VERSION[] = "0.5 beta";
char DESCR[] = "Discador 3G";

int desconectar(){
    printf("\nDesconectando...\n");
    log("Desconectando.");
    //char id[]="kill -15 ", busc[10]="vazio", resultado[20];
    int o;
    //printf("pppd PID: %d\n\n",pppID);
    /*system("pgrep pppd | tail -1 > /var/log/open3g.log &");
    sleep(5);
    log("Salvando o PID do pppd. (functions.desconectar)");
    FILE *djlog=fopen("/var/run/ppp0.pid","r");
    log("Abrindo o LOG do PID. (functions.desconectar)");
    fgets(busc,10,djlog);
    log("Pegando o PID do pppd no log. (functions.desconectar)");
    fclose(djlog);
    sprintf(resultado,"%s%s",id,busc);
    //printf("pppd PID: %s\n\n",busc);*/
    if (pppID == 0){ //strcmp("vazio",busc)==0){
        printf("Nenhum processo pppd encontrado. Saindo...\n\n");
        exit(0);
    } else {
        //o = system(resultado);
    	o = kill(pppID,SIGTERM);
        log("Enviado o comando para encerrar o pppd. (functions.desconectar)");
        if(o==0) exit(0);
        log("Abrindo o LOG do PID novamente. (functions.desconectar)");
        //strcpy(id,"kill -9 ");
        //sprintf(resultado,"%s%s",id,busc);
        //system(resultado);
        o = kill(pppID,SIGTERM);
        log("Forçando encerramento do pppd. (functions.desconectar)");
        exit(0);
    }
}

int findMod(){
    FILE *mod1=fopen("/dev/ttyACM0","r");
    FILE *mod2=fopen("/dev/ttyUSB0","r");
    FILE *mod3=fopen("/dev/ttyACM1","r");
    FILE *mod4=fopen("/dev/ttyUSB1","r");
    log("Modem: Tentando localizar em tty USB/ACM 0/1. (functions.findMod)");
    printf("Localizando o modem: ");

    if(mod1==NULL){
        if(mod2==NULL){
            if(mod3==NULL){
                if(mod4==NULL){
                    printf("Modem nao encontrado. Tente novamente.\n");
                    log("ERRO: Modem NÃO encontrado em nenhum tty. (functions.findMod)");
                    exit(0);
                }
                else{
                    printf("Modem encontrado em /dev/ttyUSB1.\n");
                    log("Modem encontrado em /dev/ttyUSB1. (functions.findMod)");
                    return 4;
                }
            }
            else{
                printf("Modem encontrado em /dev/ttyACM1.\n");
                log("Modem encontrado em /dev/ttyACM1. (functions.find-mod)");
                return 3;
            }
        }
        else{
            printf("Modem encontrado em /dev/ttyUSB0.\n");
            log("Modem encontrado em /dev/ttyUSB0. (functions.findMod)");
            return 2;
        }
    }
    else{
        printf("Modem encontrado em /dev/ttyACM0.\n");
        log("Modem encontrado em /dev/ttyACM0. (functions.findMod)");
        return 1;
    }
}

int findModem(int par){
    char buffer[501], *resulta;
    int ch;
    printf("\nEncontrando seu modem...");
    log("Encontrando seu modem. (functions.findModem)");
    system("lsusb > /var/log/open3g.log");
    log("Jogando dados dos dispositivos para log. (functions.findModem)");
    FILE *oplog=fopen("/var/log/open3g.log","r");
    while(fgets(buffer,501,oplog)!=NULL){
        resulta = strstr(buffer,"0fce:d0cf");
        log("Buscando no LOG. (functions.findModem)");
        if (resulta!=NULL){
            printf("OK\n\n");
            printf("Sony Ericsson MD300 encontrado.\n");
            log("Sony Ericsson MD300 encontrado. (functions.findModem)");
            if(par==1){
            printf("Escrevendo regras para udev...");
            FILE *rules;
            rules=fopen("/etc/udev/rules.d/50-md300modem.rules","w");
            char var[3];
            strcpy(var,"%p");
            fprintf(rules,"#claro-3g script\n"
                       "ACTION!=\"add\", GOTO=\"3G_End\"\n"
                       "BUS==\"usb\", SYSFS{idProduct}==\"d0cf\", "
                       "SYSFS{idVendor}==\"0fce\", NAME=\"modem\" "
                       "PROGRAM=\"/bin/sh -c '"
                       "echo 3 > /sys/%s/device/bConfigurationValue'\"\n"
                       "LABEL=\"3G_End\"",var);
            fclose(rules);
            printf("OK.\n");
            printf("Reiniciando UDEV...");
            log("Regras para UDEV escritas. (functions.findModem)");
            //system("service udev restart");
            //sleep(30);
            printf("OK.\n");
            }
            findMod();
            return 1;
        } else {
            resulta=NULL;
            resulta = strstr(buffer,"12d1:1003");
            if (resulta!=NULL){
            printf("OK\n\n");
            printf("Huawei E220 encontrado.\n");
            log("Modem Huawei E220 encontrado. (functions.findModem)");
            if(par==1){
            printf("Escrevendo regras para udev...");
            FILE *rules;
            rules=fopen("/etc/udev/rules.d/99_huawei.rules","w");
            fprintf(rules,"SUBSYSTEM==\"block\", \\\n"
                      "ACTION==\"add\", \\\n"
                      "SYSFS{idVendor}==\"12d1\", \\\n"
                      "SYSFS{idProduct}==\"1003\", \\\n"
                      "OPTIONS=\"ignore_device\"\n\n"
                      "SUBSYSTEM==\"usb\", \\\n"
                      "SYSFS{idVendor}==\"12d1\", \\\n"
                      "SYSFS{idProduct}==\"1003\", \\\n"
                      "RUN+=\"/sbin/modprobe usbserial vendor=0x12d1 product=0x1003\"");
            fclose(rules);
            printf("OK.\n");
            printf("Reiniciando UDEV...");
            system("service udev restart");
            log("Regras para UDEV escritas. (functions.findModem)");
            sleep(30);
            printf("OK.\n");
            return 2;
            } else {
                resulta=NULL;
                resulta = strstr(buffer,"19d2:0001");
                if (resulta!=NULL){
                printf("OK\n\n");
                printf("Onda Communication MSA501HS encontrado.\n");
                log("Onda Communication MSA501HS encontrado. (functions.findModem)");
                if(par==1){
                printf("Escrevendo regras para udev...");
                FILE *rules;
                rules=fopen("/etc/udev/rules.d/10-onda-msa501hs.rules","w");
                fprintf(rules,"ACTION!=\"add\", GOTO=\"ONDA_End\"\n"
                               "SUBSYSTEM==\"usb\", SYSFS{idProduct}==\"2000\","
                               "SYSFS{idVendor}==\"19d2\", GOTO=\"ONDA_ZeroCD\"\n"
                               "SUBSYSTEM==\"usb\", SYSFS{idProduct}==\"0001\","
                               "SYSFS{idVendor}==\"19d2\", GOTO=\"ONDA_Modem\"\n"
                               "LABEL=\"ONDA_ZeroCD\"\n"
                               "RUN+=\"/usr/sbin/usb_modeswitch -d 1 -v 0x19d2 -p 0x2000 -V 0x19d2 -P 0x0001\"\n"
                               "LABEL=\"ONDA_Modem\"\n"
                               "RUN+=\"/sbin/modprobe usbserial vendor=0x19d2 product=0x0001\","
                               "MODE=\"660\", GROUP=\"tty\"\n"
                               "LABEL=\"ONDA_End\"");
                fclose(rules);
                printf("OK.\n");
                printf("Reiniciando UDEV...");
                system("service udev restart");
                log("Regras para UDEV escritas. (functions.findModem)");
                sleep(30);
                printf("OK.\n");
                return 2;
                } else {
                    resulta=NULL;
                    resulta = strstr(buffer,"1a8d:1002");
                    if (resulta!=NULL){
                    printf("OK\n\n");
                    printf("Modem BandLuxe C120 encontrado.\n");
                    log("Modem BandLuxe C120 encontrado. (functions.findModem)");
                    if(par==1){
                    printf("Escrevendo regras para udev...");
                    FILE *rules;
                    rules=fopen("/etc/udev/rules.d/10-onda-msa501hs.rules","w");
                    char var[3];
                    strcpy(var,"%p");
                    fprintf(rules,"ACTION!=\"add\", GOTO=\"hso_end\"\n"
                                   "SYSFS{idVendor}==\"1a8d\", SYSFS{idProduct}==\"1000\", RUN=\"/usr/bin/eject /dev/%s\"\n"
                                   "LABEL=\"hso_end\"",var);
                    fclose(rules);
                    printf("OK.\n");
                    printf("Reiniciando UDEV...");
                    system("service udev restart");
                    log("Regras para UDEV escritas. (functions.findModem)");
                    sleep(30);
                    printf("OK.\n");
                    return 2;
                    }
                  }
                }
              }
            }
            findMod();
            return 3;
        }
      }
    }
    printf("Modem nao suportado nativamente.\n");
    printf("Forcando a deteccao do modem...\n");
    log("ERRO: Modem não detectado. Buscar em /dev. (functions.findModem)");
    ch = findMod();
    if(ch==1) return 1;
    if(ch==2) return 2;
    if(ch==3) return 3;
    if(ch==4) return 4;
    return 0;
}

int conectar(int reconectar){
    printf("@ Conectando...\n");
    log("Conectando. (functions.conectar)");
    char buff[100],op_usr[100]="",op_pwd[100]="",op_apn[100]="",op_nbr[100]="";
    //char *opts[20];
    char op_op1[21]="",op_op2[21]="",op_op3[21]="",op_op4[21]="",op_op5[21]="";
    char op_op6[21]="",op_op7[21]="",op_op8[21]="",op_op9[21]="",op_op0[21]="";
    char place[21];
    char conn[1024];
    int i,o;
    FILE *conf=fopen("/etc/open3g/open3g.conf","r");

    if (conf==NULL){
        printf("\n@ Erro ao abrir arquivo de configuração.\n");
        exit(0);
    } else {
        printf("@ Arquivo de configuração aberto para leitura.\n@ ");
        while (fgets(buff,100, conf) != NULL){
            if (strstr(buff,"//")) continue; //pula uma linha comentada com: //
            if (strstr(buff,"USR")) {
                sscanf(buff,"%*s %*s %s",op_usr);
                continue;
            }
            if (strstr(buff,"PWD")) {
                sscanf(buff,"%*s %*s %s",op_pwd);
                continue;
            }
            if (strstr(buff,"APN")) {
                sscanf(buff,"%*s %*s %s",op_apn);
                continue;
            }
            if (strstr(buff,"NBR")) {
                sscanf(buff,"%*s %*s %s",op_nbr);
                continue;
            }
            if (strstr(buff,"OP1")) {
                sscanf(buff,"%*s %*s %s",op_op1);
                continue;
            }
            if (strstr(buff,"OP2")) {
                sscanf(buff,"%*s %*s %s",op_op2);
                continue;
            }
            if (strstr(buff,"OP3")) {
                sscanf(buff,"%*s %*s %s",op_op3);
                continue;
            }
            if (strstr(buff,"OP4")) {
                sscanf(buff,"%*s %*s %s",op_op4);
                continue;
            }
            if (strstr(buff,"OP5")) {
                sscanf(buff,"%*s %*s %s",op_op5);
                continue;
            }
            if (strstr(buff,"OP6")){
                sscanf(buff,"%*s %*s %s",op_op6);
                continue;
            }
            if (strstr(buff,"OP7")){
                sscanf(buff,"%*s %*s %s",op_op7);
                continue;
            }
            if (strstr(buff,"OP8")){
                sscanf(buff,"%*s %*s %s",op_op8);
                continue;
            }
            if (strstr(buff,"OP9")){
                sscanf(buff,"%*s %*s %s",op_op9);
                continue;
            }
            if (strstr(buff,"OP0")){
                sscanf(buff,"%*s %*s %s",op_op0);
                continue;
            }
        }
    fclose(conf);

    o = findMod();
    if(o==1) strcpy(place,"/dev/ttyACM0");
    if(o==2) strcpy(place,"/dev/ttyUSB0");
    if(o==3) strcpy(place,"/dev/ttyACM1");
    if(o==4) strcpy(place,"/dev/ttyUSB1");

    //encerrando qualquer processo anterior
    //system("killall -q pppd");
    printf("@ Iniciando o pppd...");

    //criando os arqumentos para o execv
    sprintf(conn,"/usr/sbin/chat "
               "TIMEOUT 300 ABORT \"BUSY\" ABORT "
               "\"NO DIALTONE\" ABORT \"NO CARRIER\" \"\" "
               "ATZ OK AT+cfun=1 OK AT+CGDCONT=1,\"IP\","
               "\"%s\" -T ATDT%s CONNECT",op_apn,op_nbr);

    char *args[] = {"/usr/sbin/pppd",place,"460800",op_op1,op_op2,op_op3,op_op4,op_op5,op_op6,op_op7,op_op8,op_op9,op_op0,"user",op_usr,"password",op_pwd,"connect",conn,(char *) 0};
    //op_op1,op_op2,op_op3,op_op4,op_op5,op_op6,op_op7,op_op8,op_op9,op_op0

    //tentativas de conexao
	for(i=1;i<=5;i=i+1){
        printf("\n@ Tentativa de discagem %d\n",i);
        // system(conn);
        pid_t pID = vfork();
        pppID = 0;
        pppID = pID + 1;
        if (pID == 0)                // processo filho para chamar o pppd
           {
               execv("/usr/sbin/pppd",args);
               _exit(0);
           }
        else if (pID < 0)            // fork falhou
           {
               printf("Fork falhou.\n\n");
               exit(1);
           }
        else                                   // parent
           {
        	//int childExitStatus;
        	//pid_t ws = waitpid( pID, &childExitStatus, 0);
        	sleep(15);
			log("Comando pppd enviado. (functions.conectar)");
			//verifica se pegou IP
			conf=fopen("/var/log/open3g.log","w");
			fclose(conf);
			system("echo \"`ifconfig ppp0 | grep inet | cut -d \":\" -f 2 | tr -d a-z,A-Z,-`\" > /var/log/open3g.log &");
			sleep(3);
			log("IP escrito no log. (functions.conectar)");
			conf=fopen("/var/log/open3g.log","r");
			fgets(buff, 16, conf);
			log("Recuperado IP gravado no log. (functions.conectar)");
			fclose(conf);
			if (strlen(buff)>7){
			    if (reconectar==1) monitorar(1);
			    else monitorar(0);
			}
			system("killall -q pppd");
			//kill(pppID,SIGTERM);
			if (i==5){
				printf("@ Não foi possível conectar, tente novamente.\n");
				exit(0);
			}
           }
		}
    }
    return 0;
}

int instalar(int option){
    log("Instalar. (functions.instalar)");
    int opc, pap_chap = 0;
    char modem[21], oper[21],usr[100],pwd[100],apn[100],nbr[100];
    if (option==1){
        opc = findModem(1);
    } else {
        opc = findModem(2);
    }
    if(opc==1) strcpy(modem,"/dev/ttyACM0");
    if(opc==2) strcpy(modem,"/dev/ttyUSB0");
    if(opc==3) strcpy(modem,"/dev/ttyACM1");
    if(opc==4) strcpy(modem,"/dev/ttyUSB1");
    log("Modem encontrado. (functions.instalar)");

    menu1:
        printf("\nQual sua operadora?\n\n");
        printf("1. Claro\n"
                "2. Tim\n"
                "3. Vivo\n"
                "4. Oi\n"
                "5. Giro\n"
                "6. Brasil Telecom\n"
        		"7. Sercomtel\n"
                "8. Inserir manualmente\n"
                "0. Sair\n\n>> ");
        scanf("%d",&opc);
        switch (opc){
            case 1:
                strcpy(oper,"claro");
                strcpy(usr,"claro");
                strcpy(pwd,"claro");
                strcpy(nbr,"*99***1#");
                strcpy(apn,"bandalarga.claro.com.br");
                break;
            case 2:
                strcpy(oper,"tim");
                strcpy(usr,"tim");
                strcpy(pwd,"tim");
                strcpy(nbr,"*99#");
                strcpy(apn,"tim.br");
                break;
            case 3:
                strcpy(oper,"vivo");
                strcpy(usr,"vivo");
                strcpy(pwd,"vivo");
                strcpy(nbr,"*99#");
                strcpy(apn,"zap.vivo.com.br");
                break;
            case 4:
                strcpy(oper,"oi");
                strcpy(usr,"oi");
                strcpy(pwd,"oi");
                strcpy(nbr,"*99***1#");
                strcpy(apn,"gprs.oi.com.br");
                break;
            case 5:
                strcpy(oper,"giro");
                strcpy(usr,"giro@giro.click21.com.br");
                strcpy(pwd,"giro");
                strcpy(nbr,"#777");
                strcpy(apn,"giro.click21.com.br");
                break;
            case 6:
                strcpy(oper,"brt");
                strcpy(usr,"brt");
                strcpy(pwd,"brt");
                strcpy(nbr,"*99#");
                strcpy(apn,"brt.br");
                break;
            case 7:
                strcpy(oper,"sercomtel");
                strcpy(usr,"sercomtel");
                strcpy(pwd,"4343");
                strcpy(nbr,"*99#");
                strcpy(apn,"sercomtel.com.br");
                break;
            case 8:
                printf("\n\n---------------------------------\n");
                printf("Digite os dados da sua operadora:\n\n");
                printf("Operadora: ");
                scanf("%s",oper);
                printf("\nUsuário: ");
                scanf("%s",usr);
                printf("\nSenha: ");
                scanf("%s",pwd);
                printf("\nNúmero de discagem: ");
                scanf("%s",nbr);
                printf("\nAPN: ");
                scanf("%s",apn);
                printf("\n\n");
                while ((pap_chap != 1) || (pap_chap != 2)){
                    printf("\033[1A");
                    printf("\033[K");
                	printf("Conectar usando [1]PAP ou [2]CHAP: ");
                	scanf("%d",&pap_chap);
                }
                break;
            case 0:
                exit(0);
            default:
                goto menu1;
        }
        log("Operadora selecionada. (functions.instalar)");
        printf("\n---------------------------------\n");
        printf("\nLimpando logs anteriores...");
        FILE *chk=fopen("/etc/open3g/open3g.conf","r");
        if(chk!=NULL){
            remove("/etc/open3g/open3g.conf");
            fclose(chk);
        }
        //se for reconfigurar não apagar o tráfego de dados
        if(option==2){
            chk=fopen("/etc/open3g/open3g_tx","r");
            if(chk!=NULL){
                remove("/etc/open3g/open3g_tx");
                fclose(chk);
            }
            chk=fopen("/etc/open3g/open3g_rx","r");
            if(chk!=NULL){
                remove("/etc/open3g/open3g_rx");
                fclose(chk);
            }
        }
        printf("OK\n");
        log("Arquivos anteriores apagados. (functions.instalar)");

        FILE *abre;
        abre=fopen("/var/log/open3g.log","w");
        fclose(abre);
        abre=fopen("/etc/open3g/open3g_tx","w");
        fclose(abre);
        abre=fopen("/etc/open3g/open3g_rx","w");
        fclose(abre);
        abre=fopen("/etc/open3g/open3g.conf","w");
        log("Arquivos novos criados. (functions.instalar)");

        if(abre==NULL){
            printf("Nao fo possivel abrir o arquivo de configuracao.\n\n");
            log("ERRO: Não fo possivel abrir o arquivo de configuração. (functions.instalar)");
            exit(0);
        }
        else{
            fprintf(abre,"#open3G - ");
            fprintf(abre,"%s\n\n",oper);
            fprintf(abre,"[%s]\n",oper);
            fprintf(abre,"MOD = %s\n",modem);
            fprintf(abre,"USR = %s\n",usr);
            fprintf(abre,"PWD = %s\n",pwd);
            fprintf(abre,"APN = %s\n",apn);
            fprintf(abre,"NBR = %s\n\n",nbr);
            fprintf(abre,"[PPPD CONFIG]\n");
            fprintf(abre,"OP1 = modem\n"
                         "OP2 = noauth\n"
                         "OP3 = crtscts\n"
                         "OP4 = defaultroute\n"
                         "OP5 = replacedefaultroute\n"
                         "OP6 = noipdefault\n"
                         "OP7 = usepeerdns\n"
                         "OP8 = nobsdcomp\n"
                         "OP9 = nodeflate\n");
	    if (opc==3){
                fprintf(abre,"OP0 = refuse-chap\n");
	    }
	    else {
		fprintf(abre,"OP0 = refuse-pap\n");
	    }
            fclose(abre);
        }

    printf("Configuracao concluida.\n");
    printf("Para conectar: [open3g -c] ou [open3g -p]\n\n");
    log("Configuração concluída. (functions.instalar)");
    return 0;
}

int usuario(){
      int isroot;
      isroot = getuid();
      if (isroot != 0)
        {
          printf("O programa precisa ser executado como root.\n");
          log("ERRO: Usuário não é o root. (functions.usuario)");
          exit(0);
      }
      return 0;
}

int zerar(){
    char z[2];
    FILE *to_clean;
    printf("\nTem certeza que deseja zerar os logs e contadores? [S/N]\n");
    scanf("%s",z);
    if((strcmp(z,"S")==0)||(strcmp(z,"s")==0)){
        to_clean = fopen("/var/log/open3g.log","w");
    	fclose(to_clean);
    	to_clean = fopen("/etc/open3g/open3g_rx","w");
    	fclose(to_clean);
      	to_clean = fopen("/etc/open3g/open3g_tx","w");
    	fclose(to_clean);
    	//system("echo \"\" > /var/log/open3g.log");
        //system("echo \"0\" > /etc/open3g/open3g_rx");
        //system("echo \"0\" > /etc/open3g/open3g_tx");
        printf("\n\nLogs e contadores zerados com sucesso.\n\n");
        log("Logs e contadores zerados. (functions.zerar)");
	exit(0);
    }
    else {
        printf("\n\nCancelado.\n\n");
        exit(0);
    }
}

int limpar(){
    //Limpa os arquivos do sistema
    remove("/etc/open3g/open3g.conf");
    remove("/var/log/open3g.log");
    remove("/var/log/main3g.log");
    remove("/etc/open3g/open3g_rx");
    remove("/etc/open3g/open3g_tx");
    remove("/etc/udev/rules.d/50-md300modem.rules ");
    remove("/etc/udev/rules.d/99_huawei.rules ");
    printf("\nArquivos apagados com sucesso.\n\n");
    exit(0);
}

int help(){
    printf("\nUso do programa:\n\n");
    printf("open3g -ARG1 -ARG2\n\n");
    printf("Máximo de 2 argumentos\n\n");
    printf("------------------------------------------------------\n");
    printf("ARGUMENTOS:\n\n");
    printf("open3g -c          ->    Faz a conexão\n");
    printf("open3g -r          ->    Reconfigura o programa\n");
    printf("open3g -i          ->    Instala o programa\n");
    printf("open3g -p          ->    Persistente: reconecta se cair\n");
    printf("open3g -d          ->    Encerra o pppd\n");
    printf("open3g -m          ->    Informacoes do seu modem\n");
    printf("open3g -t          ->    Trafego de dados total\n");
    printf("open3g -z          ->    Zera os logs e contadores\n");
    printf("open3g -u          ->    Apaga logs e configurações\n");
    printf("open3g -h          ->    Imprime esta tela\n");
    printf("open3g [OPT] -l    ->    Inicia sem o LOG\n");
    printf("------------------------------------------------------\n\n");
    exit(0);
}

int info(){
    printf("#  %s\n",NAME);
    printf("#  Versão: %s\n",VERSION);
    printf("#  %s\n\n",DESCR);
    printf("---\n\n");
    printf("Desenvolvedores:\n\n");
    printf("! Joao Batista Oliveira\n");
    printf("! Diego Pessanha\n\n");
    printf("! www.open-br.net\n");
    printf("! contato@open-br.net\n\n");
    printf("---\n\n");
    printf("Digite 'open3g -h' para obter ajuda com o uso.\n");
    printf("Se é a primeira utilizacao digite 'open3g -i'.\n\n");
    exit(0);
}

int title(){
    printf("\n----------------------------------------------------------------\n");
    printf("%s v%s - %s\n",NAME,VERSION,DESCR);
    printf("----------------------------------------------------------------\n\n");
    return 0;
}
