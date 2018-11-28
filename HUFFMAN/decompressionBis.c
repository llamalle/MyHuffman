#include"decompression.h"           //il faut declarer le tableau et le renvoyer
#include<math.h>
#include<stdio.h>
#include"afficheBin.h"
#include<stdlib.h>

struct noeud* lireArbre(FILE* file , FILE* decomp, int* a, int* curs, char nbChar,int* nbBitEcrit){
	struct noeud* T = malloc((int)nbChar*10*sizeof(struct noeud));
	int i=0;
	T[i].pere=-1;
	int B=0;
	char caractere=0;
	while(B<(int)nbChar){  	
		printf("nbBitEcir vaut %d \n" , *nbBitEcrit);		//tant que le nombre de caractere triuve n'est pas egale au nombre de char total
		if(*curs<0){
			*a=fgetc(file);
			*curs=7;
		}

		if((*a & (char)pow(2,*curs))==0){
			T[i].fg=2*i+1;
			T[2*i+1].pere=i;	
			T[i].fd=2*i+2;
			T[2*i+2].pere=i;						//on declare que la case i+1 sera le fg et la case 
			T[i].c=0;
			*curs=*curs-1;							//si le bit lu est 0 on declare un noeud
			*nbBitEcrit=*nbBitEcrit+1;
		}
		if((*a & (char)pow(2,*curs))!=0){
			T[i].fd=-1;
			T[i].fg=-1;
			*curs=*curs-1;
			*nbBitEcrit=*nbBitEcrit+1;

			for(int k=7; k>=0; k--){
				if(*curs<0){
					*a=fgetc(file);
					*curs=7;
			}
				if((*a & (char)pow(2,*curs))==1)
					caractere |= (char)pow(2,k);
				*curs=*curs-1;
				*nbBitEcrit=*nbBitEcrit+1;
			}
			T[i].c=caractere;
			B++;
			printf("char ecrit %d\n",caractere);
		}								//si le bit est 1 on declare une feuille et on ecrit le caractere
		i++;
	}
	printf("nbBitEcrit vaut %d \n ", *nbBitEcrit);
	return T;
}




void decompression(char* text , int cursComp){
	FILE* fichier=NULL;
	fichier=fopen(text,"r");
	FILE* decomp=NULL;
	decomp=fopen("filedecompressed","w");
	int i=0;
	int curs=7;
	int* ptrcurs=&curs;
	int a=fgetc(fichier);
	int* ptra=&a;
	int nbBitEcrit=1;
	int* ptrnbBit=&nbBitEcrit;
//	printf("a vaut %c\n" , a);
	
	if(fichier==NULL){printf("impossible d'ouvrir le fichier"); return ;}
	
	struct noeud* arbre=lireArbre(fichier,decomp,ptra,ptrcurs,a,ptrnbBit);
	while(arbre[i].pere != -1)
		i++;
	struct noeud noeudCourant=arbre[i];
	char d=noeudCourant.c;
	while(a!=EOF){
		noeudCourant=arbre[i];
		d=noeudCourant.c;
		//	printf("test");
		while((noeudCourant.fd != -1) || (noeudCourant.fg != -1)){
//			printf("a vaut");
//			affichebin(a);
//			printf("\npowcurs 2 vaut");
//			affichebin((char)pow(2,curs));
//			printf("\n");
//			printf("coucou");
//			printf("est ce quon va a gauche : %d \n" ,(a&(char)pow(2,curs))==1);
			//affichebin(a&(char)pow(2,curs));
//			printf("\n");
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
			if(nbBitEcrit==cursComp){
				noeudCourant.fd=-1 ;
			        noeudCourant.fg=-1;	
				a=EOF;
			}

		}	
//		printf("cursComp vaut %d\n nbBitEcrit vaut %d\n",cursComp,nbBitEcrit);
		fwrite(&d,sizeof(char),1,decomp);
	}
	fclose(fichier);
	fclose(decomp);
	free(arbre);
	return ;

}

