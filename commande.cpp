#include "commande.h"
#include "mainwindow.h"

void RemplireFichierCommande1(com CM)
{
    FILE*fd=fopen(FCOM1,"a");
    fprintf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,CM.PU,CM.QT,CM.TL,CM.CCL,CM.DATE);
    fclose(fd);
}

com*LirelesFichierFCM1(int *n,com CM1)
{
    com CM,*resultat;
    resultat=(com*)malloc(sizeof(com));
    int size=0;
    FILE*fd=fopen(FCOM1,"r");
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            if(strcasecmp(CM.NC,CM1.NC)==0){
                resultat[size]=CM;
                size++;
                resultat=(com*)realloc(resultat,(size+1)*sizeof(com));
            }
        }
    }
    fclose(fd);
    *n=size;
    return resultat;
}

int IsExistMateriel2pourVoirLecontenueDeStock1(com CM)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;

    int trouve=0,Stock;
    while(!feof(fd) && trouve==0 ){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,CM.NM)==0){
            trouve=1;
            Stock=Materiel.Stock;
        }
    }
    fclose(fd);
    return Stock;
}
int IsExistMateriel2pourVoirLecontenueDeStock2(char *nuMmat)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0,Stock;
    while(!feof(fd)){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,nuMmat)==0){
            trouve=1;
            Stock=Materiel.Stock;
        }
    }
    fclose(fd);
    return Stock;
}

void FonctionDeVariationdesStock1(int Nouveau,com CM)
{
    MAT Materiel;
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return;
    while(!feof(fd1)){
         fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
         if(strcmp(Materiel.numMat,CM.NM)==0){
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
void FonctionDeRetabTotalCO(int Nouveau,com CM)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM,"r");
    fd2=fopen(FTMP,"w");
    Achat commande;
    if(fd1==NULL) return;
    while(!feof(fd1)){
        if(fscanf(fd1,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,&commande.Totale,commande.date)==4){
         if(strcmp(commande.index,CM.NC)==0){
          fprintf(fd2,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,Nouveau,commande.date);
         }
         else{
          fprintf(fd2,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.Totale,commande.date);
         }
       }
    }
    fclose(fd1);fclose(fd2);
    remove(FCOM);
    rename(FTMP,FCOM);
}

int RecupererTotale(com CM)
{
    FILE*fd1;
    fd1=fopen(FCOM,"r");
    Achat commande;
    int trouve=0,Totale=0;
    while(!feof(fd1)){
        if(fscanf(fd1,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,&commande.Totale,commande.date)==4){
             if(strcmp(commande.index,CM.NC)==0){
                trouve=1;
                Totale=commande.Totale;
             }
       }
    }
    fclose(fd1);
    return Totale;
}

void SupprimerCommande(com CM1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM1,"r");
    fd2=fopen(FTMP,"w");
    com CM;
    if(fd1==NULL) return;
    while(!feof(fd1)){
        if(fscanf(fd1,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            if(strcmp(CM.NC,CM1.NC)!=0){
                 fprintf(fd2,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,CM.PU,CM.QT,CM.TL,CM.CCL,CM.DATE);
            }
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FCOM1);
    rename(FTMP,FCOM1);
}
void SupprimerCommande2(com CM1)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM1,"r");
    fd2=fopen(FTMP,"w");
    com CM;
    if(fd1==NULL) return;
    while(!feof(fd1)){
        if(fscanf(fd1,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            if((strcmp(CM.NC,CM1.NC)==0 && strcmp(CM.NM,CM1.NM)!=0) || (strcmp(CM.NC,CM1.NC)!=0) ){
                 fprintf(fd2,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,CM.PU,CM.QT,CM.TL,CM.CCL,CM.DATE);
            }
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FCOM1);
    rename(FTMP,FCOM1);
}

void DeleteCommande3(com CM)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM,"r");
    fd2=fopen(FTMP,"w");
    Achat commande;
    if(fd1==NULL) return;
    while(!feof(fd1)){
         if(fscanf(fd1,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,&commande.Totale,commande.date)==4){
             if(strcmp(commande.index,CM.NC)!=0) fprintf(fd2,"%s\t%s\t%d\t%s\n",commande.index,commande.numClient,commande.Totale,commande.date);
         }
    }
   fclose(fd1);fclose(fd2);
   remove(FCOM);
   rename(FTMP,FCOM);
}

void chiffredaffaire(com CM)
{
    Affaire Aff;
    FILE*fd1,*fd2;
    fd1=fopen(FAFF,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return ;
    while(!feof(fd1)){
        fscanf(fd1,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,&Aff.vola);
        if(strcmp(Aff.NUM,CM.CCL)==0){
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,CM.TL);
        }
        else{
            fprintf(fd2,"%s\t%s\t%d\n",Aff.NUM,Aff.NOM,Aff.vola);
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FAFF);
    rename(FTMP,FAFF);
}

void FonctionDeVariationdesStockcommande(int Nouveau,com CM)
{
    MAT Materiel;
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return;
    while(!feof(fd1)){
            if(fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock)==4){
                 if(strcasecmp(Materiel.numMat,CM.NM)==0){
                     fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Nouveau);
                 }
                 else{
                     fprintf(fd2,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,Materiel.PuReal,Materiel.Stock);
                 }
            }
    }
    fclose(fd1);fclose(fd2);
    remove(FMAT);
    rename(FTMP,FMAT);
}
void FonctionDeVariationdesStockcommande1(int Nouveau,char*numMat)
{
    MAT Materiel;
    FILE*fd1,*fd2;
    fd1=fopen(FMAT,"r");
    fd2=fopen(FTMP,"w");
    if(fd1==NULL) return;
    while(!feof(fd1)){
         fscanf(fd1,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
         if(strcmp(Materiel.numMat,numMat)==0){
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

int IsExistMateriel2pourVoirLecontenueDeStockcommande(com CM)
{
    FILE*fd=fopen(FMAT,"r");
    MAT Materiel;
    int trouve=0,Stock;
    while(!feof(fd) && trouve==0 ){
        fscanf(fd,"%s\t%s\t%d\t%d\n",Materiel.numMat,Materiel.Design,&Materiel.PuReal,&Materiel.Stock);
        if(strcmp(Materiel.numMat,CM.NM)==0){
            trouve=1;
            Stock=Materiel.Stock;
        }
    }
    fclose(fd);
    return Stock;
}

com*getTousLesCommandeClients1(char*numclients ,int *n,int *Totale)
{
    FILE*fd=fopen(FCOM1,"r");
    com CM,*resultat;
    int i=0,T=0;
    resultat=(com*)malloc(sizeof(com));
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            printf("%s",CM.CCL);
            if(strcmp(CM.CCL,numclients)==0){
                T=T+CM.TL;
                resultat[i]=CM;
                i++;
                resultat=(com*)realloc(resultat,(i+1)*sizeof(com));
            }
        }
    }
    fclose(fd);
    if(i==0) resultat=NULL;
    *n=i;
    *Totale=T;
    return resultat;
}
com*getTousLesCommandeClients2(char*numclients,int *n, int*Totale,int Annee)
{
    FILE*fd=fopen(FCOM1,"r");
    com CM,*resultat;
    int i=0,T=0;
    int jour,mois,annee;
    resultat=(com*)malloc(sizeof(com));
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            sscanf(CM.DATE,"%d-%d-%d",&jour,&mois,&annee);
            if(strcmp(CM.CCL,numclients)==0 && annee==Annee){
                T=T+CM.TL;
                resultat[i]=CM;
                i++;
                resultat=(com*)realloc(resultat,(i+1)*sizeof(com));
            }
        }
    }
    fclose(fd);
    if(i==0) resultat=NULL;
    *n=i;
    *Totale=T;
    return resultat;
}
com*getTousLesCommandeClients3(char*numclients,int *n,int *Totale,int Mois,int Annee)
{
    FILE*fd=fopen(FCOM1,"r");
    com CM,*resultat;
    int i=0,T=0;
    int jour,mois,annee;
    resultat=(com*)malloc(sizeof(com));
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            sscanf(CM.DATE,"%d-%d-%d",&jour,&mois,&annee);
            if(strcmp(CM.CCL,numclients)==0 && annee==Annee && mois==Mois){
                T=T+CM.TL;
                resultat[i]=CM;
                i++;
                resultat=(com*)realloc(resultat,(i+1)*sizeof(com));
            }
        }
    }
    fclose(fd);
    if(i==0) resultat=NULL;
    *n=i;
    *Totale=T;
    return resultat;
}

com*getTousLesCommandeClients4(com CM1,int *n)
{
    FILE*fd=fopen(FCOM1,"r");
    com CM,*resultat;
    int i=0;
    resultat=(com*)malloc(sizeof(com));
    while(!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
            if(strcmp(CM.NC,CM1.NC)==0){
                resultat[i]=CM;
                i++;
                resultat=(com*)realloc(resultat,(i+1)*sizeof(com));
            }
        }
    }
    fclose(fd);
    if(i==0) resultat=NULL;
    *n=i;
    return resultat;
}

void EditerCommande1(int b,com CM)
{
    FILE*fd1,*fd2;
    fd1=fopen(FCOM,"r");
    fd2=fopen(FTMP,"w");
    Achat commande;
    if(fd1==NULL) return;
    while(!feof(fd1)){
         if(fscanf(fd1,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,&commande.Totale,commande.date,&commande.numero)==5){
             if(strcmp(commande.index,CM.NC)==0){
                 fprintf(fd2,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,b,commande.date,commande.numero);
             }
             else{
              fprintf(fd2,"%s\t%s\t%d\t%s\t%d\n",commande.index,commande.numClient,commande.Totale,commande.date,commande.numero);
             }
        }
    }
    fclose(fd1);fclose(fd2);
    remove(FCOM);
    rename(FTMP,FCOM);
}
