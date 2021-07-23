#ifndef FORMULAIRE_H
#define FORMULAIRE_H

#include <QDialog>

namespace Ui {
class Formulaire;
}

class Formulaire : public QDialog
{
    Q_OBJECT

public:
    explicit Formulaire(QDialog *parent = 0);
    ~Formulaire();

private:
    Ui::Formulaire *ui;

protected:
    void paintEvent(QPaintEvent*e);

};

#endif // FORMULAIRE_H
