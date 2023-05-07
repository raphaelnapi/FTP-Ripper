#ifndef STRING_HANDLING_H
#define STRING_HANDLING_H

int splitcount(char* string, char separator);
char* _split(char* string, char separator, int pos);
char* removeFirstSplit(char* string, char separator);
int instr(int ipos, char* str1, char* str2);

#endif
