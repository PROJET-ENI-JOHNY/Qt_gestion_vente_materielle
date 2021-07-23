#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTableWidgetItem"
#include <QtDebug>
#include <QPrinter>
#include <QPrintDialog>
#include "QPainter"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     QGridLayout *mainLayout = new QGridLayout;
 mainLayout->addWidget(directoryComboBox, 2, 1);
    directoryComboBox = createComboBox(QDir::currentPath());

    ui->setupUi(this);
    ui->GestionCLient->setCurrentIndex(0);
    initialiser();
    initialiserCli();
    initialiserMateriel();
    AfficherCli();
    AfficherMateriel();
    RemplireTableauCommande();
    AfficherTousLesChiffresDAffaireDeChaqueClients();
    initialiserClientsNouveau();
    initialiserRadioBottonRecherche();
    LesCodeAutomatique();
    ui->AnnulerRechercheClients->setVisible(false);
    ui->pushButtonforsupprimerCommande->setEnabled(false);
    ui->labelTotaleTemporaire->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_27->setVisible(false);
    ui->textBrowser->setReadOnly(true);
    ui->AnnulerechercheMateriel->setVisible(false);
    commande();
    cb();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initialiserCli()
{
    ui->EnrengistrerClient->setVisible(false);
    ui->NumeroEdit->setReadOnly(true);
    ui->AjouterClient->setVisible(true);
    //A propos de clients
    ui->EditerClient->setEnabled(false);
    ui->SupprimerClients->setEnabled(false);
    //A propos de Materiel
    ui->EditerMateriel->setEnabled(false);
    ui->SupprimerMateriel->setEnabled(false);
    //A propos de Achat
    ui->EditerCommande->setEnabled(false);
    ui->SuprimerComande->setEnabled(false);
    qDebug()<<QDate::currentDate();
     qDebug()<<QTime::currentTime();
    RemplireFichierCfiffreDaffaire();
    clearForm();
}
void MainWindow::LesCodeAutomatique()
{
    int nbM=0;
    NbTotaleDesMateriele(&nbM);
    char nba[100];
    sprintf(nba,"ART00%d",nbM);
    ui->CodeMateriel->setText(nba);

    //code Automatique pour le commande
    int nbCM=DeterminerNbCommande();
    char nbC[100];
    sprintf(nbC,"CM00%d",nbCM);
    ui->label_25->setText(nbC);

    int nbCLI=TousClient1();
    char CLI[20];
    sprintf(CLI,"CLI0%d",nbCLI);
    ui->NumeroEdit->setText(CLI);

    int n=CodeAutomatique();
    char numeroFac[100];
    sprintf(numeroFac,"FAC0%d",n);
    ui->label_10->setText(numeroFac);
    ui->label_31->setText(numeroFac);
}

void MainWindow::initialiserRadioBottonRecherche()
{
    ui->dateEditForAnnee->setVisible(false);
    ui->dateEditPourCommencer->setVisible(false);
    ui->labelZNtreDeuxDate->setVisible(false);
    ui->dateEditOurLimiteDeRecherche->setVisible(false);
    ui->dateEditPourLeMois->setVisible(false);
}

void MainWindow::initialiserMateriel()
{
    ui->SupprimerMateriel->setEnabled(false);
    ui->EditerMateriel->setEnabled(false);

}

void MainWindow::initialiserClientsNouveau()
{
    ui->widgetForNouveauClients->setVisible(false);
    ui->GROUPEBOXNOUVEAUMateriel->setVisible(false);
    ui->groupeBoxForinformation->setVisible(false);
}

void MainWindow::clearForm()
{
    ui->NomEdit->clear();
    ui->DesignationMateriel->clear();
    ui->PrixReelMateriel->clear();
    ui->StockCommande->clear();
}
/*=============================================================================================================*/
/*===============================================================================================================*/
                                      // A PROPOS DU CLIENT//
/*===============================================================================================================*/
/*==============================================================================================================*/


void MainWindow::AfficherCli()
{

    int n;
    CLI*ncli=TousClient(&n);
    int i=0;
    ui->TableauClient->setRowCount(0);
    for(i=0;i<n;i++){
            ui->TableauClient->insertRow(i);
            ui->TableauClient->setItem(i,0,new QTableWidgetItem(ncli[i].numCli));
            ui->TableauClient->setItem(i,1,new QTableWidgetItem(QString::fromLatin1(ncli[i].nomCli).replace(":"," ")));
            ui->TableauClient->item(i,0)->setTextAlignment(Qt::AlignCenter);
    }
    initialiserCli();
}
void MainWindow::cb()
{
    int n;
    CLI*ncli=TousClient(&n);
    int i=0;
    ui->comboBoxforClients->clear();
    ui->comboBoxFroNomclients->clear();
     for(i=0;i<n;i++){
         if(i==0){
         ui->comboBoxforClients->addItem("");
         ui->comboBoxFroNomclients->addItem("");
         }
         ui->comboBoxforClients->addItem(ncli[i].numCli);
         ui->comboBoxFroNomclients->addItem(QString::fromLatin1(ncli[i].nomCli).replace(":"," "));
     }
}

//listage des materiel acheter par un clients dans plusieurs methode

void MainWindow::AfficherLitesdesAchatsParClients()
{
    int n;
    Achat*commande=TousLesAchatsEffectuersParUnClient(&n);
    int i=0;
    if(commande == NULL){
        return;
    }
    else{
        ui->TABLEAULISTEDESMATERIELPARCLIENT->setRowCount(0);
        for(i=0;i<n;i++){
            ui->TABLEAULISTEDESMATERIELPARCLIENT->insertRow(i);
            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,0,new QTableWidgetItem(commande[i].numMat));
            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,1,new QTableWidgetItem(QString::number(commande[i].Qte)));
            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,2,new QTableWidgetItem(commande[i].date));
        }
    }
}


void MainWindow::on_AjouterClient_clicked()
{
    CLI ncli;
    QString numero=ui->NumeroEdit->text();
    QString nom=ui->NomEdit->text().replace(" ",":");
    if(numero.isEmpty() || nom.isEmpty()){
        QMessageBox::warning(this,"Champs vide","Veillez remplire le formulaire");
        return;
    }
    strcpy(ncli.numCli,numero.toLatin1());
    strcpy(ncli.nomCli,nom.toLatin1());
    int n=TousClient1();
    ncli.indexe=n;
    if(!ExistClient(ncli)){
        AjoutClient(ncli);
        ExisteClientsDansCommande1(ncli);
        AfficherCli();
        AfficherTousLesChiffresDAffaireDeChaqueClients();
        QMessageBox::information(this,"Information","Clients ajouter avec succès");
        LesCodeAutomatique();
        cb();
        ui->widgetForNouveauClients->setVisible(false);
    }
    else{
        QMessageBox::warning(this,"Erreur","Clients exist deja");
    }
}


void MainWindow::on_SupprimerClients_clicked()
{
    int SelectedRow=ui->TableauClient->currentRow();
    if(SelectedRow<0){
        QMessageBox::warning(this,"Erreur","Aucun ligne Selectioner");
        return;
    }
    else{
         int r=QMessageBox::question(this,"Confirmer suppression","Voulez-vous supprimer  ce clients"
                                ,QMessageBox::Yes|QMessageBox::No);
         if(r==QMessageBox::Yes){
               CLI c;
               strcpy(c.numCli,ui->TableauClient->item(SelectedRow,0)->text().toLatin1());
               strcpy(c.nomCli,ui->TableauClient->item(SelectedRow,1)->text().toLatin1());
               DeleteClient(c);
               SupprimerClientsDansLesAffaireSiOnSupprimeUnClients(c);
               AfficherTousLesChiffresDAffaireDeChaqueClients();
               AfficherCli();
               QMessageBox::information(this,"Information","Client supprimer avec succès");
          }
    }
}


void MainWindow::on_EditerClient_clicked()
{
    int SelectedRow=ui->TableauClient->currentRow();
    if(SelectedRow<0){
        QMessageBox::warning(this,"Erreur","Aucun ligne Selectioner");
        return;
    }
    ui->NumeroEdit->setText(ui->TableauClient->item(SelectedRow,0)->text());
    ui->NomEdit->setText(ui->TableauClient->item(SelectedRow,1)->text());
    ui->NumeroEdit->setReadOnly(true);
    ui->AjouterClient->setVisible(false);
    ui->EnrengistrerClient->setVisible(true);
    ui->widgetForNouveauClients->setVisible(true);
}


void MainWindow::on_EnrengistrerClient_clicked()
{
    CLI ncli;
    QString numero=ui->NumeroEdit->text();
    QString nom=ui->NomEdit->text().replace(" ",":");
    if(nom.isEmpty()){
        QMessageBox::warning(this,"Champs vide","Veillez remplire le formulaire");
        return;
    }
    else{
        strcpy(ncli.numCli,numero.toLatin1());
        strcpy(ncli.nomCli,nom.toLatin1());
        int n,trouve,i=0;
        CLI*Cherche=RechercheClient(ncli.numCli,&n,&trouve);
        ncli.indexe=Cherche[i].indexe;
        EditClient(ncli);
        ui->widgetForNouveauClients->setVisible(false);
        //Modification en Chiffre d'Affaire
        MiseAJoursDuClientsAffaire(ncli);
        AfficherTousLesChiffresDAffaireDeChaqueClients();
        AfficherCli();
        initialiserCli();
        clearForm();
        QMessageBox::information(this,"Information","Modification du clients avec succes");
        ui->widgetForNouveauClients->setVisible(false);
    }
}


//Recherche Par tableau,
void MainWindow::rechercheCli()
{
    /*
  QSystemTrayIcon*syico=new QSystemTrayIcon(this);
  syico->show();
  syico->showMessage("mety",tr("nnnnnnnn"));
*/
  QString txte=ui->txtCherchCli->text().toUpper();
  if(txte.isEmpty()){
      QMessageBox::warning(this,"Champ vide","Entrer le nom ou code clients dans le champ de recherche");
      ui->txtCherchCli->focusPolicy();
  }
  if(!txte.isEmpty()){
          char txt[30];
          strcpy(txt,txte.toLatin1().replace(" ",":"));
          int n,trouve=0;
          CLI*ncli=RechercheClient(txt,&n,&trouve);
          int i=0;
          if(trouve==0){
              QMessageBox::critical(this,"","Clients non trouver");
              AfficherCli();
          }
          else{
              if(n==0){
                  return;
              }
              ui->TableauClient->setRowCount(0);
              for(i=0;i<n;i++){
                  ui->TableauClient->insertRow(i);
                  ui->TableauClient->setItem(i,0,new QTableWidgetItem(ncli[i].numCli));
                  ui->TableauClient->setItem(i,1,new QTableWidgetItem(QString::fromLatin1(ncli[i].nomCli).replace(":"," ")));
                  ui->TableauClient->item(i,0)->setTextAlignment(Qt::AlignCenter);
              }
          }
      }
  else {
      AfficherCli();
  }
  /*
    QString cherche=ui->txtCherchCli->text();
    if(cherche==NULL){
        AfficherCli();
        QMessageBox::critical(this,"","Entrer le clients à chercher");
    }
    else{
        char txt[30];
        strcpy(txt,cherche.toLatin1().replace(" ",":"));
        int n,trouve=0;
        CLI*ncli=RechercheClient(txt,&n,&trouve);
        int i=0;
        if(trouve==0){
            QMessageBox::critical(this,"","Clients non trouver");
            AfficherCli();
        }
        else{
            if(n==0){
                return;
            }
            ui->TableauClient->setRowCount(0);
            for(i=0;i<n;i++){
                ui->TableauClient->insertRow(i);
                ui->TableauClient->setItem(i,0,new QTableWidgetItem(ncli[i].numCli));
                ui->TableauClient->setItem(i,1,new QTableWidgetItem(QString::fromLatin1(ncli[i].nomCli).replace(":"," ")));
            }
        }
    }
    */
}
void MainWindow::on_radioRechercheetntrdeuxdate_clicked()
{
    ui->label_27->setVisible(true);
    ui->dateEditPourCommencer->setVisible(true);
    ui->labelZNtreDeuxDate->setVisible(true);
    ui->dateEditOurLimiteDeRecherche->setVisible(true);
    ui->dateEditForAnnee->setVisible(false);
    ui->dateEditPourLeMois->setVisible(false);
    ui->radioRechercheetntrdeuxdate->setVisible(true);
}

void MainWindow::on_radioRecherchedansunmoi_clicked()
{
    ui->label_27->setVisible(false);
    ui->dateEditPourLeMois->setVisible(true);
    ui->dateEditPourCommencer->setVisible(false);
    ui->labelZNtreDeuxDate->setVisible(false);
    ui->dateEditOurLimiteDeRecherche->setVisible(false);
    ui->dateEditForAnnee->setVisible(false);
    ui->dateEditPourLeMois->setDate(QDate::currentDate());
}

void MainWindow::on_radiorechercheDansuneanne_clicked()
{
    ui->label_27->setVisible(false);
    ui->dateEditForAnnee->setVisible(true);
    ui->dateEditForAnnee->setValue(2017);
    ui->dateEditPourLeMois->setVisible(false);
    ui->dateEditPourCommencer->setVisible(false);
    ui->labelZNtreDeuxDate->setVisible(false);
    ui->dateEditOurLimiteDeRecherche->setVisible(false);
}


void MainWindow::on_pushButton_clicked()
{
    rechercheCli();
}

com* MainWindow::on_pushButtonForRechercheClients_clicked()
{
    ui->TABLEAULISTEDESMATERIELPARCLIENT->setRowCount(0);
    ui->EditerClient->setEnabled(true);
    ui->SupprimerClients->setEnabled(true);
    ui->widgetForNouveauClients->setVisible(false);
    int SelectedRow=ui->TableauClient->currentRow();
    if(SelectedRow<0){
        QMessageBox::critical(this,"","Selectionner au moins une ligne dans le tableau");
    }
    else{
        CLI ncli;
        strcpy(ncli.numCli,(ui->TableauClient->item(SelectedRow,0)->text().toLatin1()));
        strcpy(ncli.nomCli,(ui->TableauClient->item(SelectedRow,1)->text().toLatin1()));
        int n=0,i=0,Totale=0;
        Achat*commande;
        com*CM;

        if(ui->radioRechercheetntrdeuxdate->isChecked()){
            QDate date;
            QDate datedep= ui->dateEditPourCommencer->date();
            QDate datefin=ui->dateEditOurLimiteDeRecherche->date();
            FILE*fd=fopen(FCOM1,"r");
            com CM;
            int i=0,j=0;
            int jour,mois,annee;
            while(!feof(fd)){
                if(fscanf(fd,"%s\t%s\t%d\t%d\t%d\t%s\t%s\n",CM.NC,CM.NM,&CM.PU,&CM.QT,&CM.TL,CM.CCL,CM.DATE)==7){
                    sscanf(CM.DATE,"%d-%d-%d",&jour,&mois,&annee);
                    date.setDate(annee,mois,jour);
                    ui->TABLEAULISTEDESMATERIELPARCLIENT->setRowCount(0);
                    if(strcmp(CM.CCL,ncli.numCli)==0 && (date>=datedep && date<=datefin)){
                        i=ui->TABLEAULISTEDESMATERIELPARCLIENT->rowCount();
                        ui->TABLEAULISTEDESMATERIELPARCLIENT->insertRow(i);
                        ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,0,new QTableWidgetItem(CM.NM));
                        ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,1,new QTableWidgetItem(QString::number(CM.QT)));
                        ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,2,new QTableWidgetItem(QString::number(CM.TL)));
                        ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,3,new QTableWidgetItem(CM.DATE));
                        Totale+=CM.TL;
                        j=j+1;
                    }
                    i++;
                }
            }
            fclose(fd);
            if(j==0){
                QSystemTrayIcon*syico=new QSystemTrayIcon(this);
                syico->show();
                syico->showMessage("Information",tr("Acune vente disponible"));
                QMessageBox::information(this,"Information","Acune vente disponible");
            }
        }
        else if(ui->radioRecherchedansunmoi->isChecked() || ui->radiorechercheDansuneanne->isChecked() || ui->radiorechercheTous->isChecked()){
            if(ui->radiorechercheTous->isChecked()){
                printf("ncli.numCli=%s",ncli.numCli);
                CM=getTousLesCommandeClients1(ncli.numCli,&n,&Totale);
            }
            else if(ui->radiorechercheDansuneanne->isChecked()){
                int Annee=ui->dateEditForAnnee->text().toInt();
                CM=getTousLesCommandeClients2(ncli.numCli,&n,&Totale,Annee);
            }
            else if(ui->radioRecherchedansunmoi->isChecked()){
                char*Dates;
                ui->dateEditPourLeMois->setDate(QDate::currentDate());
                QString Date=ui->dateEditPourLeMois->text().toLatin1();
                QByteArray byteArray=Date.toUtf8();
                Dates=byteArray.data();
                remplireFichierPourMois(Dates);
                commande=ChercherMoiDisponible();
                CM=getTousLesCommandeClients3(ncli.numCli,&n,&Totale,commande[i].mois,commande[i].annee);
            }
            if(n==0){
                    QSystemTrayIcon*syico=new QSystemTrayIcon(this);
                    syico->show();
                    syico->showMessage("Information",tr("Acune vente disponible "));
                    QMessageBox::information(this,"Information","Acune vente disponible ");
                }
                else{
                    ui->TABLEAULISTEDESMATERIELPARCLIENT->setRowCount(0);
                    for(i=0;i<=n;i++){
                         ui->TABLEAULISTEDESMATERIELPARCLIENT->insertRow(i);
                         ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,0,new QTableWidgetItem(CM[i].NM));
                         ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,1,new QTableWidgetItem(QString::number(CM[i].QT)));
                         ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,2,new QTableWidgetItem(QString::number(CM[i].TL)));
                         ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,3,new QTableWidgetItem(CM[i].DATE));
                        if(i==n){
                            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,0,new QTableWidgetItem(""));
                            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,1,new QTableWidgetItem("Totale"));
                            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,2,new QTableWidgetItem(QString::number(Totale)));
                            ui->TABLEAULISTEDESMATERIELPARCLIENT->setItem(i,3,new QTableWidgetItem(""));
                         }
                    }
            }
          }
       }
    }

void MainWindow::on_AnnulerRechercheClients_clicked()
{
    AfficherCli();
    ui->txtCherchCli->clear();
}


void MainWindow::on_TableauClient_clicked()
{
    ui->EditerClient->setEnabled(true);
    ui->SupprimerClients->setEnabled(true);
    ui->widgetForNouveauClients->setVisible(false);
    int SelectedRow=ui->TableauClient->currentRow();
    CLI ncli;
    strcpy(ncli.numCli,(ui->TableauClient->item(SelectedRow,0)->text().toLatin1()));
}

void MainWindow::on_txtCherchCli_textEdited()
{
    QString cherche=ui->txtCherchCli->text();
    if(cherche.isEmpty()){
        AfficherCli();
        //QMessageBox::critical(this,"","Putin");
        ui->AnnulerRechercheClients->setVisible(false);
    }
        ui->AnnulerRechercheClients->setVisible(true);
}

void MainWindow::on_ClientBoutton_clicked()
{
      ui->AnnulerechercheMateriel->setVisible(false);
      ui->GestionCLient->setCurrentIndex(1);
      AfficherCli();
}

void MainWindow::on_MaterielButton_clicked()
{
      ui->AnnulerechercheMateriel->setVisible(false);
    ui->GestionCLient->setCurrentIndex(2);
    AfficherMateriel();

}

void MainWindow::on_AchatsBouton_clicked()
{
    ui->AnnulerechercheMateriel->setVisible(false);
    ui->GestionCLient->setCurrentIndex(3);
    LesCodeAutomatique();
    RemplireTableauCommande();

}

/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //L'ALGORITHME CONCERNANT CLIENTS SE TERMINE ICI//
/*===============================================================================================================*/
/*=============================================================================================================*/




/*=============================================================================================================*/
/*===============================================================================================================*/
                                      // A PROPOS DE MATERIEL//
/*===============================================================================================================*/
/*==============================================================================================================*/



void MainWindow::AfficherMateriel()
{
    int nb;
    MAT*Materiel=NbTotaleDesMateriel(&nb);
    int i;
    ui->MaterieTab->setRowCount(0);
    for(i=0;i<nb;i++)
    {
        int nbRows = ui->MaterieTab->rowCount();
        ui->MaterieTab->insertRow(nbRows);
        QTableWidgetItem *itemnumMat = new  QTableWidgetItem(Materiel[i].numMat);
        QTableWidgetItem *itemDesign = new  QTableWidgetItem(QString::fromLatin1(Materiel[i].Design).replace(":", " "));
        QTableWidgetItem *itemPuReal = new  QTableWidgetItem(QString::number(Materiel[i].PuReal));
        QTableWidgetItem *itemStock  = new  QTableWidgetItem(QString::number(Materiel[i].Stock));
        ui->MaterieTab->setItem(nbRows,0,itemnumMat);
        ui->MaterieTab->setItem(nbRows,1,itemDesign);
        ui->MaterieTab->setItem(nbRows,2,itemPuReal);
        ui->MaterieTab->setItem(nbRows,3,itemStock);
    }
}

void MainWindow::on_SupprimerMateriel_clicked()
{
    int nb=ui->MaterieTab->currentRow();
    MAT Materiel;
    if(nb<0){
        QMessageBox::warning(this,"Erreur","Aucun ligne Selectioner");
        return;
    }
    int r=QMessageBox::question(this,"Confirmer suppression","Voulez-vous supprimer  ce materiel"
                                ,QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
        strcpy(Materiel.numMat,ui->MaterieTab->item(nb,0)->text().toLatin1());
        strcpy(Materiel.Design,ui->MaterieTab->item(nb,1)->text().toLatin1());
        Materiel.PuReal=ui->MaterieTab->item(nb,2)->text().toInt();
        Materiel.Stock=ui->MaterieTab->item(nb,3)->text().toInt();
        ui->MaterieTab->removeRow(nb);
        SupprimerMateriel(Materiel);
        QMessageBox::information(this,"Suppression","Materiel supprimer avec succèes");
    }
    AfficherMateriel();
}

void MainWindow::on_EditerMateriel_clicked()
{
    ui->pushButton_8->setVisible(true);
    ui->Enregistrer->setVisible(true);
    ui->AjouterMateriel->setVisible(false);
    ui->groupeBoxForinformation->setVisible(false);
    ui->GROUPEBOXNOUVEAUMateriel->setVisible(true);
    int nb=ui->MaterieTab->currentRow();
    if(nb<0){
        QMessageBox::warning(this,"Erreur","Aucune ligne Selectioner");
        return;
    }
   else{
        ui->CodeMateriel->setText(ui->MaterieTab->item(nb,0)->text());
        ui->DesignationMateriel->setText(ui->MaterieTab->item(nb,1)->text());
        ui->PrixReelMateriel->setValue(ui->MaterieTab->item(nb,2)->text().toInt());
        ui->StockCommande->setValue(ui->MaterieTab->item(nb,3)->text().toInt());
    }
}

void MainWindow::on_AjouterMateriel_clicked()
{
    MAT Materiel1;
    QString numMat=ui->CodeMateriel->text();
    QString Design=ui->DesignationMateriel->text().replace(" ",":");
    int PuReal=ui->PrixReelMateriel->text().toInt();
    int Stock=ui->StockCommande->text().toInt();
    if(numMat.isEmpty() || Design.isEmpty()){
        QMessageBox::warning(this,"Champs vide","Veuillez remplir le formulaire");
        return;
    }
    int n=DeterminerNbCommande();
    strcpy(Materiel1.numMat,numMat.toLatin1());
    strcpy(Materiel1.Design,Design.toLatin1());
    Materiel1.PuReal=PuReal;
    Materiel1.Stock=Stock;
    if(IsExistMateriel(Materiel1)){
         QMessageBox::warning(this,"Information","Materiel deja saisi");
         return;

    }
    else{
        RemplireFichierMateriel(Materiel1);
        AfficherMateriel();
        clearForm();
        LesCodeAutomatique();
        cb();
        QMessageBox::information(this,"information","Enregistrement effectuer");
        ui->GROUPEBOXNOUVEAUMateriel->setVisible(false);
    }
}

void MainWindow::on_Enregistrer_clicked()
{
    QString numMat=ui->CodeMateriel->text();
    QString Design=ui->DesignationMateriel->text().replace(" ",":");
    int PuReal=ui->PrixReelMateriel->text().toInt();
    int Stock=ui->StockCommande->text().toInt();
    if(numMat.isEmpty() || Design.isEmpty())
    {
        QMessageBox::warning(this,"Champs vide","Veillez remplire le formulaire");
        return;
    }
    else{
         MAT Materiel1;
         strcpy(Materiel1.numMat,numMat.toLatin1());
         strcpy(Materiel1.Design,Design.toLatin1());
         Materiel1.PuReal=PuReal;
         Materiel1.Stock=Stock;
         QMessageBox::question(this,"Confirmation de modification","Vous voulez enregistrer la modifacation?");
         EditerMateriel(Materiel1);
         AfficherMateriel();
         clearForm();
         QMessageBox::information(this,"Information","Modification avec succès");
         ui->GROUPEBOXNOUVEAUMateriel->setVisible(false);
         ui->GestionCLient->setCurrentIndex(2);
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    RechercheMateriel();
}

void MainWindow::RechercheMateriel()
{
    /*
    QString txt=ui->RechercheMateriele->text().toUpper();
    int i;
    if(!txt.isEmpty())
    {
        for(i=0;i<ui->MaterieTab->rowCount();i++)
        {
            if(ui->MaterieTab->item(i,0)->text().toUpper().indexOf(txt)<0 && (ui->MaterieTab->item(i,1)->text().toUpper().indexOf(txt)<0) && (ui->MaterieTab->item(i,2)->text().toUpper().indexOf(txt)<0) && (ui->MaterieTab->item(i,3)->text().toUpper().indexOf(txt)<0)){
            ui->MaterieTab->removeRow(i);
            }

        }
    }
    else {
        AfficherMateriel();
    }
   */
    char txt[20];
    QString recherche=ui->RechercheMateriele->text();
    strcpy(txt,recherche.toLatin1().replace(" ",":"));
    if(recherche==""){
        AfficherMateriel();
        QMessageBox::warning(this,"Error","Entrer le designation ou code le code du materiel");
    }
    else{
        int n=0,trouve=0;
        MAT*Materiel=RechercheMateriele(txt,&n,&trouve);
        if(trouve==0){
            QMessageBox::information(this,"Recherche","Materiel non trover");
             ui->RechercheMateriele->setText("");
            AfficherMateriel();
        }
        else{
            if(n==0) return;
            int i=0;
            ui->MaterieTab->setRowCount(0);
            for(i=0;i<n;i++ ){
                ui->MaterieTab->insertRow(i);
                ui->MaterieTab->setItem(i,0,new QTableWidgetItem(Materiel[i].numMat));
                ui->MaterieTab->setItem(i,1,new QTableWidgetItem(QString::fromLatin1(Materiel[i].Design).replace(":"," ")));
                ui->MaterieTab->setItem(i,2,new QTableWidgetItem(QString::number(Materiel[i].PuReal)));
                ui->MaterieTab->setItem(i,3,new QTableWidgetItem(QString::number(Materiel[i].Stock)));
            }
        }
    }
}

void MainWindow::on_NouveauMateriel_clicked()
{
       LesCodeAutomatique();
       ui->SupprimerMateriel->setEnabled(false);
       ui->EditerMateriel->setEnabled(false);
       ui->GROUPEBOXNOUVEAUMateriel->setVisible(true);
       ui->groupeBoxForinformation->setVisible(false);
       ui->CodeMateriel->setReadOnly(true);
       ui->Enregistrer->setVisible(false);
       ui->AjouterMateriel->setVisible(true);
       clearForm();
}

void MainWindow::on_AnnulerechercheMateriel_clicked()
{
    AfficherMateriel();
    ui->RechercheMateriele->setText("");
}

/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //L'ALGORITHME CONCERNAT MATERIEL SE TERMINE ICI//
/*===============================================================================================================*/
/*==============================================================================================================*/



/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //L'ALGORITHME CONCERNAT l"ACHAT//
/*===============================================================================================================*/
/*==============================================================================================================*/

void MainWindow::RemplireTableauCommande()
{
    int nb,i=0;
    Achat*commande=DeterminerNbCommande(&nb);
    ui->TableauCommande->setRowCount(0);
    for(i=0;i<nb;i++){
        ui->TableauCommande->insertRow(i);
        ui->TableauCommande->setItem(i,0,new QTableWidgetItem(commande[i].index));
        ui->TableauCommande->setItem(i,1,new QTableWidgetItem(commande[i].numClient));
        ui->TableauCommande->setItem(i,2,new QTableWidgetItem(QString::number(commande[i].Totale)));
        ui->TableauCommande->setItem(i,3,new QTableWidgetItem(commande[i].date));
        int trouve=IsCommandeaunefacture(commande[i].index);
        if(!trouve){
            ui->TableauCommande->setItem(i,4,new QTableWidgetItem("NON"));
         }
        else{
            ui->TableauCommande->setItem(i,4,new QTableWidgetItem("OUI"));
        }
        ui->TableauCommande->item(i,4)->setTextAlignment(Qt::AlignCenter);

   }

}


/*
void MainWindow::on_Effectuerlachat_clicked()
{
      Achat commande;
      int Nouveau,Prix,vola,Stock,vola1,VolaVaovao;
      Stock=IsExistMateriel2pourVoirLecontenueDeStock(commande);
      if( && !numMat.isEmpty() && Qte!=NULL){
              if(Qte>=1){
                  if(Stock>=Qte && ExistClientCommande(commande) && IsExistMaterielCommande(commande)){
                           Prix=IsExistMateriel2pourVoirLecontenueDePrixreel(commande);
                           vola=(Prix*Qte);
                           vola1=ExisteClientsDansCommande1(commande);
                           Nouveau=(Stock-Qte);
                           RemplireFichierCommande(commande);
                           RemplireTableauCommande();
                           FonctionDeVariationdesStock(Nouveau,commande);
                           AfficherMateriel();
                           VolaVaovao=(vola+vola1);
                           ExistClientDansLeCommandePourFaireLeRetablisementDuPrixTotal(commande,VolaVaovao);
                           AfficherTousLesChiffresDAffaireDeChaqueClients();
                           clearForm();
                           QMessageBox::information(this,"Confirmation","Achats effectuer avec succèe",QMessageBox::Yes);
                           LesCodeAutomatique();
                           initialiserCli();
                     }
                  else if(!ExistClientCommande(commande)){
                      QMessageBox::critical(this,"Clients existe","Le cliens que vous avez entrer n'existe pas");
                  }
                  else if(!IsExistMaterielCommande(commande)){
                       QMessageBox::critical(this,"Materiel existe","Le materiel que vous avez entrer n'existe pas");
                  }
                  else{
                       QMessageBox::warning(this,"Erreur","Stock insuffisant");
                  }
              }
              else{
                  QMessageBox::warning(this,"Erreur","Le Quantiter ne doivent pas être zero 0");
                }
      }
      else{
          QMessageBox::warning(this,"Erreur","Veillez remplire tous le formulaire");
      }
}
*/
void MainWindow::on_SuprimerComande_clicked()
{
    int nb=ui->TableauCommande->currentRow();
    Achat commande;
    if(nb<0){
        QMessageBox::warning(this,"Erreur","Aucune ligne selectionner");
        return;
    }
    int r=QMessageBox::question(this,"Confirmation","Voulez vous supprimer definitivement ce commande",QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
         strcpy(commande.index,(ui->TableauCommande->item(nb,0)->text().toLatin1()));
         //Suppression de Tous les commandes concerner
         com CM;
         strcpy(CM.NC,commande.index);
         int vola1=0,VolaVaovao=0,n=0,i=0,Stock=0,Nouveau=0;
         strcpy(commande.numClient,(ui->TableauCommande->item(nb,1)->text().toLatin1()));
         commande.Totale=ui->TableauCommande->item(nb,2)->text().toInt();
         strcpy(commande.date,ui->TableauCommande->item(nb,3)->text().toLatin1());
         vola1=ValeurDuChiffredaffaireParClient(commande);
         com*CM1=LirelesFichierFCM1(&n,CM);
         printf("n==%d",n);
         while(i<n){
             printf("NUMAT 1=%s\t",CM1[i].NM);
             Stock=IsExistMateriel2pourVoirLecontenueDeStock2(CM1[i].NM);//Recuperztion des stock disponible
             Nouveau=Stock+CM1[i].QT;
             FonctionDeVariationdesStockcommande1(Nouveau,CM1[i].NM);//Variation de stock materiel
             i++;
         }
         SupprimerCommande(CM);
         DeleteCommande(commande);
         VolaVaovao=(vola1-(commande.Totale));
         ExistClientDansLeCommandePourFaireLeRetablisementDuPrixTotal(commande,VolaVaovao);
         AfficherTousLesChiffresDAffaireDeChaqueClients();
         RemplireTableauCommande();
         AfficherMateriel();
         QMessageBox::information(this,"Suppression","Commande supprimer avec succès");
    }
    initialiserCli();
}
void MainWindow::on_EditerCommande_clicked()
{
    com*CM,CM1;
    int i=0,n,trouve,nba=0,Totale=0;
    int nb=ui->TableauCommande->currentRow();
    ui->pushButtonEnrengistrerlesmodification->setEnabled(false);
    ui->tableWidgetforCommande->setRowCount(0);
    ui->label_14->setText("EDITION COMMANDE");
    ui->pushButtonforsupprimerCommande->setEnabled(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButtonEnrengistrerlesmodification->setVisible(true);
        if(nb<0){
           QMessageBox::warning(this,"Erreur","Aucune ligne selectionner");
           return;
        }
        strcpy(CM1.a,ui->TableauCommande->item(nb,4)->text().toLatin1());
        if(strcmp(CM1.a,"NON")==0){
            strcpy(CM1.NC,ui->TableauCommande->item(nb,0)->text().toLatin1());
            strcpy(CM1.NM,ui->TableauCommande->item(nb,1)->text().toLatin1());
            Totale=ui->TableauCommande->item(nb,2)->text().toInt();
            CLI*ncli=RechercheClient(CM1.NM,&nba,&trouve);
            ui->lineEditforNumeroClientsCommande->setText(CM1.NM);
            ui->labelTotaleTemporaire->setText(QString::number(Totale));
            ui->lineEdit->setText(CM1.NOM);
            ui->label_25->setText(CM1.NC);
            ui->lineEdit->setText(QString::fromLatin1(ncli[i].nomCli).replace(":"," "));
            ui->dateEditforCommande->setDate(QDate::fromString(ui->TableauCommande->item(nb,3)->text().toLatin1(),"dd-MM-yyyy"));
            ui->GestionCLient->setCurrentIndex(4);
            CM=LirelesFichierFCM1(&n,CM1);
            ui->tableWidgetforCommande->removeRow(0);
            for(i=0;i<n;i++){
                ui->tableWidgetforCommande->insertRow(i);
                ui->tableWidgetforCommande->setItem(i,0,new QTableWidgetItem(CM[i].NM));
                ui->tableWidgetforCommande->setItem(i,1,new QTableWidgetItem(QString::number(CM[i].PU)));
                ui->tableWidgetforCommande->setItem(i,2,new QTableWidgetItem(QString::number(CM[i].QT)));
                ui->tableWidgetforCommande->setItem(i,3,new QTableWidgetItem(QString::number(CM[i].TL)));
            }
               ui->EditerCommande->setEnabled(false);
          }
        else{
              QMessageBox::information(this,"Information","Commande dejà payé \nVous ne pouvez pas modifier");
        }
}

void MainWindow::on_TableauCommande_clicked(const QModelIndex &index)
{
   ui->EditerCommande->setEnabled(true);
   ui->SuprimerComande->setEnabled(true);
}

/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //FIN DE L'ALGORITHME CONCERNAT l'ACHAT//
/*===============================================================================================================*/
/*==============================================================================================================*/




/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //ALGORITHME DE FACTURES//
/*===============================================================================================================*/
/*==============================================================================================================*/


void MainWindow::Creefacture(com CM)
{
    FAC v;
    CONVERSION lettre;
    string d=lettre.Convertir(CM.TL);
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("Facture.pdf");
    QPainter painter;
    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }
    else{
           painter.drawText(120,20,"FACTURE N°:"" "+QString::fromLatin1(CM.FACT));
           painter.drawText(120,40,"N°CLIENT:"" "+QString::fromLatin1(CM.CCL));
           painter.drawText(400,40,"DATE:"" "+QString::fromLatin1(CM.DATE));
           painter.drawText(120,60,"NOM:"" "+QString::fromLatin1(CM.NOM).replace(":"," "));
           painter.drawText(120,120,"DESIGNATION");
           painter.drawText(240,120,"PU");
           painter.drawText(330,120,"QUANTITE");
           painter.drawText(420,120,"MONTANT (AR)");

           int i=0,e=0,nb=0,somme=100,b=20,colone=110,Heightcolone,p=155,Tailleoneligne;
           //Test pour le l"ajout des lignes pour le facture//
           com*CM1=LirelesFichierFCM1(&nb,CM);

           Tailleoneligne=25;

          //Insertion des ligne

           for(i=0;i<nb;i++){
               if(i==0){
                   b=b+80;
                   QRect rect(110,somme,400,25);//	QRect(int x, int y, int width, int height)
                   painter.drawRect(rect);
               }
               somme=somme+25;
               b=b+80;
               printf("CM.Qt==%d",CM1[i].QT);
               QRect rect(110,somme,400,25);//	QRect(int x, int y, int width, int height)
               painter.drawRect(rect);
               MAT*a=Recupererdesignation(CM1[i].NM);
               painter.drawText(120,(somme+20),QString::fromLatin1(a[e].Design).replace(":"," "));
               painter.drawText(240,(somme+20),QString::number(CM1[i].PU));
               painter.drawText(330,(somme+20),QString::number(CM1[i].QT));
               painter.drawText(420,(somme+20),QString::number(CM1[i].TL));
          }
           //insertion des colones

           for(i=0;i<=2;i++){
               colone=colone+100;
               Heightcolone=Tailleoneligne*(nb+1);
               QRect rec2(colone,100,100,Heightcolone);
               painter.drawRect(rec2);
               if(i==2){
                   QRect rec(310,100,100,(Heightcolone+25));
                   painter.drawRect(rec);
                   QRect rec2(410,100,100,(Heightcolone+25));
                   painter.drawRect(rec2);
                   painter.drawText(330,(120+Heightcolone),"TOTAL");
                   painter.drawText(420,(120+Heightcolone),QString::number(CM.TL));
               }
           }
           painter.drawText(120,(Heightcolone+p),"Arretée la présente facture à la somme de "+QString::fromLatin1(d.c_str())+" ""Ar.");
           painter.end();
    }

}

void MainWindow::on_factureBouton_clicked()
{
    int nb=ui->TableauCommande->currentRow();
    if(nb<0){
        QMessageBox::warning(this,"Error","Veillez selectionnez une ligne");
    }
    else{
            LesCodeAutomatique();
            ui->label_30->setVisible(false);
            ui->label_3->setVisible(false);
            ui->tableWidgetforfacture->setRowCount(0);
            com*CM,CM1;
            int i=0,n,e=0,trouve,nba=0,Totale=0;
            strcpy(CM1.a,ui->TableauCommande->item(nb,4)->text().toLatin1());
            if(strcmp(CM1.a,"NON")==0){
                ui->GestionCLient->setCurrentIndex(6);
                strcpy(CM1.NC,ui->TableauCommande->item(nb,0)->text().toLatin1());
                Totale=ui->TableauCommande->item(nb,2)->text().toInt();
                strcpy(CM1.CCL,ui->TableauCommande->item(nb,1)->text().toLatin1());
                if(nb<0){
                   QMessageBox::warning(this,"Erreur","Selectionner au moins une ligne");
                   return;
                }

                CM=LirelesFichierFCM1(&n,CM1);
                CLI*ncli=RechercheClient(CM1.CCL,&nba,&trouve);
                ui->label_3->setText(QString::fromLatin1(CM1.NC));
                ui->label_12->setText(QString::fromLatin1(CM1.CCL));
                strcpy(CM1.FACT,ui->label_10->text().toLatin1());
                ui->label_30->setText(QString::number(Totale));
                ui->label_21->setText(QString::fromLatin1(ncli[i].nomCli).replace(":"," "));
                ui->label_19->setText(ui->TableauCommande->item(nb,3)->text().toLatin1());
                ui->tableWidgetforfacture->removeRow(0);
                for(i=0;i<=n;i++){
                    ui->tableWidgetforfacture->insertRow(i);
                    MAT*a=Recupererdesignation(CM[i].NM);
                    ui->tableWidgetforfacture->setItem(i,0,new QTableWidgetItem(QString::fromLatin1(a[e].Design).replace(":"," ")));
                    ui->tableWidgetforfacture->setItem(i,1,new QTableWidgetItem(QString::number(CM[i].PU)));
                    ui->tableWidgetforfacture->setItem(i,2,new QTableWidgetItem(QString::number(CM[i].QT)));
                    ui->tableWidgetforfacture->setItem(i,3,new QTableWidgetItem(QString::number(CM[i].TL)));
                    if(i==n){
                        ui->tableWidgetforfacture->setItem(i,0,new QTableWidgetItem(""));
                        ui->tableWidgetforfacture->setItem(i,1,new QTableWidgetItem(""));
                        ui->tableWidgetforfacture->setItem(i,2,new QTableWidgetItem("TOTAL"));
                        ui->tableWidgetforfacture->setItem(i,3,new QTableWidgetItem(QString::number(Totale)));
                    }
                    ui->tableWidgetforfacture->item(i,1)->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidgetforfacture->item(i,2)->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidgetforfacture->item(i,3)->setTextAlignment(Qt::AlignCenter);
                }
                CONVERSION lettre;
                string d=lettre.Convertir(Totale);
                ui->label_29->setText("Arretée la presente facture à la somme de"" "+QString::fromLatin1(d.c_str())+" ""Ar.");
            }
            else{
                 QMessageBox::information(this,"Information","Facture dejà payé");
            }

       }
}
QComboBox *MainWindow::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
void MainWindow::b()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());

    if (!directory.isEmpty()) {
        if (directoryComboBox->findText(directory) == -1)
            directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}

/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //ALGORITHME DE FACTURES//
/*===============================================================================================================*/
/*==============================================================================================================*/


/*=============================================================================================================*/
/*===============================================================================================================*/
                                      //ALGORITHME DE CHIFFRE D'AFFAIRE//
/*===============================================================================================================*/
/*==============================================================================================================*/

void MainWindow::on_ChiffredAffaire_clicked()
{
    ui->GestionCLient->setCurrentIndex(5);
}


void MainWindow::AfficherTousLesChiffresDAffaireDeChaqueClients()
{
    int n;
    Affaire*Aff=TousClientdAffaire(&n);
    int i=0;
    ui->TableauChiffresdAffaire->setRowCount(0);
    for(i=0;i<n;i++)
    {
        ui->TableauChiffresdAffaire->insertRow(i);
        ui->TableauChiffresdAffaire->setItem(i,0,new QTableWidgetItem(Aff[i].NUM));
        ui->TableauChiffresdAffaire->setItem(i,1,new QTableWidgetItem(QString::fromLatin1(Aff[i].NOM).replace(":"," ")));
        ui->TableauChiffresdAffaire->setItem(i,2,new QTableWidgetItem (QString::number(Aff[i].vola)));
    }
}



/*=============================================================================================================*/
/*===============================================================================================================*/
                                      // FIN DE L'ALGORITHME DE CHIFFRE D'AFFAIRE//
/*===============================================================================================================*/
/*==============================================================================================================*/


void MainWindow::on_ButtonNouveauClients_clicked()
{
    ui->EnrengistrerClient->setVisible(false);
    ui->AjouterClient->setVisible(true);
    ui->widgetForNouveauClients->setVisible(true);
    LesCodeAutomatique();
    clearForm();
}

void MainWindow::on_ButtonAnnuler_clicked()
{
    QString nomClients=ui->NomEdit->text().toLatin1();
    QMessageBox::information(this,"Nouveau clients","Vous voulez annuler vraiment?\nTous le donner dans la formulaire sera perdu",QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes  && !(nomClients.isEmpty())){
        clearForm();
        ui->widgetForNouveauClients->setVisible(false);
    }
}


void MainWindow::on_MaterieTab_clicked(const QModelIndex &index)
{
    int nb=ui->MaterieTab->currentRow();
    MAT Materiel;
    ui->EditerMateriel->setEnabled(true);
    ui->SupprimerMateriel->setEnabled(true);
    ui->GROUPEBOXNOUVEAUMateriel->setVisible(false);
   // ui->groupeBoxForinformation->setVisible(true);
    strcpy(Materiel.numMat,(ui->MaterieTab->item(nb,0)->text().toLatin1()));
    Materiel.PuReal=(ui->MaterieTab->item(nb,2)->text().toInt());
    ui->labelforCodeClients->setText(Materiel.numMat);
    int Total=RecuperationdesNombreTotaleDeVenteDunMateriel(Materiel);
    if(Total==NULL){
        ui->labelForTotaldesVante->setText("Aucune vente");
    }
    else{
        ui->labelForTotaldesVante->setText(QString::number(Total));
    }
    int Prix=(Total*(Materiel.PuReal));
    ui->labelForProxTotal->setText(QString::number(Prix));
}

void MainWindow::on_ButtonImprimer_clicked()
{
    QPrinter printer;
    printer.setPrinterName("johny lino");
    QPrintDialog mainwindow(&printer,this);
    if(mainwindow.exec() == QDialog::Rejected) return;
    //ui->textEdit->print(&printer);
}

void MainWindow::on_pushButtonNouveauCommande_clicked()
{
    LesCodeAutomatique();
    ui->label_14->setText("CREATION COMMANDE");
    ui->pushButtonforsupprimerCommande->setEnabled(false);
    ui->pushButton_3->setVisible(true);
    ui->GestionCLient->setCurrentIndex(4);
    ui->lineEditforNumeroClientsCommande->setText("");
    ui->lineEdit->setText("");
    ui->dateEditforCommande->setDate(QDate::currentDate());
    ui->pushButtonEnrengistrerlesmodification->setVisible(false);
    ui->comboBoxforClients->setCurrentIndex(0);
    ui->comboBoxFroNomclients->setCurrentIndex(0);
    ui->tableWidgetforCommande->setRowCount(0);
    ui->lineEdit->setReadOnly(true);
       ui->pushButtonEnrengistrerlesmodification->setEnabled(false);
}

void MainWindow::commande()
{
    ui->tableWidgetforCommande->setRowCount(0);
    ui->tableWidgetforCommande->insertRow(0);
}

void MainWindow::on_pushButtonforAutre_clicked()
{
      ui->tableWidgetforCommande->insertRow(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    com CM;
    Achat commande;
    int n=ui->tableWidgetforCommande->rowCount();
    printf("n==%d",n);
    int i=0,Totale=0,Stock=0,Nouveau=0;
    QString NumeroCommande=ui->label_25->text();
    QString Date=ui->dateEditforCommande->text();
    QString index=ui->label_25->text().toLatin1();
    QString numClient= ui->lineEditforNumeroClientsCommande->text().toLatin1();
    strcpy(commande.index,index.toLatin1());
    strcpy(commande.numClient,numClient.toLatin1());
    if(n>0){
            if(numClient.isEmpty()){
                QMessageBox::warning(this,"Code client vide","Error ,code client vide");
                n<0;
            }
            else{
                int trouves=0;
                for(i=0;i<n;i++){
                    QString NumMat=ui->tableWidgetforCommande->item(i,0)->text().toLatin1();
                    int Pu=ui->tableWidgetforCommande->item(i,1)->text().toInt();
                    int Quantiter=ui->tableWidgetforCommande->item(i,2)->text().toInt();
                    int montant=Pu*Quantiter;
                    strcpy(CM.NC,NumeroCommande.toLatin1());
                    strcpy(CM.NM,NumMat.toLatin1());
                    CM.PU=Pu;
                    CM.QT=Quantiter;
                    CM.TL=montant;
                    strcpy(CM.DATE,Date.toLatin1());
                    strcpy(CM.CCL,numClient.toLatin1());
                    if(NumMat.isEmpty()){
                        QMessageBox::warning(this,"Code article vide","Veillez entrer le code Article");
                        i=n;
                    }
                    else if(Quantiter==NULL){
                        QMessageBox::warning(this,"Quantiter ","Veillez entrer le quatiter");
                        i=n;
                    }
                    else if(Quantiter<0){
                        QMessageBox::warning(this,"Quantiter ","Le quantiter ne peux pas être inferieur à zero");
                        trouves=1;
                        i=n;
                    }
                    else{
                        ui->tableWidgetforCommande->setItem(i,3,new QTableWidgetItem(QString::number(montant)));
                        Stock=IsExistMateriel2pourVoirLecontenueDeStockcommande(CM);
                        if(Stock<Quantiter){
                                QMessageBox::information(this,"Stock insuffisant","Commande non effectuer ,stock insuffisant pour l'article"" "+QString::fromLatin1(CM.NM)+"\n""Stock disponible"" "+QString::number(Stock));
                                i=n;
                        }
                        else{
                                RemplireFichierCommande1(CM);
                                Totale=Totale+montant;
                                Nouveau=Stock-Quantiter;
                                FonctionDeVariationdesStockcommande(Nouveau,CM);
                                commande.Totale=Totale;
                                strcpy(commande.date,Date.toLatin1());
                                AfficherMateriel();
                                AfficherTousLesChiffresDAffaireDeChaqueClients();
                                ui->GestionCLient->setCurrentIndex(3);
                            }
                        }
                    }
                                                QMessageBox::information(this,"Commande","Commande"" "+QString::fromLatin1(CM.NC)+" ""enrengistrer avec succèes");
            }
           int n=DeterminerNbCommande();
           commande.numero=n;
           RemplireFichierCommande(commande);
    }
    else{
          QMessageBox::information(this,"Information","Ajouter au moins une ligne pour une nouvelle commande");
    }
    RemplireTableauCommande();
}
void MainWindow::PlacerLenomDuClientsSelectionner(char*CodeClients)
{
    printf("codeClients==%s",CodeClients);
    QMessageBox::information(this,"",QString::fromLatin1(CodeClients));
    ui->lineEditforNumeroClientsCommande->setText(CodeClients);
}

void MainWindow::on_comboBoxforClients_currentIndexChanged(int index)
{

    int n=0;
    CLI*ncli=TousClient(&n);
    if(n==0 || n<index) return;
    if(index==0){
          ui->lineEditforNumeroClientsCommande->setText("");
          ui->lineEdit->setText("");
    }
    else{
          ui->lineEditforNumeroClientsCommande->setText(ncli[index-1].numCli);
          ui->lineEdit->setText(QString::fromLatin1(ncli[index-1].nomCli).replace(":"," "));
    }
}



void MainWindow::on_pushButtonEnrengistrerlesmodification_clicked()
{
    int n=0,i=0,b=0,nb=0,Stock=0,Stock1=0,Nouveau=0,Nouveaua=0,Quantiter,Pu,montant;
    com CM;
    strcpy(CM.NC,ui->label_25->text().toLatin1());
    com*CM1=LirelesFichierFCM1(&nb,CM);
    while(i<nb){
        Stock=IsExistMateriel2pourVoirLecontenueDeStock2(CM1[i].NM);//Recuperation des stock disponible
        Nouveau=Stock+CM1[i].QT;
        FonctionDeVariationdesStockcommande1(Nouveau,CM1[i].NM);//Variation de stock materiel
        i++;
    }
    SupprimerCommande(CM);
    AfficherMateriel();
    n=ui->tableWidgetforCommande->rowCount();
    for(i=0;i<n;i++){
        QString NumMat=ui->tableWidgetforCommande->item(i,0)->text().toLatin1();
        strcpy(CM.NM,NumMat.toLatin1());
        Stock1=IsExistMateriel2pourVoirLecontenueDeStock2(CM.NM);//Recuperztion des stock disponible
        Quantiter=ui->tableWidgetforCommande->item(i,2)->text().toInt();
        if(Stock1>=Quantiter){
            QString Date=ui->dateEditforCommande->text();
            QString numclients=ui->lineEditforNumeroClientsCommande->text().toLatin1();
            Pu=ui->tableWidgetforCommande->item(i,1)->text().toInt();
            montant=Pu*Quantiter;
            CM.PU=Pu;
            CM.TL=montant;
            CM.QT=Quantiter;
            strcpy(CM.DATE,Date.toLatin1());
            strcpy(CM.CCL,numclients.toLatin1());
            ui->tableWidgetforCommande->setItem(i,3,new QTableWidgetItem(QString::number(montant)));
            RemplireFichierCommande1(CM);
                b+=montant;
                Nouveaua=Stock1-Quantiter;
                FonctionDeVariationdesStockcommande(Nouveaua,CM);//Variation de stock materiel
                EditerCommande1(b,CM);
                RemplireTableauCommande();
                AfficherMateriel();
                ui->GestionCLient->setCurrentIndex(3);
        }
        else{
            QMessageBox::information(this,"Information","Stock insuffisant pour l'Article"" "+QString::fromLatin1(CM1[i].NM));
            i=n;
         }
    }

}

void MainWindow::on_pushButtonforsupprimerCommande_clicked()
{
    com CM;
    int nb=ui->tableWidgetforCommande->currentRow();
    strcpy(CM.NC,ui->label_25->text().toLatin1());
    strcpy(CM.NM,ui->tableWidgetforCommande->item(nb,0)->text().toLatin1());
    strcpy(CM.CCL,ui->lineEditforNumeroClientsCommande->text().toLatin1());
    CM.QT=ui->tableWidgetforCommande->item(nb,2)->text().toInt();
    CM.TL=ui->tableWidgetforCommande->item(nb,3)->text().toInt();
    SupprimerCommande2(CM);
    int Stock=IsExistMateriel2pourVoirLecontenueDeStock1(CM);
    int Nouveau=Stock+(CM.QT);
    FonctionDeVariationdesStock1(Nouveau,CM);

    int Totale=RecupererTotale(CM);
    printf("TOTALE=%d",Totale);
    int Vola2=Totale-CM.TL;
    FonctionDeRetabTotalCO(Vola2,CM);
    ui->tableWidgetforCommande->removeRow(nb);
  //  int n=ui->tableWidgetforCommande->rowCount();
   /* if(n==0){

       DeleteCommande3(CM);
    }
    else{
    }
    */
    RemplireTableauCommande();
    AfficherMateriel();
}

void MainWindow::on_tableWidgetforCommande_clicked(const QModelIndex &index)
{
    ui->pushButtonforsupprimerCommande->setEnabled(true);
    ui->pushButtonEnrengistrerlesmodification->setEnabled(true);
     // recuperation prix reel Prix=IsExistMateriel2pourVoirLecontenueDePrixreel(commande1);
}


void MainWindow::on_comboBoxFroNomclients_currentIndexChanged(int index)
{
    int n=0;
    CLI*ncli=TousClient(&n);
    if(n==0 || n<index) return;
    if(index==0){
          ui->lineEditforNumeroClientsCommande->setText("");
          ui->lineEdit->setText("");
    }
    else{
         ui->lineEdit->setText(QString::fromLatin1(ncli[index-1].nomCli).replace(":"," "));
         ui->lineEditforNumeroClientsCommande->setText(ncli[index-1].numCli);
         printf("ncli=%s",ncli[index-1].nomCli);
    }
}


void MainWindow::on_radiorechercheTous_clicked()
{
    ui->label_27->setVisible(false);
    ui->dateEditPourCommencer->setVisible(false);
    ui->labelZNtreDeuxDate->setVisible(false);
    ui->dateEditOurLimiteDeRecherche->setVisible(false);
    ui->dateEditForAnnee->setVisible(false);
    ui->dateEditPourLeMois->setVisible(false);
}

void MainWindow::on_pushButton_5_clicked()
{
      ui->AnnulerechercheMateriel->setVisible(false);
      ui->GestionCLient->setCurrentIndex(8);
      ui->stackedWidgetforgestiondespdf->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
      ui->AnnulerechercheMateriel->setVisible(false);
    ui->GestionCLient->setCurrentIndex(0);
}

void MainWindow::on_RechercheMateriele_textEdited()
{
    QString recherche=ui->RechercheMateriele->text();
    if(recherche=="NULL"){
        AfficherMateriel();
        ui->AnnulerechercheMateriel->setVisible(false);
    }
    ui->AnnulerechercheMateriel->setVisible(true);
 /*    else{
        QString txte=ui->RechercheMateriele->text().toUpper();
        printf("txt=%d",&txte);
        if(!txte.isEmpty()){
            for(int i=0;i<ui->MaterieTab->rowCount();i++){
                if(ui->MaterieTab->item(i,1)->text().toUpper().indexOf(txte)<0){
                     ui->MaterieTab->removeRow(i);
                }
             }
            if(ui->MaterieTab->rowCount()==0){
                QMessageBox::information(this,"","Materiel non trover");
                ui->RechercheMateriele->clear();
                AfficherMateriel();

            }
        }
     }
     */
}
void MainWindow::on_pushButton_7_clicked()
{
    com CM;
    FAC v;
    strcpy(CM.NC,ui->label_3->text().toLatin1());
    CM.TL=ui->label_30->text().toInt();
    strcpy(CM.CCL,ui->label_12->text().toLatin1());
    strcpy(CM.NOM,ui->label_21->text().toLatin1());
    strcpy(CM.DATE,ui->label_19->text().toLatin1());
    strcpy(CM.FACT,ui->label_10->text().toLatin1());
    int n=CodeAutomatique();
    v.numero=n;
    QMessageBox::information(this,"","Voulez vous vraiment generer ce facture en pdf",QMessageBox::No | QMessageBox::Yes);
    if(QMessageBox::Yes){
       strcpy(v.commande,CM.NC);
       strcpy(v.Facture,CM.FACT);
       Creefacture(CM);
       AjouterfactureEffectuer(v);
       RemplireTableauCommande();
       chiffredaffaire(CM);
       AfficherTousLesChiffresDAffaireDeChaqueClients();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox::information(this,"Annulation","Vous voulez annuler vraiment la modification?\n",QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes){
        ui->GROUPEBOXNOUVEAUMateriel->setVisible(false);
        ui->groupeBoxForinformation->setVisible(false);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    LesCodeAutomatique();
    ui->labelPoursavoirsilestsolderounon->setVisible(false);
    ui->labelforNumerocommande->setVisible(false);
    ui->labelforcodeclientscommande->setVisible(false);
    ui->labelForTotaleCommande->setVisible(false);
    ui->labelfrodateCommande->setVisible(false);
    com*CM,CM1;
    int i=0,n,e=0,Totale=0;
    int nb=ui->TableauCommande->currentRow();
    if(nb<0){
        QMessageBox::warning(this,"Error","Veillez selectionnez une ligne");
    }
    else{
        ui->GestionCLient->setCurrentIndex(7);
        strcpy(CM1.NC,ui->TableauCommande->item(nb,0)->text().toLatin1());
        ui->textBrowser_2->setText("CONTENUE DU COMMANDE"" "+QString::fromLatin1(CM1.NC));
        ui->textBrowser_2->setAlignment(Qt::AlignCenter);
        Totale=ui->TableauCommande->item(nb,2)->text().toInt();
        strcpy(CM1.CCL,ui->TableauCommande->item(nb,1)->text().toLatin1());
        strcpy(CM1.a,ui->TableauCommande->item(nb,4)->text().toLatin1());
        ui->labelPoursavoirsilestsolderounon->setText(QString::fromLatin1(CM1.a));
        ui->labelforNumerocommande->setText(QString::fromLatin1(CM1.NC));
        ui->labelforcodeclientscommande->setText(QString::fromLatin1(CM1.CCL));
        ui->labelForTotaleCommande->setText(QString::number(Totale));
        ui->labelfrodateCommande->setText(ui->TableauCommande->item(nb,3)->text().toLatin1());
        FAC*fact=RecherchenumFacture(CM1.NC);
        ui->labelNUMEROFACTURE->setText(fact[i].Facture);
        if(nb<0){
           QMessageBox::warning(this,"Erreur","Selectionner au moins une ligne dans le tableau");
           return;
        }
        CM=LirelesFichierFCM1(&n,CM1);
        ui->tableWidgetforVisualiserCommande->setRowCount(0);
        for(i=0;i<=n;i++){
            ui->tableWidgetforVisualiserCommande->insertRow(i);
            MAT*a=Recupererdesignation(CM[i].NM);
            ui->tableWidgetforVisualiserCommande->setItem(i,0,new QTableWidgetItem(QString::fromLatin1(a[e].Design).replace(":"," ")));
            ui->tableWidgetforVisualiserCommande->setItem(i,1,new QTableWidgetItem(QString::number(CM[i].PU)));
            ui->tableWidgetforVisualiserCommande->setItem(i,2,new QTableWidgetItem(QString::number(CM[i].QT)));
            ui->tableWidgetforVisualiserCommande->setItem(i,3,new QTableWidgetItem(QString::number(CM[i].TL)));
            if(i==n){
                ui->tableWidgetforVisualiserCommande->setItem(i,0,new QTableWidgetItem(""));
                ui->tableWidgetforVisualiserCommande->setItem(i,1,new QTableWidgetItem(""));
                ui->tableWidgetforVisualiserCommande->setItem(i,2,new QTableWidgetItem("TOTAL"));
                ui->tableWidgetforVisualiserCommande->setItem(i,3,new QTableWidgetItem(QString::number(Totale)));
            }
            ui->tableWidgetforVisualiserCommande->item(i,1)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetforVisualiserCommande->item(i,2)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetforVisualiserCommande->item(i,3)->setTextAlignment(Qt::AlignCenter);
        }
        CONVERSION lettre;
        string d=lettre.Convertir(Totale);
        ui->label_29->setText("Arretée la presente facture à la somme de"" "+QString::fromLatin1(d.c_str())+" ""Ar.");
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidgetforgestiondespdf->setCurrentIndex(0);
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidgetforgestiondespdf->setCurrentIndex(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidgetforgestiondespdf->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
    LesCodeAutomatique();
    com CM;
    FAC v;
    strcpy(CM.NC,ui->labelforNumerocommande->text().toLatin1());
    strcpy(CM.CCL,ui->labelforcodeclientscommande->text().toLatin1());
    CM.TL=ui->labelForTotaleCommande->text().toInt();
    strcpy(CM.FACT,ui->labelNUMEROFACTURE->text().toLatin1());
    if(strcmp(CM.FACT,"")==0){
        strcpy(CM.FACT,ui->label_31->text().toLatin1());
        int n= CodeAutomatique();
        v.numero=n;
        int i=0;
        strcpy(CM.DATE,ui->labelfrodateCommande->text().toLatin1());
        strcpy(CM.a,ui->labelPoursavoirsilestsolderounon->text().toLatin1());
        if(strcmp(CM.a,"NON")==0){
            int nba,trouve;
                   CLI*ncli=RechercheClient(CM.CCL,&nba,&trouve);
                   strcpy(CM.NOM,ncli[i].nomCli);
                   QMessageBox::information(this,"","Voulez vous vraiment generer ce facture en pdf",QMessageBox::No | QMessageBox::Yes);
                   if(QMessageBox::Yes){
                   strcpy(v.commande,CM.NC);
                   strcpy(v.Facture,CM.FACT);
                   Creefacture(CM);
                   AjouterfactureEffectuer(v);
                   RemplireTableauCommande();
                   chiffredaffaire(CM);
                   AfficherTousLesChiffresDAffaireDeChaqueClients();
                }
          }
    }
    else{
        QMessageBox::information(this,"Facture","Facture dejà paye");
    }
}
