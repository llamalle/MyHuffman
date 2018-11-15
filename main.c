#include"prob.h"
#include<stdio.h>
#include<stdlib.h>
#include"creerArbre.h"
#include"codeChar.h"
#include"tailleMoyenne.h"
#include"compression.h"
#include"decompression.h"

int main(int argc , char** argv){
	float* tabprob = proba(argv[1]) ;
	struct noeud* arbre = creerArbre(tabprob) ;

	printf("%d\n" , arbre[0].c);
	for(int i=0 ; i<25 ; i++){
		printf("%d. char = %c  pere = %i  filsdr = %i  filsga = %i  prob = %f \n" , i, arbre[i].c , arbre[i].pere , arbre[i].fd , arbre[i].fg , arbre[i].prob) ;
	}

	codeChar('e' , arbre) ;
	printf("%f",tailleMoyenne(arbre));
//	compression(argv[1] , arbre);
	decompression(argv[2] , arbre , 3);
	free(tabprob) ;

	

	return 0 ;
}
