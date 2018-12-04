#include"prob.h"
#include<stdio.h>
#include<stdlib.h>
#include"creerArbre.h"
#include"codeChar.h"
#include"tailleMoyenne.h"
#include"compression.h"
#include"decompression.h"
//#include<stdint.h>

int main(int argc , char** argv){
	float* tabprob = proba(argv[1]) ;
	struct noeud* arbre = creerArbre(tabprob) ;
	
	

	compression(argv[1] , argv[2] ,arbre);

	return 0 ;
}
