#include"decompression.h"
#include<math.h>
#include<stdio.h>
#include"afficheBin.h"

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
	int nbBitEcrit=0;

	struct noeud noeudCourant=arbre[i] ;
	printf("le char du noeud est %c\n" , noeudCourant.c);

	if(fichier==NULL){printf("impossible d'ouvrir le fichier"); return ;}
	char d=noeudCourant.c;
	printf("d vaut %c\n",d);
	while(a!=EOF){
		noeudCourant=arbre[i];
		d=noeudCourant.c;
	//	printf("test");
		while(d =='0'){
			printf("a vaut");
			affichebin(a);
			printf("\npowcurs 2 vaut");
			affichebin((char)pow(2,curs));
			printf("\n");
			printf("coucou");
			printf("est ce quon va a gauche : %d \n" ,(a&(char)pow(2,curs))==1);
			affichebin(a&(char)pow(2,curs));
			printf("\n");
			if(curs<0){
			//	affichebi();
	//			printf("change octet\n");
				a=fgetc(fichier) ; 
				curs=7 ;}
			if((a & (char)pow(2,curs)) !=0 ){
				noeudCourant=arbre[noeudCourant.fd];
				d=noeudCourant.c ;}

			if((a & (char)pow(2,curs))==0){
				noeudCourant=arbre[noeudCourant.fg];
				d=noeudCourant.c;}
			curs--;
			nbBitEcrit++;
	//		printf("nb bitecrit vaut %d\n curs vaut %d\n" , nbBitEcrit , cursComp);
			if(nbBitEcrit==cursComp){ d = 1; a=EOF ;}

		}
		
	//		printf("jolie boucle\n");
		fwrite(&d,sizeof(char),1,decomp);
	}
	fclose(fichier);
	fclose(decomp);

}

