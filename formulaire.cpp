#include "formulaire.h"
#include "ui_formulaire.h"
#include "mainwindow.h"
#include "QPainter"

Formulaire::Formulaire(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Formulaire)
{
    ui->setupUi(this);
}

Formulaire::~Formulaire()
{
    delete ui;
}
void Formulaire::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(100,100,"HELO johny");
    QRect rec(100,150,250,25);
    painter.drawRect(rec);
   // painter.drawText(rec.Qt::Aligntext);

}
