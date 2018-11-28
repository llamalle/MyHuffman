#include<stdio.h>
#include<stdlib.h>
#include"prob.h"

float* proba(char* txt){
	
	float* T = malloc(256*sizeof(float)) ;
	int a;
	FILE* fichier=NULL ;
	fichier = fopen( txt  , "r+") ;  //ouvre le fichier passé en arg
	int i=0 ;
	char e = 0 ;

	for(int i=0 ; i<256 ; i++)
		T[i] = 0 ;
	

	a = fgetc(fichier) ; // a lit le fichier char par char

	while(a != EOF){
		T[a] ++ ;
		a = fgetc(fichier) ;  
		i++ ;
	}                           //ajoute 1 a la case de tab d'indice a 

	for(int j=0 ; j<256 ; j++){
		T[j] = (float)T[j]/i ;  // proba de chaque char
		e = (char)j ;
		if(T[j] != 0)
			printf("%c  %f\n" , e , T[j]); 
	}
	
	fclose(fichier);
	return T ;

}
