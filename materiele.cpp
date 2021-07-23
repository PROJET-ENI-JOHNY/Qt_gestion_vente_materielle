#include "materiele.h"
#include "fichier.h"
#include "achat.h"

#include <qstring.h>
#include <stdio.h>
#include <stdlib.h>



int IsExistMateriel(MAT Materiel1)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0;
    while(!feof(fd) && trouve==0 )
    {
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,Materiel1.numMat)==0 || strcmp(Materiel.Design,Materiel1.Design)==0)
        {
            trouve=1;
        }

    }
    fclose(fd);
    return trouve;
}


int IsExistMateriel2pourVoirLecontenueDeStock(Achat commande)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;

    int trouve=0,Stock;
    while(!feof(fd) && trouve==0 )
    {
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,commande.numMat)==0)
        {

            trouve=1;
            Stock=Materiel.Stock;
        }

    }
    fclose(fd);
    return Stock;
}



//Pour le chiffre d'affaire

int IsExistMateriel2pourVoirLecontenueDePrixreel(Achat commande)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0,PuReal=0;
    while(!feof(fd) && trouve==0){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,commande.numMat)==0){
            trouve=1;
            PuReal=Materiel.PuReal;
        }
    }
    fclose(fd);
    return PuReal;
}


void RemplireFichierMateriel(MAT Materiel)
{
    FILE*fd=fopen(FMAT,"a");
    if(fd==NULL) return ;
    fprintf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Materiel.Stock);
    fclose(fd);
}

MAT *NbTotaleDesMateriel(int *nb)
{
    FILE*fd;
    fd=fopen(FMAT,"r");
    MAT*Materiel=(MAT*)malloc(sizeof(MAT));
    int i=0;
    while(!feof(fd))
    {
        if(fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel[i].numMat,Materiel[i].Design,&Materiel[i].PuReal,&Materiel[i].Stock)==4)
        {
            i++;
            Materiel=(MAT*)realloc(Materiel,(i+1)*sizeof(MAT));
        }
    }
    fclose(fd);
    if(i==0) Materiel=NULL;
    *nb=i;
  return Materiel;
}
//Faire le numero automatique du materiel
 void NbTotaleDesMateriele(int *nbM)
{
    FILE*fd;
    fd=fopen(FMAT,"r");
    int i=0;
    MAT*Materiel=(MAT*)malloc(sizeof(MAT));
    while(!feof(fd))
    {
        if(fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel[i].numMat,Materiel[i].Design,&Materiel[i].PuReal,&Materiel[i].Stock)==4)
        {
            i++;
            Materiel=(MAT*)realloc(Materiel,(i+1)*sizeof(MAT));
        }
    }
    fclose(fd);
    if(i==0) Materiel=NULL;
    *nbM=(i+1);

}
void SupprimerMateriel(MAT Materiel1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    MAT Materiel;
   while(!feof(fd1))
   {
       fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
       if(strcmp(Materiel.numMat,Materiel1.numMat)!=0) fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Materiel.Stock);
   }
   fclose(fd1);fclose(fd2);
   remove(FMAT);
   rename(FTMP,FMAT);
}


void EditerMateriel(MAT Materiel1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    MAT Materiel;
   while(!feof(fd1))
   {
       fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
       if(strcmp(Materiel.numMat,Materiel1.numMat)==0) Materiel=Materiel1;
           fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Materiel.Stock);
   }
   fclose(fd1);fclose(fd2);
   remove(FMAT);
   rename(FTMP,FMAT);
}


MAT *RechercheMateriele(char *txt, int *n, int *trouve)
{
    FILE* fd=fopen(FMAT,"r");
    int i=0,trouves=0;
    MAT Materiel;
    MAT* Materiel1=(MAT*)malloc(sizeof(MAT));
    while(!feof(fd) && trouves==0){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcasecmp(Materiel.numMat,txt)==0 || strcasecmp(Materiel.Design,txt)==0){
            Materiel1[i]=Materiel;
            i++;
            Materiel1=(MAT*)realloc(Materiel1,(i+1)*sizeof(MAT));
            trouves=1;
        }
    }
    fclose(fd);
    *n=i;
    *trouve=trouves;
    return Materiel1;
}

//pour avoir lr nombre totale de vente d'un materiel

int RecuperationdesNombreTotaleDeVenteDunMateriel(MAT Materiel)
{
    FILE*fd1;
    fd1=fopen(FCOM,"r");
    Achat commande;
    int Qte=0;
    while(!feof(fd1))
    {
         fscanf(fd1,"%s\t%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.numMat,&commande.Qte,commande.date);
         if(strcmp(Materiel.numMat,commande.numMat)==0)
         {
             Qte=Qte+commande.Qte;
         }
    }
   fclose(fd1);
  return Qte;

}

int getPuRealMateriel(char*numMat)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0,Pureal;
    while(!feof(fd) && trouve==0 ){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,numMat)==0){
            trouve=1;
            Pureal=Materiel.PuReal;
        }
    }
    fclose(fd);
    return Pureal;
}
MAT*Recupererdesignation(char*numMat)
{
    FILE* fd=fopen(FMAT,"r");
    int i=0,trouves=0;
    MAT Materiel;
    MAT* Materiel1=(MAT*)malloc(sizeof(MAT));
    while(!feof(fd) && trouves==0){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcasecmp(Materiel.numMat,numMat)==0){
            Materiel1[i]=Materiel;
            i++;
            Materiel1=(MAT*)realloc(Materiel1,(i+1)*sizeof(MAT));
            trouves=1;
        }
    }
    fclose(fd);
    return Materiel1;
}
