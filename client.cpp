#include "client.h"
#include "fichier.h"
#include "achat.h"
#include "mainwindow.h"


int ExistClient(CLI ncli1)
{
    FILE*fd1;
    CLI ncli;
    fd1=fopen(FCLI,"r");
    int t=0;
    while(!feof(fd1) && t==0)
    {
        fscanf(fd1,"%s\t%s\n",ncli.numCli,ncli.nomCli);
        if(strcmp(ncli.numCli,ncli1.numCli)==0) t=1;
    }
    fclose(fd1);
    return t;
}

// Pour savoir si le client existe deja sur le fichier commande
int ExisteClientsDansCommande(Achat commande1)
{
    FILE*fd1;
    CLI ncli;
    int vola=0;
    fd1=fopen(FAFF,"r");
    int t=0;
    while(!feof(fd1) && t==0)
    {
        fscanf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,&vola);
        if(strcmp(ncli.numCli,commande1.numClient)==0)
        {
            t=1;
        }
    }
    fclose(fd1);
    return t;
}

int ExisteClientsDansCommande1(Achat commande1)
{
    FILE*fd1;
    CLI ncli;
    int vola=0;
    fd1=fopen(FAFF,"r");
    int t=0;
    while(!feof(fd1) && t==0)
    {
        fscanf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,&vola);
        if(strcmp(ncli.numCli,commande1.numClient)==0)
        {
            t=1;
        }
    }
    fclose(fd1);
    return vola;
}


int ExistClientCommande(Achat commande)
{
    FILE*fd1;
    CLI ncli;
    fd1=fopen(FCLI,"r");
    int t=0;
    while(!feof(fd1) && t==0)
    {
        fscanf(fd1,"%s\t%s\n",ncli.numCli,ncli.nomCli);
        if(strcmp(ncli.numCli,commande.numClient)==0) t=1;
    }
    fclose(fd1);
    return t;
}


void MiseAJoursDuClientsAffaire(CLI ncli)
{
    FILE*fd1,*fd2;
    Affaire Aff;
    fd1=fopen(FAFF,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==0) return;
    while(!feof(fd1))
    {
        fscanf(fd1,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
        if(strcmp(Aff.NUM,ncli.numCli)==0)
        {
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,ncli.nomCli,Aff.vola);
        }
        else
        {
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,Aff.vola);
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FAFF);
    rename(FTMP,FAFF);
}
int ExistClientCommande1(Achat commande)
{
    FILE*fd1;
    Affaire*Aff;
    fd1=fopen(FAFF,"r");
    int t=0,i=0;
    while(!feof(fd1) && t==0)
    {

        fscanf(fd1,"%s\t%s\t%d\n",Aff[i].NUM,Aff[i].NOM,&Aff[i].vola);
        if(strcmp(Aff[i].NUM,commande.numClient)==0) t=1;
    }
    fclose(fd1);
    return t;
}
int IsExistMaterielCommande(Achat commande)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0;
    while(!feof(fd) && trouve==0 )
    {
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,commande.numMat)==0)
        {
            trouve=1;
        }

    }
    fclose(fd);
    return trouve;
}


void AjoutClient(CLI ncli)
{
    FILE*fd=fopen(FCLI,"a");
    fprintf(fd,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,ncli.indexe);
    fclose(fd);
}

void EditClient(CLI ncli1)
{
    FILE*fd1,*fd2;
    CLI ncli;
    fd1=fopen(FCLI,"r");
    fd2=fopen(FTMP,"w");

    while(!feof(fd1))
    {
        fscanf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,&ncli.indexe);
        if(strcmp(ncli.numCli,ncli1.numCli)==0) ncli=ncli1;
        fprintf(fd2,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,ncli.indexe);
    }
    fclose(fd1);fclose(fd2);
    remove(FCLI);
    rename(FTMP,FCLI);
}


void DeleteClient(CLI ncli1)
{
    FILE*fd1,*fd2;
    CLI ncli;
    fd1=fopen(FCLI,"r");
    fd2=fopen(FTMP,"w");
    while(!feof(fd1))
    {
        fscanf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,&ncli.indexe);
        if(strcmp(ncli.numCli,ncli1.numCli)!=0) fprintf(fd2,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,ncli.indexe);
    }
    fclose(fd1);fclose(fd2);
    remove(FCLI);
    rename(FTMP,FCLI);
}
CLI* TousClient(int *nb)
{
    FILE*fd1;
    fd1=fopen(FCLI,"r");
    int i=0;
    CLI *cli=(CLI*)malloc(sizeof(CLI));
    while(!feof(fd1)){
       if(fscanf(fd1,"%s\t%s\t%d\n",cli[i].numCli,cli[i].nomCli,&cli[i].indexe)==3){
           i++;
           cli=(CLI*)realloc(cli,(i+1)*sizeof(CLI));
       }
    }
    fclose(fd1);
    if(i==0)cli=NULL;
    *nb=i;
    return cli;

}
//Pour faire une numero automatique du clients
int TousClient1()
{
    FILE*fd1;
    fd1=fopen(FCLI,"r");
    CLI ncli;
    int n=0,i=0;
    while(!feof(fd1)){
       if(fscanf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,&ncli.indexe)==3){
           n=ncli.indexe;
           i++;
       }

    }
    if(i==0) n==1;
    fclose(fd1);
   return (n+1);
}

CLI*RechercheClient(char *txt,int *n,int *trouve)
{
    FILE*fd=fopen(FCLI,"r");
    int a=0, trouves=0;
    CLI cli;
    CLI*ncli=(CLI*)malloc(sizeof(CLI));
    while(!feof(fd)){
        fscanf(fd,"%s\t%s\t%d\n",cli.numCli,cli.nomCli,&cli.indexe);
        if(strcasecmp(cli.numCli,txt)==0 || strcasecmp(cli.nomCli,txt)==0){
           ncli[a]=cli;
           a++;
           ncli= (CLI*)realloc(ncli,(a+1)*sizeof(CLI));
           trouves=1;
        }
    }
    fclose(fd);
    *trouve=trouves;
    *n=a;
    return ncli;
}

int ExisteClientsDansCommande1(CLI ncli)
{
    FILE*fd1;
    Affaire Aff;
    fd1=fopen(FAFF,"r");
    int t=0;
    while(!feof(fd1) && t==0){
       fscanf(fd1,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
       if(strcmp(Aff.NUM,ncli.numCli)==0){
           t=1;
        }
        else{
           t=0;
        }
    }
    if(t==0){
         AjouterLesNouveauClientsDansLesAffaire(ncli);
    }
    fclose(fd1);
    return t;
}


//A propos dE chifrre daffaire
void AjouterLesNouveauClientsDansLesAffaire(CLI ncli)
{
    FILE*fd1;
    fd1=fopen(FAFF,"a");
    int vol=0;
    fprintf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,vol);

    fclose(fd1);
}
void SupprimerClientsDansLesAffaireSiOnSupprimeUnClients(CLI ncli)
{
    FILE*fd1,*fd2;
    Affaire Aff;
    fd1=fopen(FAFF,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return;
    while(!feof(fd1))
    {
        fscanf(fd1,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
        if(strcmp(Aff.NUM,ncli.numCli)!=0)
        {
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,Aff.vola);
        }

    }
    fclose(fd1);fclose(fd2);
    remove(FAFF);
    rename(FTMP,FAFF);

}















