#ifndef _CARBRE
#define _CARBRE

struct noeud{
	char c ;
	int pere ;
	int fg ;
	int fd ;
	float prob ;
} ; 

struct noeud* creerArbre(float *tab) ;

#endif
