#ifndef ACHAT_H
#define ACHAT_H


#include "fichier.h"
#include "client.h"
#include "materiele.h"

        typedef struct AchatMateriele
        {
            char index[20],numClient[10],numMat[20],date[20],GetMoi[50];
            int Qte,jour,mois,annee,Totale,numero;
        }Achat;
        int DeterminerNbCommande();
        void RemplireFichierCommande(Achat commande);
        void remplireFichierPourMois(char *mois);
        int RecuperationdesQuatiterDisponible(Achat commande1);
        int ValeurDuChiffredaffaireParClient(Achat commande);
        Achat*DeterminerNbCommande(int *nb);
        void DeleteCommande(Achat commande1);
        void EditerCommande(Achat commande1);
        void FonctionDeVariationdesStock(int Nouveau,Achat commande);
        int IsExistMateriel2pourVoirLecontenueDeStock(Achat commande);
        int ExistClientCommande(Achat commande);
        int ExistClientCommande1(Achat commande);
        int IsExistMaterielCommande(Achat commande);
        Achat* TousLesAchatsEffectuersParUnClient(int *NbAchats);
        void ExistClientDansLeCommandePourFaireLeRetablisementDuPrixTotal(Achat commande,int VolaVaovao);
        int ExisteClientsDansCommande(Achat commande1);
        int ExisteClientsDansCommande1(Achat commande1);
        int IsExistMateriel2pourVoirLecontenueDePrixreel(Achat commande);
        Achat* ChercherMoiDisponible();
        Achat *RecherchedesListeDesAchatsEffectuersParClient(char *numClient, int *nb);
        Achat *DeterminerNbCommandePouRechercheeAlaidedeDate(int *nb);
        Achat*LireFichierCommandePourAvoirListeDesMaterielAcheterParUnClientsdansuneAnne(int Annee, char *numClient, int *nb);
        int getTousLesCommandeClientsDansUneAnnee(char *numClient,int annee);
        Achat*LireFichierCommandePourAvoirListeDesMaterielAcheterParUnClientsdansunmoi(int annee, int mois, char *numClient, int *nb);
        void getTousLesSommeTotaleCommandeClientsDansUnMois(char *numClient,int mois,int annee,int *Totale);
        Achat* getTousLesCommandeClients(char *numClient, int *totale, int *nb);
        int getPuRealMateriel(char*numMat);

#endif // ACHAT_H
