#ifndef FICHIER_H
#define FICHIER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FCLI "Client.dat"
#define FMAT "Materiel.dat"
#define FCOM "Commande.dat"
#define FAFF "Affaire.dat"
#define FTMP "Tmp.dat"
#define FTMP1 "Tmp1.dat"
#define FCOM1 "com.dat"
#define FFACT "Facture.dat"


void CreeFichier(char *fnam);
void initialiser();

#endif // FICHIER_H
