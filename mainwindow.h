#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDir>
#include "client.h"
#include "materiele.h"
#include "conversion.h"
#include "achat.h"
#include "qsystemtrayicon.h"
#include "qmessagebox.h"
#include <qstring.h>
#include <stdio.h>
#include <stdlib.h>
#include "affaire.h"
#include "formulaire.h"
#include "recherchedate.h"
#include "commande.h"
#include "choisirclients.h"
#include "facture.h"
class QComboBox;
namespace Ui {
class MainWindow;

}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void clearForm();
    void AfficherCli();
    void AfficherMateriel();
    void RemplireTableauCommande();
    void initialiserCli();
    void initialiserMateriel();
    void rechercheCli();
    void RechercheMateriel();
    void Jours();
    void AfficherLitesdesAchatsParClients();
    void AfficherTousLesChiffresDAffaireDeChaqueClients();
    void initialiserClientsNouveau();
    void LesCodeAutomatique();
    void initialiserRadioBottonRecherche();
    void commande();
    void PlacerLenomDuClientsSelectionner(char *CodeClients);
    void cb();
    void Creefacture(com CM);
    void b();
private slots:
    void on_AjouterClient_clicked();
    void on_SupprimerClients_clicked();
    void on_EditerClient_clicked();
    void on_EnrengistrerClient_clicked();
    void on_txtCherchCli_textEdited();
    void on_ClientBoutton_clicked();
    void on_MaterielButton_clicked();
    void on_AchatsBouton_clicked();
    void on_SupprimerMateriel_clicked();
    void on_EditerMateriel_clicked();
    void on_AjouterMateriel_clicked();
    void on_Enregistrer_clicked();
    void on_SuprimerComande_clicked();
    void on_EditerCommande_clicked();
    void on_factureBouton_clicked();
    void on_NouveauMateriel_clicked();
    void on_AnnulerechercheMateriel_clicked();
    void on_AnnulerRechercheClients_clicked();
    void on_ChiffredAffaire_clicked();
    void on_TableauCommande_clicked(const QModelIndex &index);
    void on_ButtonNouveauClients_clicked();
    void on_ButtonAnnuler_clicked();
    void on_MaterieTab_clicked(const QModelIndex &index);
    void on_ButtonImprimer_clicked();
    void on_radioRechercheetntrdeuxdate_clicked();
    void on_radioRecherchedansunmoi_clicked();
    void on_radiorechercheDansuneanne_clicked();
    void on_pushButton_clicked();
    com *on_pushButtonForRechercheClients_clicked();
    void on_TableauClient_clicked();
    void on_pushButtonNouveauCommande_clicked();
    void on_pushButtonforAutre_clicked();
    void on_pushButton_3_clicked();
    void on_comboBoxforClients_currentIndexChanged(int index);
    void on_pushButtonEnrengistrerlesmodification_clicked();
    void on_pushButtonforsupprimerCommande_clicked();
    void on_tableWidgetforCommande_clicked(const QModelIndex &index);
    void on_comboBoxFroNomclients_currentIndexChanged(int index);
    void on_radiorechercheTous_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_RechercheMateriele_textEdited();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_TableauCommande_cellClicked(int row, int column);

    void on_TableauCommande_cellPressed(int row, int column);

private:
    Ui::MainWindow *ui;
    QComboBox *directoryComboBox;
    QComboBox *createComboBox(const QString &text = QString());
    QDir currentDir;
};
#endif // MAINWINDOW_H
