#include"creerArbre.h"
#include<stdlib.h>


struct noeud* creerArbre(float *tab){

	int i1 , i2 ;
	int cpt = 0 ; //nb de car different dans le fichier
	struct noeud min1 , min2 ;
	int j = 0 ; //compteur du tableau de structure

	for(int i=0 ; i<256 ; i++){
		if(tab[i] !=0) { cpt++ ;}
	}

	struct noeud* T = malloc(cpt*2*sizeof(struct noeud)) ;
	//tableau pour chaque char different

	for(int i=0 ; i<256 ; i++){
		if(tab[i]!=0){
			T[j].c = (char)i ;
			T[j].pere = -1 ;
			T[j].fg = -1 ;
			T[j].fd = -1 ;
			T[j].prob = tab[i] ;
			j++ ;
		}
	}            

	// initialise tout les noeuds 
	do{
		min1.prob = 1 ;
		min2.prob = 1 ;
		i1 = 0 ;
		i2 = 0 ;
		for(int k=0 ; k<j ; k++){
			if((T[k].prob<min1.prob) && (T[k].pere == -1)){
				min2 = min1 ;
				min1 = T[k] ;
				i2 = i1 ;      
				i1 = k ;       
			}
			else if((T[k].prob<min2.prob) && (T[k].pere == -1)){
				min2.prob = T[k].prob ;
				i2 = k ;
			}
		}
			//si le noeud a un pere on ne le compte plus
			// prend les noeuds de prob minimum 

			if(min1.prob != 1 && min2.prob !=1) { 
				T[j].c = '0';
				T[j].pere = -1 ;
				T[j].fd = i1 ;
				T[j].fg = i2 ;
				T[j].prob = min1.prob + min2.prob ;
				j++ ;

				T[i1].pere = j-1 ;
				T[i2].pere = j-1 ;
			}
			// ajoute un noeud pere pour les 2 noeud fils de proba minimum 

		}while((min1.prob!=1) && (min2.prob!=1)) ; //s'arrete s'il n'y a pas 2 noeuds sans pere

		return T ;
	}
