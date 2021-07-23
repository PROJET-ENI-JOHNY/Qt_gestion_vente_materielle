#include "facture.h"
#include "mainwindow.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void AjouterfactureEffectuer(FAC v)
{
    FILE*fd=fopen(FFACT,"a");
    fprintf(fd,"%d\t%s\t%s\n",v.numero,v.Facture,v.commande);
    fclose(fd);
}
int IsCommandeaunefacture(char*commande)
{
    FAC*v=(FAC*)malloc(sizeof(FAC));
    int i=0,trouve=0;
    FILE*fd=fopen(FFACT,"r");
    while(!feof(fd)){
        if(fscanf(fd,"%d\t%s\t%s\n",&v[i].numero,v[i].Facture,v[i].commande)==3){
            if(strcasecmp(v[i].commande,commande)==0){
                trouve=1;
            }
        }
        i++;
        v=(FAC*)realloc(v,(i+1)*sizeof(FAC));
    }
    fclose(fd);
    if(i==0) trouve=0;
    return trouve;
}

int CodeAutomatique()
{
    FAC*v=(FAC*)malloc(sizeof(FAC));
    int numFAC=0;
    int i=0;
    FILE*fd=fopen(FFACT,"r");
    while(!feof(fd)){
      if(fscanf(fd,"%d\t%s\t%s\n",&v[i].numero,v[i].Facture,v[i].commande)==3){
            numFAC=v[i].numero;
            i++;
            v=(FAC*)realloc(v,(i+1)*sizeof(FAC));
    }
    }
    if(i==0) numFAC=0;
    fclose(fd);
    return (numFAC+1);
}


FAC*RecherchenumFacture(char*numcom)
{
    FAC v1;
    FAC*v=(FAC*)malloc(sizeof(FAC));
    int i=0;
    FILE*fd=fopen(FFACT,"r");
    while(!feof(fd)){
      if(fscanf(fd,"%d\t%s\t%s\n",&v1.numero,v1.Facture,v1.commande)==3){
          if(strcasecmp(v1.commande,numcom)==0){
             v[i]=v1;
             i++;
             v=(FAC*)realloc(v,(i+1)*sizeof(FAC));
         }
      }
    }
    if(i==0) v=NULL;
    fclose(fd);
    return v;
}
