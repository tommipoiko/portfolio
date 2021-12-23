#ifndef OPTIONSWINDOW_HH
#define OPTIONSWINDOW_HH

#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    OptionsWindow(QWidget *parent = nullptr);

    // Palauttaa asetusten arvot.
    int return_bs();
    int return_seed();

private slots:

    // Slotit, joita kutsutaan asetuslaatikoiden arvojen
    // muuttuessa.
    void set_bs();
    void set_seed();

private:

    // Osoittimet laatikoidin ja niitä esitteleviin QLabeleihin.
    QSpinBox *board_side_box_;
    QLineEdit *seed_edit_;
    QLabel *seed_label_;
    QLabel *board_side_label_;

    // Perus-attribuutit, joita muutetaan tarvittaessa.
    int bs_ = 6;
    int seed_ = time(NULL);
};
#endif // OPTIONSWINDOW_HH
