#include"compression.h"
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include"codeChar.h"
#include<stdlib.h>
#include"afficheBin.h"
#include<stdint.h>
#include<inttypes.h>

void CopieDeb(uint32_t A , char* cible){
	int c;
	char buf=0;
	FILE* tmp=tmpfile();
	FILE* file=fopen(cible , "r+");
	while((c=fgetc(file))!=EOF)
		fputc(c,tmp);	

	rewind(tmp);
	rewind(file);
	for(int i=31; i>=0 ; i--){
		if((A & (uint32_t)pow(2,i))!=0)
			buf |= (uint32_t)pow(2,i%8) ;
	        if(i%8==0){
			fwrite(&buf,sizeof(char),1,file);
	       		buf=0;
			printf("u32 ecirt\n");
		}		
	}

	while((c=fgetc(tmp))!=EOF)
		fputc(c,file);

	fclose(tmp);
	fclose(file);
	return ;
}

void ecrireArbre(struct noeud N , struct noeud* arbre , FILE* fichierC , char* buffer , int* curs, uint32_t* cursFinEcriture){
	if(N.fg==-1 && N.fd==-1){
		return ;
	}
	if(arbre[N.fg].c != 0){
		*buffer |= (char)pow(2,*curs);
		if(*curs<0){
			printf("coucou\n");
			fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;
		//bit a 1 pour prevenir quil y aura un charatere apres

		for(int p=7 ; p>=0 ; p--){
			if(*curs<0){
				fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
				*curs=7;
				*buffer=0;
			}
			if((arbre[N.fg].c & (char)pow(2,p))!=0){
				*buffer |= (char)pow(2,*curs);}
			*curs = *curs-1;
			*cursFinEcriture=*cursFinEcriture+1;	
		}
		printf("le char ecrit est %c \n",arbre[N.fg].c);
		//** ecriture du caractere de l'arbre 
	}
	else{ 

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;	

	}	

	if(arbre[N.fd].c != 0){	

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
			*curs=7;
			*buffer=0;
		}
		*buffer |= (char)pow(2,*curs);
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;
		//bit a 1 pour indiquer quil y aura un char apres 

		for(int p=7 ; p>=0 ; p--){
			if(*curs<0){
				fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
				*curs=7;
				*buffer=0;	
			}
			if((arbre[N.fd].c & (char)pow(2,p))!=0)
				*buffer |= (char)pow(2,*curs);
			*curs = *curs-1;	
			*cursFinEcriture=*cursFinEcriture+1;	

		}
		printf("le char ecrit est %c \n",arbre[N.fd].c);
		//** ecriture du caractere de l'arbre 
	}
	else {

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			affichebin(*buffer);
			printf("\n");
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;	

	}

	ecrireArbre(arbre[N.fg],arbre,fichierC,buffer,curs,cursFinEcriture);
	ecrireArbre(arbre[N.fd],arbre,fichierC,buffer,curs,cursFinEcriture);
}


void compression(char* text , char* cible , struct noeud* arbre){

	int i=0;
	char buffer = 0;
	char* ptrbuffer = &buffer;
	FILE* file = NULL;
	file = fopen(cible , "w+");	
	FILE* fichier = NULL ;
	fichier=fopen(text , "r+");
	int curs = 6 ; //curseur qui pointe ou doit etre ecrit l'octet
	int* ptrcurs = &curs ;
	if(fichier==NULL){ printf("fichier non ouvert\n"); return ; }   //ajouter message d'erreur
	uint32_t cursFinEcriture=1 ;
	uint32_t* ptrcursFinEcriture=&cursFinEcriture;
	char nbChar=0;

	while(arbre[i].pere != -1){
		if(arbre[i].c != 0)
			nbChar++;
		i++ ;
	}

	fwrite(&nbChar,sizeof(char),1,file);
	cursFinEcriture+=8;
	struct noeud noeudCourant=arbre[i] ;

	printf("curs fin %d\n",cursFinEcriture);
	ecrireArbre(noeudCourant , arbre , file , ptrbuffer , ptrcurs, ptrcursFinEcriture);
	printf("cursfinecr vaaut %d \n ", cursFinEcriture);
	int a=fgetc(fichier);
	while(a != EOF){
		i=0;	
		while(codeChar(a,arbre)[i] != '\0'){
			if(curs<0){
				fwrite(&buffer,sizeof(char),1,file);
				buffer=0;
				curs=7;
			}
			if(codeChar(a,arbre)[i]=='1'){
				buffer |= (char)pow(2,curs);
			}
			curs-- ;
			cursFinEcriture++ ;
			i++ ;
		}
		free(codeChar(a,arbre));
		a=fgetc(fichier);
	}
	fwrite(&buffer,sizeof(char),1,file);
	fclose(fichier);
	fclose(file);
	CopieDeb(cursFinEcriture,cible);
	return  ;
}


