#include"compression.h"
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include"codeChar.h"
#include"afficheBin.h"

int compression(char* text , struct noeud* arbre){

	int i=0;	
	char buffer = 0;
	FILE* file = NULL;
        file = fopen("filecompressed" , "w");	
	FILE* fichier = NULL ;
	int curs = 7 ; //curseur qui pointe ou doit etre ecrit l'octet
	fichier=fopen(text , "r+");
	if(fichier==NULL){ printf("fichier non ouvert\n"); return 1; }   //ajouter message d'erreur
	int cursFinEcriture=0 ;

	int a=fgetc(fichier);
	while(a != EOF){
		i=0;	
		printf("a vaut %c" , a);
		while(codeChar(a,arbre)[i] != '\0'){
			if(curs<0){
				fwrite(&buffer,sizeof(char),1,file);
				buffer=0;
				curs=7;
//				printf("octet ecrit\n");
			}
			if(codeChar(a,arbre)[i]=='1'){
//				printf("bit change\n");
				buffer |= (char)pow(2,curs);
			}
			curs-- ;
			cursFinEcriture++ ;
			printf("curs : %d\n" , curs);
			i++ ;
		}
		a=fgetc(fichier);
	}
//	affichebin((unsigned)buffer);
	printf("\n le dernier buffer vaut");
	affichebin(buffer);
	printf("\n");
	fwrite(&buffer,sizeof(char),1,file);
	fclose(fichier);
	fclose(file);
	return cursFinEcriture ;
}

