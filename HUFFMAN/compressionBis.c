#include"compression.h"
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include"codeChar.h"
#include"afficheBin.h"

void ecrireArbre(struct noeud N , struct noeud* arbre , FILE* fichierC , char* buffer , int* curs, int* cursFinEcriture){
//	printf("cursfinecr vaut %d \n" , *cursFinEcriture );
	if(N.fg==-1 && N.fd==-1){
	//	printf("fin de branche \n");
		return ;
	}
	if(arbre[N.fg].c != 0){
		*buffer |= (char)pow(2,*curs);
		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;
		for(int p=7 ; p>=0 ; p--){
			if(*curs<0){
				fwrite(buffer,sizeof(char),1,fichierC);
				*curs=7;
				*buffer=0;
			}
			if((arbre[N.fg].c&(char)pow(2,p))==1)
				*buffer |= (char)pow(2,*curs);
			*curs = *curs-1;
			*cursFinEcriture=*cursFinEcriture+1;	
		}
		//** ecriture du caractere de l'arbre 
	}
	else{ 

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;	
		
	}	

	if(arbre[N.fd].c != 0){	

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			*curs=7;
			*buffer=0;
		}
		*buffer |= (char)pow(2,*curs);
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;

		for(int p=7 ; p>=0 ; p--){
			if(*curs<0){
				fwrite(buffer,sizeof(char),1,fichierC);
				*curs=7;
				*buffer=0;	
			}
			if((arbre[N.fd].c&(char)pow(2,p))==1)
				*buffer |= (char)pow(2,*curs);
			*curs = *curs-1;	
			*cursFinEcriture=*cursFinEcriture+1;	
				

		}
//		printf("cursfinecr vaut %d \n",*cursFinEcriture);
//		printf("caractere compresse\n");
		//** ecriture du caractere de l'arbre 
	}
	else {

		if(*curs<0){
			fwrite(buffer,sizeof(char),1,fichierC);
			*curs=7;
			*buffer=0;
		}
		*curs = *curs-1;
		*cursFinEcriture=*cursFinEcriture+1;	
			
	}

	ecrireArbre(arbre[N.fg],arbre,fichierC,buffer,curs,cursFinEcriture);
	ecrireArbre(arbre[N.fd],arbre,fichierC,buffer,curs,cursFinEcriture);
//	printf("yahooo\n" );
}


int compression(char* text , struct noeud* arbre){

	int i=0;
	char buffer = 0;
	char* ptrbuffer = &buffer;
	FILE* file = NULL;
	file = fopen("filecompressed" , "w");	
	FILE* fichier = NULL ;
	int curs = 7 ; //curseur qui pointe ou doit etre ecrit l'octet
	int* ptrcurs = &curs ;
	fichier=fopen(text , "r+");
	if(fichier==NULL){ printf("fichier non ouvert\n"); return 1; }   //ajouter message d'erreur
	int cursFinEcriture=1 ;
	int* ptrcursFinEcriture=&cursFinEcriture;
	char nbChar=0;

	while(arbre[i].pere != -1){
		if(arbre[i].c != 0)
			nbChar++;
		i++ ;
	}

	fwrite(&nbChar,sizeof(char),1,file);
	cursFinEcriture+=8;
	struct noeud noeudCourant=arbre[i] ;

	ecrireArbre(noeudCourant , arbre , file , ptrbuffer , ptrcurs, ptrcursFinEcriture);
	printf("cursfinecr vaaut %d \n ", cursFinEcriture);
	int a=fgetc(fichier);
	while(a != EOF){
		i=0;	
	//	printf("a vaut %c" , a);
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
		//	printf("curs : %d\n" , curs);
			i++ ;
		}
		a=fgetc(fichier);
	}
	//	affichebin((unsigned)buffer);
//	printf("\n le dernier buffer vaut");
//	affichebin(buffer);
//	printf("\n");
	fwrite(&buffer,sizeof(char),1,file);
	fclose(fichier);
	fclose(file);
	return cursFinEcriture ;
}


