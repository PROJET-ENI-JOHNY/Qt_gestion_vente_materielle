#ifndef FACTURE_H
#define FACTURE_H

typedef struct facture
{
    char Facture[1000],commande[100],test[10000];
    int numero;
}FAC;
void AjouterfactureEffectuer(FAC v);
int IsCommandeaunefacture(char *commande);
int CodeAutomatique();
FAC*RecherchenumFacture(char*numcom);
#endif // FACTURE_H
