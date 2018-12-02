#include"codeChar.h"
#include<stdlib.h>
#include<stdio.h>

char * codeChar(char caractere, struct noeud * arbre) {
	int i = 0,j = 1;
	while (arbre[i].c != caractere) {
		i++;
	}
	for (int a = i; arbre[a].pere != -1; a = arbre[a].pere) {
		j++;
	}
	char* code = malloc((j)*sizeof(char));
	code[--j] = '\0';

	for (int a = i; arbre[a].pere != -1; a = arbre[a].pere) {
		if (a == arbre[arbre[a].pere].fd)
			code[--j] = '1';
		else
			code[--j] = '0';
	}
	return code;

}
