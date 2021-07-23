#ifndef MATERIELE_H
#define MATERIELE_H
#include "materiele.h"
#include "fichier.h"
#include "mainwindow.h"

    typedef struct Materiele
    {
        char numMat[20],Design[30];
        int PuReal,Stock;
    }MAT;
    int IsExistMateriel(MAT Materiel1);
    char *generatorNomMAteriel(MAT materiel1);
    void RemplireFichierMateriel(MAT Materiel);
    MAT *NbTotaleDesMateriel(int *nb);
    void NbTotaleDesMateriele(int *nbM);
    void SupprimerMateriel(MAT Materiel1);
    void EditerMateriel(MAT Materiel1);
    MAT *RechercheMateriele(char *txt, int *n, int *trouve);
    int RecuperationdesNombreTotaleDeVenteDunMateriel(MAT Materiel);
    MAT *Recupererdesignation(char *numMat);

#endif // MATERIELE_H
