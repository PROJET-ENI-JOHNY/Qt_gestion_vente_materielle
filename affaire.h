#ifndef AFFAIRE_H
#define AFFAIRE_H
#include "fichier.h"
#include "client.h"
#include "materiele.h"

typedef struct Affaire
{
    char NUM[10],NOM[100];
    int vola;
}Affaire;
void RemplireFichierCfiffreDaffaire();
Affaire*TousClientdAffaire(int *nb);
int NombredelignedeAffaire();
void TousClientdAffaire1(int *nb);

#endif // AFFAIRE_H
