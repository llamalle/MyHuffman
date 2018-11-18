#include"tailleMoyenne.h" 
#include"creerArbre.h"
#include<stdio.h>
#include<string.h>
#include"codeChar.h"

float tailleMoyenne (struct noeud * arbre) {
  int i = 0;
  while (arbre[i].pere != -1) {
    i++;
  }
  int somme = 0;
  int div = 0;
  for (int j = 0; j < i; j++) {
    if (arbre[j].c != 0) {
      printf("%c : %s -- %ld\n",arbre[j].c ,codeChar(arbre[j].c,arbre),strlen(codeChar(arbre[j].c,arbre)));
      somme += strlen(codeChar(arbre[j].c,arbre));
      div++;
    }
  }
  return ((float)somme/(float)div);
}
