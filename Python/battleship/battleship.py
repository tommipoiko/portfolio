"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Tommi Poikolainen
050093232
tommi.poikolainen@tuni.fi

Ohjelma vastaa laivanupotuspeliä kaikessa kompleksisuudessaan.
"""


class Ship:
    """
    Luokka, jolla kuvataan laivoja.
    """
    def __init__(self, row):
        """
        :param row: Kuvaa kaiken tiedon tekstitiedoston
        riviltä. Tästä jalostetaan olioon tämän attribuutteja.
        """
        items = row.split(";")
        items[-1] = items[-1].strip()
        self.__name = items[0]
        self.__fletter = items[0][0].upper()
        self.__coordinates = dict()
        self.__is_it_hit = dict()

        for coordinate in items[1:]:
            self.__coordinates[coordinate] = self.__fletter
            self.__is_it_hit[coordinate] = 0

    def did_it_hit(self, shot):
        """
        :param shot: Muuttuja kuvaa ammunnan koordinaatteja.
        Tätä käytetään mahdollisen osuman tarkistamiseen.
        :return: Metodi palauttaa osuman laadusta riippuen eri
        arvoja: Hutiosuman kohdalla arvon 1, (ensimmäisen)
        osuman kohdalla arvon 2 ja toistuvissa ammunnoissa
        arvon 3.
        """
        if shot not in self.__coordinates:
            return 1

        elif shot in self.__coordinates:
            if self.__is_it_hit[shot] == 0:
                self.__is_it_hit[shot] = 2
                return 2
            else:
                return 3

        else:
            return 3

    def were_they_all_hit(self, shot):
        """
        :param shot: Muuttuja kuvaa ammunnan koordinaatteja.
        Tämä on käytössä metodissa laivan upotuksen tarkistamiseen.
        :return: Mikäli laivan jokainen koordinaatti on pommitettuna,
        metodi palauttaa arvon 4 ja muussa tapauksessa ammunnat
        jatkuvan normaaliin tahtiin ja palautetaan arvo 2.
        """
        count = 0
        if shot in self.__coordinates:
            for coordinate in self.__coordinates:
                if self.__is_it_hit[coordinate] == 2:
                    count += 1

            if count == len(self.__is_it_hit):
                return 4

            else:
                return 2

    def get_coordinates(self, shot):
        """
        :param shot: Muuttuja kuvaa ammunnan koordinaatteja.
        :return: Metodilla muodostetaan lista osutun laivan
        muistakin koordinaateista. Tämä palautetaan.
        """
        list_of_coordinates = []
        if shot in self.__coordinates:
            for coordinate in self.__coordinates:
                list_of_coordinates.append(coordinate)

            return list_of_coordinates

    def check_for_win(self, coordinates):
        """
        :param coordinates: Kuvaa tyhjää listaa, johon täytetään
        kaikkien laivojen koordinaatit.
        :return: Palauttaa kyseisen listan.
        """
        for coord in self.__coordinates:
            coordinates.append(coord)

        return coordinates

    def get_fletter(self):
        """
        :return: Palauttaa laivan nimen ensimmäisen kirjaimen.
        """
        return self.__fletter

    def get_name(self):
        """
        :return: Palauttaa laivan nimen.
        """
        return self.__name


def read_file():
    """
    :return: Onnistuneen tiedoston lukemisen jälkeen funktio
    palauttaa listan laiva-olioista ja sovelluksen jatkamista
    kuvaavan arvon. Tiedoston lukemisessa esiintyessä virhe,
    palautetaankin sovelluksen lopettamista kuvaava arvo.
    """
    filename = input("Enter file name: ")
    try:
        file = open(filename, mode="r")
        list_of_ships = []
        list_of_coordinates = []
        for row in file:
            if are_there_similarities(row, list_of_coordinates):
                print("There are overlapping ships in the input file!")
                dont_quit = 0
                return None, dont_quit

            if range_of_coordinates(row):
                print("Error in ship coordinates!")
                dont_quit = 0
                return None, dont_quit

            name = Ship(row)
            list_of_ships.append(name)

        dont_quit = 1
        return list_of_ships, dont_quit

    except IOError:
        print("File can not be read!")
        dont_quit = 0
        return None, dont_quit


def range_of_coordinates(row):
    """
    :param row: Luettavan tiedoston rivi, jonka komponentteja
    tarkastellaan sopivien koordinaattien löytämiseksi.
    :return: Palauttaa virhetilanteessa arvon True, joka kuvaa
    "emo"-ohjelmassa sovelluksen lopettamisen tarvetta.
    """
    items = row.split(";")
    items[-1] = items[-1].strip()
    for component in items[1:]:
        X = component[0]
        Y = int(component[1:])
        if X not in ["a", "A", "b", "B", "c", "C", "d", "D", "e", "E",
                     "f", "F", "g", "G", "h", "H", "i", "I", "j", "J"]:
            return True

        elif Y not in range(0, 10):
            return True


def are_there_similarities(row, list_of_coordinates):
    """
    :param row: Luettavan tiedoston rivi, jonka komponentteja
    tarkastellaan päällekkäisten koordinaattien löytymiseksi.
    :param list_of_coordinates: Tyhjä lista, mihin täytetään
    laiva-olioiden koordinaatteja, mikäli sellaista ei vielä
    listasta löydy.
    :return: Palauttaa päällekkäisyyden tapauksessa sovelluksen
    lopettamista kuvaavan True-arvon ja muulloin sovelluksen
    jatkamista kuvaavan False-arvon.
    """
    items = row.split(";")
    items[-1] = items[-1].strip()
    for component in items[1:]:
        if component in list_of_coordinates:
            return True

        else:
            list_of_coordinates.append(component)
            return False


def create_board():
    """
    :return: Palauttaa luodun 10x10-pelilaudan, joka esiintyy
    muodossa sanakirja sanakirjassa.
    """
    board = dict()
    board["A"] = dict()
    for num in range(0, 10):
        board["A"][num] = " "
    board["B"] = dict()
    for num in range(0, 10):
        board["B"][num] = " "
    board["C"] = dict()
    for num in range(0, 10):
        board["C"][num] = " "
    board["D"] = dict()
    for num in range(0, 10):
        board["D"][num] = " "
    board["E"] = dict()
    for num in range(0, 10):
        board["E"][num] = " "
    board["F"] = dict()
    for num in range(0, 10):
        board["F"][num] = " "
    board["G"] = dict()
    for num in range(0, 10):
        board["G"][num] = " "
    board["H"] = dict()
    for num in range(0, 10):
        board["H"][num] = " "
    board["I"] = dict()
    for num in range(0, 10):
        board["I"][num] = " "
    board["J"] = dict()
    for num in range(0, 10):
        board["J"][num] = " "
    return board


def print_board(board):
    """
    :param board: Pelilauta nykytilassa, jota käytetään
    tilanteen esittämiseen tulostuksen muodossa.
    """
    print("")
    print("  A B C D E F G H I J")
    for round in range(0, 10):
        print(round, board["A"][round], board["B"][round], board["C"][round],
              board["D"][round], board["E"][round], board["F"][round],
              board["G"][round], board["H"][round], board["I"][round],
              board["J"][round], round)

    print("  A B C D E F G H I J")


def hit(list_of_ships, shot, board):
    """
    :param list_of_ships: Lista laiva-olioista.
    :param shot: Ammunnan kohdekoordinaatit.
    :param board: Pelilauta, johon kirjataan osumien laadut.
    :return: Palauttaa pääohjelmaan pelilautaa sen
    uusintakäsittelyä varten ja onnistuneissa sekvensseissä
    pelin jatkamista kuvaavaa arvoa 1 ja päättymistilanteessa
    pelin lopettamista kuvaavan arvon 0.
    """
    X = str(shot[0].upper())
    Y = int(shot[1])
    for ship in list_of_ships:
        hitmod = ship.did_it_hit(shot)
        if hitmod == 2:
            hitmod = ship.were_they_all_hit(shot)
            break

    if hitmod == 1:
        if board[X][Y] == " ":
            board[X][Y] = "*"

        else:
            print("Location has already been shot at!")

    elif hitmod == 2:
        board[X][Y] = "X"

    elif hitmod == 4:
        board = show_fletter(list_of_ships, shot, board)
        if won_the_game(list_of_ships, board):
            print_board(board)
            print("")
            print("Congratulations! You sank all enemy ships.")
            return board, 0

    else:
        print("Location has already been shot at!")

    return board, 1


def won_the_game(list_of_ships, board):
    """
    :param list_of_ships: Lista pelin laiva-olioista.
    :param board: Pelilauta sen nykyisessä tilassaan.
    :return: Funktion löytäessä tilanteen, jossa jokainen
    laiva on upotettu, se palauttaa voittamista kuvaavan
    True-arvon ja muutoin pelin jatkamista kuvaavan False-
    arvon.
    """
    coordinates = []
    for ship in list_of_ships:
        coordinates = ship.check_for_win(coordinates)

    goal = len(coordinates)
    checked = 0
    list_of_symbols = [" ", "*", "X"]
    for coord in coordinates:
        X = str(coord[0])
        Y = int(coord[1:])
        if board[X][Y] not in list_of_symbols:
            checked += 1

    if checked == goal:
        return True

    else:
        return False


def show_fletter(list_of_ships, shot, board):
    """
    :param list_of_ships: Lista olemassaolevista laiva-olioista.
    :param shot: Osuman koordinaatit.
    :param board: Pelilauta sen nykyisessä tilassaan.
    :return: Mikäli funktio huomaa yhden laivan jokaiseen
    koordinaattiin osuttaneen, funktio kirjoittaa lautaan tämän
    koordinaatteihin tämän laivan tunnuksen.
    """
    for ship in list_of_ships:
        if ship.get_coordinates(shot) is not None:
            list_of_coordinates = ship.get_coordinates(shot)
            fletter = ship.get_fletter()
            name = ship.get_name()

            if board[shot[0].upper()][int(shot[1])] != fletter:
                for coordinate in list_of_coordinates:
                    X = coordinate[0].upper()
                    Y = int(coordinate[1])
                    board[X][Y] = fletter

                print(f"You sank a {name}!")

            else:
                print("Location has already been shot at!")

            return board


def command(list_of_ships, board):
    """
    :param list_of_ships: Lista laiva-olioista.
    :param board: Pelilauta sen nykyisessä tilassaan.
    :return: Palauttaa, riippuen tilanteesta, pelin jatkamista
    kuvaavan arvon 1 tai pelin päättämistä kuvaavan arvon 0.
    """
    print("")
    list_of_X = ["a", "A", "b", "B", "c", "C", "d", "D", "e", "E",
                 "f", "F", "g", "G", "h", "H", "i", "I", "j", "J"]
    shot = input("Enter place to shoot (q to quit): ")
    if shot == "q" or shot == "Q":
        print("Aborting game!")
        return board, 0

    elif len(shot) > 2 or len(shot) < 2:
        print("Invalid command!")
        return board, 1

    elif str(shot[0]) not in list_of_X or int(shot[1]) not in range(0, 10):
        print("Invalid command!")
        return board, 1

    else:
        X = shot[0].upper()
        Y = shot[1]
        shot = X + Y
        board, dont_quit = hit(list_of_ships, shot, board)
        return board, dont_quit


def main():
    board = create_board()
    list_of_ships, dont_quit = read_file()
    if dont_quit == 1:
        print_board(board)

    while dont_quit == 1:
        board, dont_quit = command(list_of_ships, board)
        if dont_quit == 1:
            print_board(board)


if __name__ == "__main__":
    main()
