#include"decompression.h"           //il faut declarer le tableau et le renvoyer
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "codeChar.h"
#include<stdint.h>
#include<inttypes.h>

void Exception1(FILE* fichier, FILE* decomp){
	int a=fgetc(fichier);
	char caca=a;
	a=fgetc(fichier);
	uint32_t cursFin=0;
	for(int i=31 ; i>=0 ; i--){
		printf("a vaut %d\n",a);
		if((a & (char)pow(2,i%8))!=0){
			cursFin |= (uint32_t)pow(2,i);
	}
		if(i%8==0){
			a=fgetc(fichier);
	}
	}
	
	for(int i=0 ; i<(int)cursFin ; i++){
		printf("%d %d\n",i,(int)cursFin);
		fwrite(&caca,sizeof(char),1,decomp);
	}
	fclose(fichier);
	fclose(decomp);
}

uint32_t lireCursFin(FILE* fichier, int* a){
	uint32_t cursFin=0;
	for(int i=31 ; i>=0 ; i--){
		if((*a & (char)pow(2,i%8))!=0)
			cursFin |= (uint32_t)pow(2,i);
		if(i%8==0)
			*a=fgetc(fichier);
		printf("curs fin vaut %d\n",cursFin);
	}
	printf("cursfin vaut%" PRIu32 "\n",cursFin);
	return cursFin ;
}


int trouve(struct noeud* T){
	int i=1;
	while(T[i].pere!=-2){
		i++;
	}
	return i ;
}

void lireArbre(FILE* file , FILE* decomp, int* a, int* curs, char* nbChar,int* nbBitEcrit,struct noeud* T,int node){
	if(*nbChar==-1)
		return ;

	char caractere=0;

	if(*curs<0){
		*a=fgetc(file);
		*curs=7;
	}
	T[node].c='w';
	int recursG=1;
	T[node].fg=trouve(T);
	T[T[node].fg].pere=node;

	if((*a & (char)pow(2,*curs))!=0){
		*curs=*curs-1;
		*nbBitEcrit=*nbBitEcrit+1;
		for(int k=7 ; k>=0 ; k--){
			if(*curs<0){
				*a=fgetc(file);
				*curs=7;
			}
			if((*a & (char)pow(2,*curs))!=0){
				caractere |= (char)pow(2,k);}
			else{printf("0\n");}
			*curs=*curs-1;
			*nbBitEcrit=*nbBitEcrit+1;
		}
		T[T[node].fg].fg=-1;
		T[T[node].fg].fd=-1;
		T[T[node].fg].c=caractere;
		*nbChar=*nbChar-1;
		recursG=0;
		printf("char ecrit %c\n",caractere);
		caractere=0;
	}
	else{*curs=*curs-1; *nbBitEcrit=*nbBitEcrit+1;}

	if(*curs<0){
		*a=fgetc(file);
		*curs=7;
	}
	int recursD=1;
	T[node].fd=trouve(T);
	T[T[node].fd].pere=node;

	if((*a & (char)pow(2,*curs))!=0){
		*curs=*curs-1;
		*nbBitEcrit=*nbBitEcrit+1;
		for(int k=7 ; k>=0 ; k--){
			if(*curs<0){
				*a=fgetc(file);
				*curs=7;
			}
			if((*a & (char)pow(2,*curs))!=0){
				caractere |= (char)pow(2,k);}
			else{printf("0\n");}
			*curs=*curs-1;
			*nbBitEcrit=*nbBitEcrit+1;

		}
		T[T[node].fd].fg=-1;
		T[T[node].fd].fd=-1;
		T[T[node].fd].c=caractere;
		*nbChar=*nbChar-1;
		recursD=0;
		printf("char ecrit %c\n",caractere);
		caractere=0;
	}
	else{*curs=*curs-1; *nbBitEcrit=*nbBitEcrit+1;}

	if(recursG)
		lireArbre(file,decomp,a,curs,nbChar,nbBitEcrit,T,T[node].fg);
	if(recursD)
		lireArbre(file,decomp,a,curs,nbChar,nbBitEcrit,T,T[node].fd);


}

void decompression(char* text, char* cible ){
	FILE* fichier=NULL;
	fichier=fopen(text,"r");
	FILE* decomp=NULL;
	decomp=fopen(cible,"w");
	int a=fgetc(fichier);
	int* ptra=&a;
	uint32_t cursComp=lireCursFin(fichier,ptra);
	printf("cursComp vaut %d\n",(int)cursComp);
	int j=0;
	int curs=6;
	int* ptrcurs=&curs;
	char nbchar=a;
	
	if(nbchar==0){
		Exception1(fichier,decomp);
		
		return ;
	}

	printf("nbchar vaut %d\n",nbchar);
	char* ptrnbchar=&nbchar;
	a=fgetc(fichier);
	int nbBitEcrit=9;
	int* ptrnbBit=&nbBitEcrit;
	char q ;
	printf("nbCHar vaut %d\n" ,nbchar);
	struct noeud* arbre = malloc((int)(nbchar+1)*10*sizeof(struct noeud));
	for(int i=1 ; i<nbchar*10 ; i++)
		arbre[i].pere=-2;

	arbre[0].pere=-1;
	if(fichier==NULL){printf("impossible d'ouvrir le fichier"); return ;}
	if(decomp==NULL){printf("impossible d'ouvrir le fichier"); return ;}
	
	lireArbre(fichier,decomp,ptra,ptrcurs,ptrnbchar,ptrnbBit,arbre,0);
//	printf("bit ecrit vaut %d\n",nbBitEcrit);
	for(int i=0 ; i<10 ; i++){
		q=arbre[i].c;
		printf("%d. char %c ,pere %d, fg %d codechar %s\n",i,q,arbre[i].pere,arbre[i].fg,codeChar(q,arbre));
		free(codeChar(q,arbre));
	}
	while(arbre[j].pere != -1)
		j++;
	struct noeud noeudCourant=arbre[j];
	char d=noeudCourant.c;
	while(a!=EOF){
		noeudCourant=arbre[j];
		d=noeudCourant.c;
		while((noeudCourant.fd != -1) || (noeudCourant.fg != -1)){
			if(curs<0){
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
			if(nbBitEcrit==cursComp){
				noeudCourant.fd=-1 ;
				noeudCourant.fg=-1;	
				a=EOF;
			}

		}	
		fwrite(&d,sizeof(char),1,decomp);
	}
	fclose(fichier);
	fclose(decomp);
	free(arbre);
	return ;

}

