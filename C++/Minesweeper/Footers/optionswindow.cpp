#include "optionswindow.hh"
#include <QApplication>
#include <QSpinBox>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QScreen>

/*
 * Rakentaja luokalle OptionsWindow, jota käytetään miinaharava-pelin laudan
 * muuttamisen mahdollistavien asetusten muokkaamiseen. Rakentaja muodostaa
 * laudan sivun koolle QSpinBoxin, jolla on maksimiarvo 18 ja minimi 6. Tä-
 * män kaveriksi luodaan QLineEdit siemenluvun kysymiseksi. Näitä kaaveraa
 * esittelevät QLabel tekstit.
 */
OptionsWindow::OptionsWindow(QWidget *parent)
    : QWidget(parent)
{
    board_side_box_ = new QSpinBox(this);
    board_side_box_->setGeometry(250, 0, 50, 50);
    board_side_box_->setValue(bs_);
    connect(board_side_box_, SIGNAL(valueChanged(int)), this, SLOT(set_bs()));
    board_side_box_->setMaximum(18);
    board_side_box_->setMinimum(6);
    board_side_box_->setAlignment(Qt::AlignCenter);

    seed_edit_ = new QLineEdit(this);
    seed_edit_->setGeometry(250, 50, 50, 50);
    connect(seed_edit_, SIGNAL(textChanged(QString)), this, SLOT(set_seed()));
    seed_edit_->setAlignment(Qt::AlignCenter);

    board_side_label_ = new QLabel(" Set the size of the board:", this);
    board_side_label_->setGeometry(0, 0, 250, 50);
    board_side_label_->setAlignment(Qt::AlignCenter);

    seed_label_ = new QLabel(" Enter seed here or leave empty:", this);
    seed_label_->setGeometry(0, 50, 250, 50);
    seed_label_->setAlignment(Qt::AlignCenter);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

/*
 * Palauttaa asetuksissa ilmenneen laudan sivun mitan.
 */
int OptionsWindow::return_bs()
{
    return bs_;
}

/*
 * Palauttaa asetuksissa ilmenneen siemenluvun.
 */
int OptionsWindow::return_seed()
{
    return seed_;
}

/*
 * Slotti asettaa pelilaudan sivun koon arvoksi spinboxin arvon aina
 * sitä muutettaessa.
 */
void OptionsWindow::set_bs()
{
    bs_ = board_side_box_->value();
}

/*
 * Slotti asettaa siemenluvun arvoksi QLineEditin arvon, mikäli se on
 * numero, muutoin siemenluvun arvona toimii käyttöjärjestelmän kellonaika.
 */
void OptionsWindow::set_seed()
{
    QString text = seed_edit_->text();
    bool digit = true;
    for (char i : text.toStdString()) {
        if (std::isdigit(i) == false) {
            digit = false;
        }
    }
    if (digit == true && text != "") {
        seed_ = text.toInt();
    } else {
        seed_ = time(NULL);
    }
}
