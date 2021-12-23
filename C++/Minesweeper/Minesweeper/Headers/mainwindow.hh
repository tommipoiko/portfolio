#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "square.hh"
#include "gameboard.hh"
#include "optionswindow.hh"
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>
#include <QMouseEvent>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Jokainen luokalla esiintyvä rakentaja.
    void init_square_buttons();
    void init_timer();
    void init_time_label();
    void init_start_button();
    void init_close_button();
    void init_options_button();
    void init_flag_or_check_browser();
    void init_description();

    // Oikean hiirenpainikkeen tunnistuksessa auttava
    // metodi.
    void mousePressEvent(QMouseEvent *e);

    // Pelin mahdollistavat metodit.
    void play_game(int x, int y);
    void change_button_text();
    std::string char_on_board(Square square);
    void clear_board();
    void new_board();
    void center();

private slots:

    // Käytössä olevat slotit.
    void set_time();
    void handle_click();
    void startSlot();
    void exitSlot();
    void optionsSlot();

private:
    Ui::MainWindow *ui;

    // Vektori vektoreista, jotka sisältävät pelilaudan
    // nappien osoittimet. Muodossa y-koord, x-koord = nappi.
    std::vector<std::vector<QPushButton*>> buttons_;

    // Pelissä esiintyvät osoittimet ja muistinvaraajat.
    QPushButton* pushButton;
    QPushButton* start_button_;
    QPushButton* close_button_;
    QPushButton* options_button_;
    QTimer *timer_;
    QLabel *time_label_;
    QTextBrowser *check_browser_;
    QTextBrowser *description_;
    GameBoard board;
    OptionsWindow *options_window_;

    // Koko vakio komponenteille, laudalle ja siemenluvulle.
    // Myöskin totuusarvoja asetuksille, lipun laitolle ja
    // pelaamisen statukselle.
    const int size_const = 64;
    int BOARD_SIDE = 6;
    bool options_showing_ = false;
    int time_ = 0;
    int seed_ = time(NULL);
    bool set_flag_ = false;
    bool playing_ = false;

};
#endif // MAINWINDOW_HH
