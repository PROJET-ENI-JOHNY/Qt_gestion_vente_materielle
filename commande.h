#ifndef COMMANDE_H
#define COMMANDE_H
#include "fichier.h"
#include <QDate>

typedef struct commande
{
    char NC[100],NM[100],NOM[100],CCL[100],DATE[100],FACT[100],a[4];
    int PU,QT,TL;
}com;
void RemplireFichierCommande1(com CM);
com*LirelesFichierFCM1(int *n , com CM1);
void FonctionDeVariationdesStockcommande(int Nouveau,com CM);
int IsExistMateriel2pourVoirLecontenueDeStockcommande(com CM);
void SupprimerCommande(com CM1);
void SupprimerCommande2(com CM1);
void FonctionDeRetabTotalCO(int Nouveau,com CM);
void DeleteCommande3(com CM);
com*getTousLesCommandeClients1(char *numclients , int *n, int *Totale);
com*getTousLesCommandeClients2(char*numclients,int *n, int*Totale,int Annee);
com*getTousLesCommandeClients3(char*numClients, int *n, int *Totale, int mois, int Annee);
void FonctionDeVariationdesStock1(int Nouveau,com CM);
int IsExistMateriel2pourVoirLecontenueDeStock1(com CM);
int IsExistMateriel2pourVoirLecontenueDeStock2(char *nuMmat);
void FonctionDeVariationdesStockcommande1(int Nouveau, char *numMat);
void EditerCommande1(int b,com CM);
com *getTousLesCommandeClients4(com CM1,int *n);
void chiffredaffaire(com CM);
int RecupererTotale(com CM);

#endif // COMMANDE_H
