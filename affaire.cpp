#include "affaire.h"
#include "mainwindow.h"

int NombredelignedeAffaire()
{
    int i=0;
    FILE*fd;
    fd=fopen(FAFF,"r");
    Affaire Aff;
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola)==3){
           i++;
        }
     }
    fclose(fd);
   return i;
}

void RemplireFichierCfiffreDaffaire()
{
    FILE*fd1,*fd2;
    fd1=fopen(FAFF,"a");
    fd2=fopen(FCLI,"r");
    int nb=0,vola=0;
    CLI ncli;
    nb=NombredelignedeAffaire();
    if(nb==0){
    while(!feof(fd2)){
         if(fscanf(fd2,"%s\t%s\n",ncli.numCli,ncli.nomCli)==2){
            fprintf(fd1,"%s\t%s\t%d\n",ncli.numCli,ncli.nomCli,vola);
         }
     }
    }
    fclose(fd1);fclose(fd2);
}


void TousClientdAffaire1(int *nb)
{
    FILE*fd1=fopen(FAFF,"r");
    Affaire*Aff=(Affaire*)malloc(sizeof(Affaire));
    int i=0;
    while(!feof(fd1))
    {
        fscanf(fd1,"%s\t%s\t%d\n",Aff[i].NUM,Aff[i].NOM,&Aff[i].vola);
        i++;
        Aff=(Affaire*)realloc(Aff,(i+1)*sizeof(Affaire));
    }

    *nb=i;
    fclose(fd1);
}
void ExistClientDansLeCommandePourFaireLeRetablisementDuPrixTotal(Achat commande,int VolaVaovao)
{
    Affaire Aff;
    FILE*fd1,*fd2;
    fd1=fopen(FAFF,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return ;
    while(!feof(fd1)){
        fscanf(fd1,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
        if(strcmp(Aff.NUM,commande.numClient)==0){
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,VolaVaovao);
        }
        else{
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,Aff.vola);
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FAFF);
    rename(FTMP,FAFF);
}

Affaire*TousClientdAffaire(int *nb)
{
    FILE*fd1=fopen(FAFF,"r");
    Affaire*Aff=(Affaire*)malloc(sizeof(Affaire));
    int i=0;
    while(!feof(fd1)){
        if(fscanf(fd1,"%s\t%s\t%d\n",Aff[i].NUM,Aff[i].NOM,&Aff[i].vola)==3){
            i++;
            Aff=(Affaire*)realloc(Aff,(i+1)*sizeof(Affaire));
        }
    }
    fclose(fd1);
    if(i==0) Aff=NULL;
    *nb=i;
    return Aff;
}
