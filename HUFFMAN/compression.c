#include"compression.h"
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include"codeChar.h"
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>

void CopieDeb(uint32_t A , char* cible);

void exception1(struct noeud* arbre, FILE* fichier , FILE* file, char* cible){
	int i=0;
	int a;
	char buf=0;
	uint32_t nbRep=0;

	i=0;
	while(arbre[i].c == 0)
		i++;

	char buffer=arbre[i].c;
	fwrite(&buffer,sizeof(char),1,file);

	while((a=fgetc(fichier))!=EOF)
		nbRep++;

	for(int i=31; i>=0 ; i--){
		if((nbRep & (uint32_t)pow(2,i))!=0)
			buf |= (uint32_t)pow(2,i%8) ;
		if(i%8==0){
			printf("buffer vaut %d\n",buf);
			fwrite(&buf,sizeof(char),1,file);
			printf("u32 ecirt %d\n",buf);
			buf=0;
		}		
	}
	printf("%d\n",nbRep);

	fclose(fichier);
	fclose(file);
	CopieDeb(0,cible);	
	printf("la taille du fichier originel vaut %d\n",nbRep);
	printf("la taille du fichier compresse vaut 9");
	printf("le gain est de %f pourcent\n" ,((1-(9/(float)nbRep))*100.));
	return ;
}

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
			printf("buffer vaut %d\n",buf);
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

void ecrireArbre(struct noeud N , struct noeud* arbre , FILE* fichierC , char* buffer , int* curs, uint32_t* cursFinEcriture,int* TailleC){
	if(N.fg==-1 && N.fd==-1){
		return ;
	}
	if(arbre[N.fg].c != 0){
		*buffer |= (char)pow(2,*curs);
		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			*TailleC=*TailleC+1;
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
				*TailleC=*TailleC+1;
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
			*TailleC=*TailleC+1;
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
			*TailleC=*TailleC+1;
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
				*TailleC=*TailleC+1;
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
			*TailleC=*TailleC+1;
			printf("\n");
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;	

	}

	ecrireArbre(arbre[N.fg],arbre,fichierC,buffer,curs,cursFinEcriture,TailleC);
	ecrireArbre(arbre[N.fd],arbre,fichierC,buffer,curs,cursFinEcriture,TailleC);
}


void compression(char* text , char* cible , struct noeud* arbre){

	int i=0;
	
	char buffer = 0;
	char* ptrbuffer = &buffer;
	
	FILE* file = NULL;
	file = fopen(cible , "w+");	
	if(!file){
		fprintf(stderr,"impossible d'ouvrir le fichier cible\n");
		return ;}
	/*ouverture du futur fichier compressé */

	FILE* fichier = NULL ;
	fichier=fopen(text , "r+");
	if(!fichier){
		fprintf(stderr,"impossible d'ouvir le fichier source");
		return ;}
	/*ouverture du fichier a compressé */

	int curs = 6 ; 
	int* ptrcurs = &curs ;
	uint32_t cursFinEcriture=1 ;
	uint32_t* ptrcursFinEcriture=&cursFinEcriture;
	unsigned char nbChar=0;
	int TailleO=0; //taille du fichier originelle
	int TailleC=5; //taille du fichier compressé
	int* ptrTailleC=&TailleC;

	while(arbre[i].pere !=-1){
		if(arbre[i].c != 0){
			printf("char %c\n",arbre[i].c);
			nbChar++;}
		i++ ;
	}
	

	printf("nbcara vaut %d\n",nbChar);

	if(nbChar==0){
		printf("nbchar vaut %d",nbChar);
		fwrite(&nbChar,sizeof(char),1,file);
		exception1(arbre,fichier,file,cible);
		return;
	}
	nbChar--;
	fwrite(&nbChar,sizeof(char),1,file);

	cursFinEcriture+=8;
	struct noeud noeudCourant=arbre[i] ;

	printf("curs fin %d\n",cursFinEcriture);
	ecrireArbre(noeudCourant , arbre , file , ptrbuffer , ptrcurs, ptrcursFinEcriture,ptrTailleC);
	printf("cursfinecr vaaut %d \n ", cursFinEcriture);
	int a=fgetc(fichier);
	while(a != EOF){
		i=0;	
		while(codeChar(a,arbre)[i] != '\0'){
			if(curs<0){
				fwrite(&buffer,sizeof(char),1,file);
				TailleC++;
				buffer=0;
				curs=7;
			}
			if(codeChar(a,arbre)[i]=='1'){
				buffer |= (char)pow(2,curs);
			}
			curs-- ;
			cursFinEcriture++ ;
			i++ ;
			printf("yoyoyo\n");
		}
		free(codeChar(a,arbre));
		a=fgetc(fichier);
		TailleO++;
	}
	fwrite(&buffer,sizeof(char),1,file);
	TailleC++;
	fclose(fichier);
	fclose(file);
	CopieDeb(cursFinEcriture,cible);
	printf("la taille du fichier originel vaut %d\n",TailleO);
	printf("la taille du fichier compresse vaut %d\n",TailleC);
	printf("le gain est de %f pourcent \n" ,((1-TailleC/(float)TailleO))*100);
	return  ;
}


