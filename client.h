#ifndef CLIENT_H
#define CLIENT_H
#include "client.h"
#include "fichier.h"
#include "achat.h"

typedef struct CLIENT
{
    char numCli[10],nomCli[30],test[100];
    int indexe;
}CLI;
//Is exist client
int ExistClient(CLI ncli1);


void AjoutClient(CLI ncli);

//Pour les affaire
void AjouterLesNouveauClientsDansLesAffaire(CLI ncli);

//Pour savoir que le clients existe ou pas dans le affaire si elle exist on n'ajoute mais si elle nes pas la on ajoute

int ExisteClientsDansCommande1(CLI ncli);

//Retablisement du Clients dans les chiffre d'affaire si on supprime un cliezn
void SupprimerClientsDansLesAffaireSiOnSupprimeUnClients(CLI ncli);

//Editer client
void EditClient(CLI ncli1);

//Modification du clients dans tableau Affaire
void MiseAJoursDuClientsAffaire(CLI ncli);

//Supprimer CLIENT
void DeleteClient(CLI ncli1);

//Nombre totale des Materieles
CLI* TousClient(int *nb);

//Pour faire une numCli automatique
int TousClient1();

//Recherche CLIENT
CLI*RechercheClient(char *txt, int *n, int *trouve);

CLI*getClients();


#endif // CLIENT_H
