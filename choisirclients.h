#ifndef CHOISIRCLIENTS_H
#define CHOISIRCLIENTS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ChoisirClients;
}

class ChoisirClients : public QDialog
{
    Q_OBJECT

public:
    explicit ChoisirClients(QWidget *parent = 0);
    ~ChoisirClients();
    void AfficherCliPourcommande();

private slots:
    void on_pushButtonfroEnrengistrclient_clicked();

private:
    Ui::ChoisirClients *ui;
};

#endif // CHOISIRCLIENTS_H
