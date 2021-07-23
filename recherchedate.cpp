#include "recherchedate.h"
#include "mainwindow.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void remplireFichierPourMois(char *mois)
{
    FILE*fd;
    fd=fopen(FTMP,"w");
    fprintf(fd,"%s",mois);
    fclose(fd);
}
//Recuperation de moi dans le fichier TMP pour faire le comparer dans le fichiet FCOM
Achat* ChercherMoiDisponible()
{
   FILE*fd=fopen(FTMP,"r");
   Achat* commande;
   int i=0;
   commande=(Achat*)malloc(sizeof(Achat));
   while(!feof(fd)){
       fscanf(fd,"%d\-%d\-%d\n",&commande[i].jour,&commande[i].mois,&commande[i].annee);
       i++;
       commande=(Achat*)realloc(commande,(i+1)*sizeof(Achat));
   }
   fclose(fd);
   return commande;
}



Achat *DeterminerNbCommandePouRechercheeAlaidedeDate(int *nb)
{
    FILE *fd=fopen(FCOM,"r");
    int i=0;
    Achat*commande;
    commande=(Achat*)malloc(sizeof(Achat));
    while(!feof(fd)){
           fscanf(fd,"%s\t%s\t%s\t%d\t%d\-%d\-%d\n",commande[i].index,commande[i].numClient,commande[i].numMat,&commande[i].Qte,&commande[i].jour,&commande[i].mois,&commande[i].annee);
           i++;
           commande=(Achat*)realloc(commande,(i+1)*sizeof(Achat));

    }
    fclose(fd);
    if(i==0) commande=NULL;
    *nb=i;
    return commande;
}

/*  DEBUT  ALGORITHME DE RECHERCHE DE TOUS LES COMMANDE DE CLIENTS AVEC LE TOTALE DE VENTE*/
Achat* getTousLesCommandeClients(char *numClient,int *totale ,int *nb)
{
    FILE*fd=fopen(FCOM,"r");
    Achat commande,*resultat=(Achat*)malloc(sizeof(Achat));
    int i=0,TOTALE=0;
    while (!feof(fd)){
        if(fscanf(fd,"%s\t %s\t %d\t %s\n",commande.index,commande.numClient,&commande.Totale,commande.date)==4){
            if(strcmp(commande.numClient,numClient)==0){
                   resultat[i]=commande;
                   TOTALE=TOTALE+commande.Totale;
                   i++;
                   resultat=(Achat*)realloc(resultat,(i+1)*(sizeof(Achat)));
            }
        }
    }
    fclose(fd);
    if(i==0) resultat=NULL;
    *totale=TOTALE;
    *nb=i;
    return resultat;
}

/*  FIN ALGORITHME DE RECHERCHE DE TOUS LES VENTES*/



/*  DEBUT  ALGORITHME DE RECHERCHE PAR ANNEE*/

Achat*LireFichierCommandePourAvoirListeDesMaterielAcheterParUnClientsdansuneAnne(int Annee, char *numClient, int *nb)
{
    Achat*commande , *resultat;
    int n=0;
    commande=DeterminerNbCommandePouRechercheeAlaidedeDate(&n);
    if(commande == NULL && n==0){
            return NULL;
       }
    else{
            resultat=(Achat*)malloc(sizeof(Achat));
            int i=0,size=0;
            for(;i<n;i++){
                if(commande[i].annee==Annee && strcmp(commande[i].numClient,numClient)==0){
                    resultat[size]=commande[i];
                    size++;
                    resultat=(Achat*)realloc(resultat,(size+1)*sizeof(Achat));
                }
            }
            *nb=size;
    }   
   return resultat;
}
int getTousLesCommandeClientsDansUneAnnee(char *numClient,int annee)
{
    FILE*fd=fopen(FCOM,"r");
    Achat* commande;
    commande=(Achat*)malloc(sizeof(Achat));
    int PrixTotale,Totale=0,Qte=0,i=0;
    while (!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%s\t%d\t%d\-%d\-%d\n",commande[i].index,commande[i].numClient,commande[i].numMat,&commande[i].Qte,&commande[i].jour,&commande[i].mois,&commande[i].annee)==7){
            if( strcmp(commande[i].numClient,numClient)==0  && commande[i].annee==annee){
                   Qte=commande[i].Qte;
                   PrixTotale=Qte*(getPuRealMateriel(commande[i].numMat));
                   Totale=Totale+PrixTotale;
                   i++;
                   commande=(Achat*)realloc(commande,(i+1)*(sizeof(Achat)));
            }
        }
    }
    fclose(fd);
    return Totale;
}

/* FIN   ALGORITHME DE RECHERCHE PAR ANNEE */



/*  DEBUT  ALGORITHME DE RECHERCHE PAR MOIS */
Achat*LireFichierCommandePourAvoirListeDesMaterielAcheterParUnClientsdansunmoi(int annee, int mois, char *numClient, int *nb)
{
    Achat*commande , *resultat;
    int n=0;
    commande=DeterminerNbCommandePouRechercheeAlaidedeDate(&n);
    if(commande == NULL && n==0){
        return NULL;
    }
    else{
        resultat=(Achat*)malloc(sizeof(Achat));
        int i=0,size=0;
        for(;i<n;i++){
            if(strcmp(commande[i].numClient,numClient)==0 && commande[i].mois==mois && commande[i].annee==annee){
                resultat[size]=commande[i];
                size++;
                resultat=(Achat*)realloc(resultat,(size+1)*sizeof(Achat));
            }

        }
        *nb=size;
     }
     return resultat;
}

void getTousLesSommeTotaleCommandeClientsDansUnMois(char *numClient,int mois,int annee,int *Totale)
{
    FILE*fd=fopen(FCOM,"r");
    Achat* commande;
    commande=(Achat*)malloc(sizeof(Achat));
    int PrixTotale,Totales=0,Qte=0,i=0;
    while (!feof(fd)){
        if(fscanf(fd,"%s\t%s\t%s\t%d\t%d\-%d\-%d\n",commande[i].index,commande[i].numClient,commande[i].numMat,&commande[i].Qte,&commande[i].jour,&commande[i].mois,&commande[i].annee)==7){
            if( strcmp(commande[i].numClient,numClient)==0  && commande[i].mois==mois &&  commande[i].annee==annee){
                   Qte=commande[i].Qte;
                   PrixTotale=Qte*(getPuRealMateriel(commande[i].numMat));
                   Totales=Totales+PrixTotale;
                   i++;
                   commande=(Achat*)realloc(commande,(i+1)*(sizeof(Achat)));
            }           
        }
    }
    fclose(fd);
    *Totale=Totales;
}

