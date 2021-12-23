#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "square.hh"
#include "gameboard.hh"
#include "optionswindow.hh"

/*
 * COMP.CS.110 Ohjelmointi 2: Syksy 2021
 * Projekti 4: Miinaharava
 * Nimi: Tommi Poikolainen
 * Email: tommi.poikolainen@tuni.fi
 * Projektissa luodaan miinaharava-peli. Pelissä on mahdollista säätää
 * sekä pelilaudan kokoa, että siemenlukua. Ohjelmassa on käytössä suh-
 * teellisen perinteinen control scheme, kuin aidoissa  miinaharavois-
 * sa, mutta oikealla napilla lipun asettamisen sijaan vaihetaan moodia
 * lipun asettamisen ja ruudun avaamisen välillä. Peliä pelatessa näk-
 * yy pelin pelaamisen kulunut aika sekunteina.
 * Asetuksiin pääsee options-nappia painamalla, pelin voi aloittaa
 * start/reset-napista ja pelin saa suljettua quit-napista.
 */

/*
 * Metodi toimii pääaikkunan rakentajana ja käytännössä myös kaikkien
 * muidenkin UI-komponenttien rakentajana. Rakentajassa myös esitel-
 * lään OptionsWindow-ikkunaluokka. Pääikkuna asetetaan suhteellisen
 * keskelle ruudulle ja ikkunasta piilotetaan default-napit, kuten
 * käyttöjärjestelmän tarjoamat exit, minimize ja maximize -napit.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    options_window_ = new OptionsWindow();
    options_window_->setAttribute(Qt::WA_QuitOnClose, false);
    options_window_->move(screen()->geometry().center() - frameGeometry().center());
    options_window_->hide();

    init_square_buttons();
    init_timer();
    init_time_label();
    init_start_button();
    init_close_button();
    init_options_button();
    init_flag_or_check_browser();
    init_description();

    center();

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

/*
 * Metodi toimii pääikkunan ja siten myös koko UI:n purkajana.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * init_square_buttons() luo pelin miinakentän käsittelyssä
 * toimivan nappikentän. Jokainen nappi asetetaan setGeomet-
 * ryllä vakiotavoin muuttuvaan paikkaan, aina size_const-
 * vakion määräämän kokoisina. Napeista muodostetaan vektori
 * vektoriin, jolloin koordinaattien vertaaminen gameboard.cpp
 * tarjoamaan lautaan on helppoa.
 */
void MainWindow::init_square_buttons()
{
    QWidget* central = new QWidget(this);

    QBrush brush(Qt::gray);
    QPalette palette;
    palette.setBrush(QPalette::Button, brush);
    int ctr = 0;
    int y_place = 2;
    int row = 0;

    std::vector<QPushButton*> x_buttons;

    while (row < BOARD_SIDE)
    {
        pushButton = new QPushButton(this);
        pushButton->setPalette(palette);

        x_buttons.push_back(pushButton);
        pushButton->setMinimumSize(size_const, size_const);
        pushButton->setGeometry(ctr * (size_const),
                                y_place * (size_const),
                                size_const,
                                size_const);


        connect(pushButton, &QPushButton::clicked,
                this, &MainWindow::handle_click);
        pushButton->show();

        ++ctr;
        if (ctr == BOARD_SIDE) {
            ctr = 0;
            ++row;
            ++y_place;
            buttons_.push_back(x_buttons);
            x_buttons.clear();
        }
    }

    setCentralWidget(central);
    return;
}

/*
 * Metodilla luodaan QTimer-luokan ajastin. Tämä lähettää sekunnin
 * välein signaalin, jolla päästään käsittelemään set_time()-slot-
 * tia.
 */
void MainWindow::init_timer()
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, SIGNAL(timeout()), this, SLOT(set_time()), Qt::DirectConnection);
}

/*
 * Alustetaan ajan esitykseen käytetty QLabel. Siistin ulkoasun
 * vuoksi en käytä projektissa mitään lcd-number tyylisiä wid-
 * gettejä.
 */
void MainWindow::init_time_label()
{
    time_label_ = new QLabel(this);
    time_label_->setText(QString::number(time_));
    time_label_->setGeometry(2 * (size_const),
                             1 * (size_const),
                             2 * size_const,
                             size_const);
    time_label_->setAlignment(Qt::AlignCenter);
    time_label_->show();
}

/*
 * init_start_button()-metodi luo pelissä esiintyvän start/
 * reset-napin, jolla voi käynnistää pelin joko alussa tai
 * kesken kaiken uusiksi. Nappi yhdistetään painallusta vas-
 * taan startSlot()-slottiin.
 */
void MainWindow::init_start_button()
{
    QBrush brush(Qt::green);
    QPalette palette;
    palette.setBrush(QPalette::Button, brush);

    start_button_ = new QPushButton("Start/Reset", this);

    start_button_->setFixedWidth(2 * size_const);
    start_button_->setPalette(palette);

    start_button_->setGeometry(4 * (size_const),
                               1 * (size_const),
                               2 * size_const,
                               size_const);

    start_button_->show();
    connect(start_button_, SIGNAL(clicked()), this, SLOT(startSlot()));
}

/*
 * Metodi luo Quit-napin, joka itsessään sulkee koko sovel-
 * luksen.
 */
void MainWindow::init_close_button()
{
    QBrush brush(Qt::red);
    QPalette palette;
    palette.setBrush(QPalette::Button, brush);

    close_button_ = new QPushButton("Quit", this);

    close_button_->setFixedWidth(2 * size_const);
    close_button_->setPalette(palette);

    close_button_->setGeometry(0 * (size_const),
                               1 * (size_const),
                               2 * size_const,
                               size_const);

    close_button_->show();
    connect(close_button_, SIGNAL(clicked()), this, SLOT(exitSlot()));
}

/*
 * Metodi luo options-napin, joka avaa uuden ikkunan ase-
 * tuksien asettamiselle optionsSlot()-slotilla. OptionsWin-
 * dow-ikkuna on esitelty rakentajassa.
 */
void MainWindow::init_options_button()
{
    options_button_ = new QPushButton("Options", this);

    options_button_->setGeometry(0 * (size_const),
                                 0 * (size_const),
                                 2 * size_const,
                                 size_const);

    options_button_->show();
    connect(options_button_, SIGNAL(clicked()), this, SLOT(optionsSlot()));
}

/*
 * Metodilla luodaan QTextBrowser, joka kertoo, että ol-
 * laanko asettamassa lippua vai avaamassa pelikentän ruu-
 * tua.
 */
void MainWindow::init_flag_or_check_browser()
{
    check_browser_ = new QTextBrowser(this);
    check_browser_->setText("Checking for mines");
    check_browser_->setGeometry(4 * (size_const),
                                0 * (size_const),
                                2 * size_const,
                                size_const);

    check_browser_->setStyleSheet("border: 2px black; text-align: center;");
    check_browser_->show();
}

/*
 * Metodi luo tekstiboksin, missä ilmoitetaan pelissä ta-
 * pahtuvista asioista, kuten voittamisesta, häviämisestä
 * ja pelin pelaamisen aloittamisesta.
 */
void MainWindow::init_description()
{
    description_ = new QTextBrowser(this);
    description_->setText("Start the game by pressing the Start/Reset -button.");
    description_->setGeometry(1 * (size_const),
                              (BOARD_SIDE+2) * (size_const),
                              4 * size_const,
                              1.5 * size_const);

    description_->setStyleSheet("border: 2px black; text-align: center;");
    description_->show();
}

/*
 * Metodi tunnistaa oikean hiirenpainikkeen käyttämisen ja
 * suorittaa asianmukaisen muutoksen peliympäristössä, eli
 * vaihtaa moodia lipun asetuksesta peliruudun tarkistukseen.
 */
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        if (set_flag_ == true) {
            set_flag_ = false;
            check_browser_->setText("Checking for mines");
        } else{
            set_flag_ = true;
            check_browser_->setText("Setting a flag");
        }
    }
}

/*
 * Metodi play_game() suorittaa pelin pelaamista. Alussa
 * otetaan tarkasteluun ruutu square ja tätä lähdetään sit-
 * ten purkamaan. Pommiin osuessa peli päättyy ja teksti-
 * kentän viesti muutetaan vastaavaksi. Loppupuolella tar-
 * kistetaan voiton ehto ja tarvittaessa kerrotaan teksti-
 * kentässä voitosta.
 */
void MainWindow::play_game(int x, int y)
{
    Square square = board.getSquare(x - 1, y - 1);
    if(square.hasFlag())
    {
        if(set_flag_ == true)
        {
            square.removeFlag();
        }
    }
    else if(set_flag_ == false)
    {
        if(not square.open())
        {
            change_button_text();
            playing_ = false;
            timer_->stop();
            description_->setText("You hit a bomb! Game over! Start a new game by pressing the Start/Reset -button.");
        }
    }
    else
    {
        square.addFlag();
    }

    board.setSquare(square, x - 1, y - 1);
    change_button_text();
    if (board.isGameOver()) {
        playing_ = false;
        timer_->stop();
        description_->setText("You won! You have cleared every bomb on the field! Start a new game by pressing the Start/Reset -button.");
    }
}

/*
 * Metodia kutsutaan play_game()-metodista ja tämän meto-
 * din tarkoituksena onkin siis muuttaa pelilauta oikean-
 * näköiseksi numeroiden ja ikonien kannalta. Grafiikan
 * asettelu suoritetaan vertaamalla gameboardin merkkejä
 * nappilautaan ja korjaamalla nappilaudan nappeihin oi-
 * keat havainnollistukset tarvittaessa.
 */
void MainWindow::change_button_text()
{
    for(int y = 0; y < BOARD_SIDE; ++y) {
        for(int x = 0; x < BOARD_SIDE; ++x) {
            Square square = board.getSquare(x, y);
            std::string flag;
            flag += FLAG;
            std::string mine;
            mine += MINE;
            if (char_on_board(square) == flag) {
                QPixmap image(":/flag.png");
                image = image.scaled(size_const, size_const);
                buttons_.at(y).at(x)->setIcon(image);
            } else if (char_on_board(square) == mine) {
                QPixmap image(":/bomb.png");
                image = image.scaled(size_const, size_const);
                buttons_.at(y).at(x)->setIcon(image);
            } else {
                buttons_.at(y).at(x)->setIcon(QIcon());
                buttons_.at(y).at(x)->setText(QString::fromStdString(char_on_board(square)));
            }
        }
    }
}

/*
 * Tätäkin metodia kutsutaan edellisellä metodilla. Meto-
 * din tarkoituksena on palauttaa change_button_text()-me-
 * todille verrattava ruudun merkki.
 */
std::string MainWindow::char_on_board(Square square)
{
    std::string to_go = "";
    if(square.hasFlag())
    {
        to_go = FLAG;
        return to_go;
    }
    else if(not square.isOpen())
    {
        to_go = "";
        return to_go;
    }
    else if(square.hasMine())
    {
        to_go = MINE;
        return to_go;
    }
    else
    {
        to_go = std::to_string(square.returnAdjacent());
        return to_go;
    }
}

/*
 * Metodi tuhoaa kaiken pelilaudasta.
 */
void MainWindow::clear_board()
{
    board.destroy_board();
    for(auto y : buttons_) {
        for(auto& x : y) {
            delete x;
        }
        y.clear();
    }
    buttons_.clear();
    delete start_button_;
    delete close_button_;
    delete options_button_;
    delete timer_;
    delete time_label_;
    delete check_browser_;
    delete description_;
}

/*
 * Tällä metodilla luodaan aiemmin tuhotut komponentin
 * mahdollisten uusien asetusarvojen perusteella.
 */
void MainWindow::new_board()
{
    init_square_buttons();
    init_timer();
    init_time_label();
    init_start_button();
    init_close_button();
    init_options_button();
    init_flag_or_check_browser();
    init_description();
    center();
    center();
    description_->setGeometry(1 * (size_const),
                              (BOARD_SIDE+2) * (size_const),
                              4 * size_const,
                              1.5 * size_const);
    description_->setText("Start the game by pressing the Start/Reset -button.");
}

/*
 * Metodi center() keskittää pääikkunan siltä varalta, että
 * pelilaudan kokoa on muutettu.
 */
void MainWindow::center()
{
    resize((BOARD_SIDE)*size_const, (BOARD_SIDE+4)*size_const);
    //hide();
    //show();
    move(screen()->geometry().center() - frameGeometry().center());
}

/*
 * Ajastimen kutsuma slotti, jossa kelloon lisätään sekunti.
 */
void MainWindow::set_time()
{
    ++time_;
    time_label_->setText(QString::number(time_));
}

/*
 * Slotilla handle_click() muokataan napin asetetut koordinaatit
 * pelilaudassa hyödynnettävään muotoon. Sitten siirretään peliin
 * play_game-metodilla.
 */
void MainWindow::handle_click()
{
    if (playing_ == true) {
        for (auto& x_button : buttons_) {
            for (auto& button : x_button) {
                if (button == sender()) {
                    int x = button->x();
                    int x_on_grid = (x+size_const)/size_const;
                    int y = button->y();
                    int y_on_grid = (y-size_const)/size_const;
                    play_game(x_on_grid, y_on_grid);
                }
            }
        }
    }
}

/*
 * Slotilla aloitetaan peli uusiksi. Tässä tuhotaan lauta,
 * luodaan se uusiksi ja asetetaan attribuutit vastaamaan ti-
 * lannetta.
 */
void MainWindow::startSlot()
{
    clear_board();
    BOARD_SIDE = options_window_->return_bs();
    seed_ = options_window_->return_seed();
    board.init(seed_, BOARD_SIDE);
    new_board();
    description_->setText("Intensely playing the game...");
    playing_ = true;
    time_ = 0;
    time_label_->setText(QString::number(time_));
    timer_->start(1000);
    if (options_showing_ == true) {
        options_window_->hide();
        options_showing_ = false;
    }
}

/*
 * Slot toimii sovelluksen sulkijana ja poistaa kaiken ohjel-
 * massa luodun, ennen pääikkunan sulkemista.
 */
void MainWindow::exitSlot()
{
    clear_board();
    delete options_window_;
    this->close();
}

/*
 * optionsSlot() avaa tai sulkee OptionsWindow-ikkunan,
 * riippuen siitä, onko se jo auki tai kiinni.
 */
void MainWindow::optionsSlot()
{
    if (options_showing_ == false) {
        options_window_->show();
        options_showing_ = true;
    } else if (options_showing_ == true) {
        options_window_->hide();
        options_showing_ = false;
    }
}
