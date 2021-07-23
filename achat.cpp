#include "achat.h"
#include "mainwindow.h"

void RemplireFichierCommande(Achat commande)
{
    FILE*fd=fopen(FCOM,"a");
    fprintf(fd,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,commande.Totale,commande.date,commande.numero);
    fclose(fd);
}

int RecuperationdesQuatiterDisponible(Achat commande1)
{
    FILE*fd=fopen(FCOM,"r");
    Achat commande;
    int trouve=0;
    int Qte;
    while(!feof(fd) && trouve==0)
    {
         fscanf(fd,"%s\t%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.numMat,&commande.Qte,commande.date);
         if((strcmp(commande.numClient,commande1.numClient)==0) && (strcmp(commande.numMat,commande1.numMat)==0) &&  (strcmp(commande.date,commande1.date)==0))
         {
             trouve=1;
             Qte=commande.Qte;
         }
    }
    fclose(fd);
  return Qte;
}

Achat*DeterminerNbCommande(int *nb)
{
    FILE *fd=fopen(FCOM,"r");
    int i=0;
    Achat*commande;
    commande=(Achat*)malloc(sizeof(Achat));
    while(!feof(fd)){
           if(fscanf(fd,"%s\t %s\t %d\t %s \t %d \n",commande[i].index,commande[i].numClient,&commande[i].Totale,commande[i].date,&commande[i].numero)==5){
               i++;
               commande=(Achat*)realloc(commande,(i+1)*sizeof(Achat));
           }
    }
    fclose(fd);
    if(i==0) commande=NULL;
    *nb=i;
    return commande;
}
int DeterminerNbCommande()
{
    FILE *fd=fopen(FCOM,"r");
    int i=0,n=0;
    Achat commande;
    while(!feof(fd)){
           if(fscanf(fd,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,&commande.Totale,commande.date,&commande.numero)==5){
               n=commande.numero;
               i++;
           }
    }
    fclose(fd);
    if(i==0) n=0;
    return (n+1);
}


//Suppression si le numClients est egales
void DeleteCommande(Achat commande1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM,"r");
    fd2=fopen(FTMP,"w");
    Achat commande;
    if(fd1==NULL) return;
    while(!feof(fd1)){
         if(fscanf(fd1,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,&commande.Totale,commande.date,&commande.numero)==5){
             if(strcmp(commande.index,commande1.index)!=0) fprintf(fd2,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,commande.Totale,commande.date,commande.numero);
         }
    }
   fclose(fd1);fclose(fd2);
   remove(FCOM);
   rename(FTMP,FCOM);
}

//Edition si le stock est egale
void EditerCommande(Achat commande1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM,"r");
    fd2=fopen(FTMP,"w");
    Achat commande;
    if(fd1==NULL) return;
    while(!feof(fd1)){
         fscanf(fd1,"%s\t%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.numMat,&commande.Qte,commande.date);
         if(strcmp(commande.index,commande1.index)==0 && strcmp(commande.numClient,commande1.numClient)==0)commande=commande1;
             fprintf(fd2,"%s\t%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.numMat,commande.Qte,commande.date);
    }
      fclose(fd1);fclose(fd2);
     remove(FCOM);
     rename(FTMP,FCOM);
}
int ValeurDuChiffredaffaireParClient(Achat commande)
{
    FILE*fd=fopen(FAFF,"r");
    int t=0,vola;
    Affaire Aff;
    while(!feof(fd) && t==0){
         fscanf(fd,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
         if(strcmp(Aff.NUM,commande.numClient)==0){
             t=1;
             vola=Aff.vola;
         }
    }
    fclose(fd);
  return  vola;
}



void FonctionDeVariationdesStock(int Nouveau,Achat commande)
{
    MAT Materiel;
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return;
    while(!feof(fd1)){
         fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
         if(strcmp(Materiel.numMat,commande.numMat)==0){
          fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Nouveau);
         }
         else{
           fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Materiel.Stock);
         }
    }
    fclose(fd1);fclose(fd2);
    remove(FMAT);
    rename(FTMP,FMAT);
}


/*=============================================================================================================*/
/*===============================================================================================================*/
                                      // LISTAGES DES ACHATS EFFECTUER  PAR CLIENTS//
/*===============================================================================================================*/
/*==============================================================================================================*/



Achat* TousLesAchatsEffectuersParUnClient(int *NbAchats)
{
    FILE*fd;
    fd=fopen(FTMP1,"r");
    if(fd==NULL)return NULL;
    Achat*commande=(Achat*)malloc(sizeof(Achat));
    int compt=0;
    while(!feof(fd))
    {
         if(fscanf(fd,"%s\t%s\t%d\t%s\n",commande[compt].index,commande[compt].numMat,&commande[compt].Qte,commande[compt].date)==5)
         {
             compt++;
             commande=(Achat*)realloc(commande,(compt+1)*sizeof(Achat));
         }

    }
     fclose(fd);
     if(compt==0) return NULL;
    *NbAchats=compt;  
    return commande;

}
Achat* RecherchedesListeDesAchatsEffectuersParClient(char *numClient, int *nb)
{
    int n;
    Achat *commande,*resultat;
    commande=DeterminerNbCommande(&n);
    if(commande == NULL && n==0){
        return NULL;
    }
    else{
        resultat=(Achat*)malloc(sizeof(Achat));
        int i=0,size=0;
        for(;i<n;i++){
            if(strcasecmp(commande[i].numClient,numClient)==0){
                resultat[size]=commande[i];
                size++;
                resultat=(Achat*)realloc(resultat,(size+1)*sizeof(Achat));
            }
        }
        *nb = size;
   }
   return resultat;
}
//Fonction pour afficher tous les chiffre d'affaire par clients




