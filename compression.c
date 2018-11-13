//#include"compression.h"
#include"creerArbre.h"
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include"codeChar.h"

void compression(char* text , struct noeud* arbre){

	int i=0;	
	char buffer = 0;
	FILE* file = NULL;
        file = fopen("filecompressed" , "w");	
	FILE* fichier = NULL ;
	int curs = 7 ; //curseur qui pointe ou doit etre ecrit l'octet
	fichier=fopen(text , "r+");
	if(fichier==NULL){ return; }   //ajouter message d'erreur

	int a=fgetc(fichier);
	
	while(a != EOF){
		while(codeChar[i] != '\0'){
			if(curs<0)
				fwrite(&buffer,sizeof(char),1,file);
			if(codeChar[i]=='1')
				buffer |= (char)pow(2,curs);
			curs-- ;
			i++ ;
		}
	}
}

