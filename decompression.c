#include"decompression.h"
#include<math.h>
#include<stdio.h>

void decompression(char* text , struct noeud* arbre , int cursComp){
	FILE* fichier=NULL;
	fichier=fopen(text,"r");
	FILE* decomp=NULL;
	decomp=fopen("filedecompressed","w");
	int i=0;
	int curs=7;
	int a=fgetc(fichier);
	printf("a vaut %c\n" , a);
	while(arbre[i].pere != -1){
		i++;
	}

	struct noeud noeudCourant=arbre[i] ;
	printf("le char du noeud est %c\n" , noeudCourant.c);

	if(fichier==NULL){printf("impossible d'ouvrir le fichier"); return ;}
	char d=noeudCourant.c;
	printf("d vaut %c",d);
	while(a!=EOF){
		noeudCourant=arbre[i];
		d=noeudCourant.c;
		printf("test");
		while(d =='0'){
			printf("coucou");
			if(curs<0){printf("change octet\n");a=fgetc(fichier) ; curs=7 ;}
			if((a & (char)pow(curs,2)) !=0 ){
				noeudCourant=arbre[noeudCourant.fd];
				d=noeudCourant.c ;}

			if((a & (char)pow(curs,2))==0){
				noeudCourant=arbre[noeudCourant.fg];
				d=noeudCourant.c;}
			curs--;

		}
		
		//	printf("jolie boucle\n");
		fwrite(&(noeudCourant.c),sizeof(char),1,decomp);
	}
	fclose(fichier);
	fclose(decomp);

}

