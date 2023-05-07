#include <stdlib.h>
#include <string.h>

int splitcount(char* string, char separator){
	int i;
	int count = 1;
	for(i = 0; i < strlen(string); i ++){
		if(*(string + i) == separator)
			count ++;
	}
	return count;
}

char* _split(char* string, char separator, int pos){
	static char* ret;
	int i;
	int c = 0;
	int currentpos = 0;
	ret = realloc(ret, strlen(string) + 1);
//																			printf("\n\nstring: .%s.", string);
//																			printf("\nmalloc: %i", strlen(string));
	//zera ret
	for(i = 0; i < strlen(string) + 1; i ++)
		*(ret + i) = '\0';
//																			printf("\nini ret: .%s.\n", ret); //debugj
	for(i = 0; i < strlen(string); i ++){
		if(currentpos == pos && *(string + i) != separator){
			*(ret + c) = *(string + i);
			c ++;
//																			printf("%c", *(string + i)); //debug
		}
		if(*(string + i) == separator){
			currentpos ++;
			if(currentpos > pos)
				break;
		}
	}
	
//																			printf("\nret: .%s.", ret);
		
	return ret;
}

char* removeFirstSplit(char* string, char separator){
	static char* ret;
	int i, z;
	
	ret = realloc(ret, strlen(string) + 1);
	
	//zera ret;
	for(i = 0; i < strlen(string) + 1; i ++)
		*(ret + i) = '\0';
	
	z = splitcount(string, ' ');
	for(i = 1; i < z; i ++){
		strcat(ret,  _split(string, ' ', i));
		if(i < z - 1){
			*(ret + strlen(ret)) = ' ';
			*(ret + strlen(ret)) = '\0';
		}
	}
	
	return ret;
}

int instr(int ipos, char* str1, char* str2){
	int i; //caracteres em str1
	int z; //caracteres em str2
	
	if(ipos >= strlen(str1)) //posição inicial nao pode ser maior que str1.length
		return -2;
	
	for(i = ipos; i < strlen(str1); i ++){ //LOOP em str1
		for(z = 0; z < strlen(str2); z ++){ //LOOP em str2 comparando cada caracter
			if(*(str1 + i + z) != *(str2 + z)) //se caracter for diferente passa para proximo caracter de str1
				break;
		}

		if(z == strlen(str2)) //se z == str2.length então loop rodou até o final (todos os caracteres foram comparados e retornaram true)
			return i; //retorna posição do primeiro caracter da sequencia de caracteres
	}
	
	return -1; //fim do loop sem encontrar str2 em str1
}
