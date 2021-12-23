"""
This program is a simple version of the traditional game
battleship. The ship coordinates are entered via a csv-
file at the start of the program. After which the game asks
you to enter coordinates in the form of XY. To quit playing,
type q or Q as the command.
"""


class Ship:
    """
    This class represents the ships in the game.
    """
    def __init__(self, row):
        """
        :param row: Parameter is equal to a row of information
        from the csv-file. This row is then split accordingly
        into the name of the ship, the symbol for the ship,
        coordinates of the ship and then these coordinates are
        set to have a value representing the status: not hit.
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
        :param shot: Parameter is equal to the shot coordinates.
        These coordinates are then used to check the hit status.
        :return: The method returns different values depending
        on the status of the shot: In the case of a miss it
        returns 1, in the case of a hit it changes the hit-status
        -attribute to 1 to represent that it is hit and returns the
        value 2. If the same spot is shot again regardless of it
        being hit, the method returns 3.
        """
        if shot not in self.__coordinates:
            return 1

        elif shot in self.__coordinates:
            if self.__is_it_hit[shot] == 0:
                self.__is_it_hit[shot] = 1
                return 2
            else:
                return 3

        else:
            return 3

    def were_they_all_hit(self, shot):
        """
        :param shot: Parameter is equal to the shot coordinates.
        These coordinates are then used to check if the ship has been
        sunk.
        :return: If each coordinate of the ship is hit, the method re-
        turns 4 and if not all coordinates are hit, the method returns
        the value 2.
        """
        count = 0
        if shot in self.__coordinates:
            for coordinate in self.__coordinates:
                if self.__is_it_hit[coordinate] == 1:
                    count += 1

            if count == len(self.__is_it_hit):
                return 4

            else:
                return 2

    def get_coordinates(self, shot):
        """
        :param shot: Parameter is equal to the shot coordinates.
        :return: The method forms a list of the sunk ships
        coordinates. This is then returned.
        """
        list_of_coordinates = []
        if shot in self.__coordinates:
            for coordinate in self.__coordinates:
                list_of_coordinates.append(coordinate)

            return list_of_coordinates

    def check_for_win(self, coordinates):
        """
        :param coordinates: Parameter is an empty list that is
        then filled with all the ship coordinates.
        :return: The formed list.
        """
        for coord in self.__coordinates:
            coordinates.append(coord)

        return coordinates

    def get_fletter(self):
        """
        :return: Returns the first letter/the symbol of the ship.
        """
        return self.__fletter

    def get_name(self):
        """
        :return: Returns the name of the ship.
        """
        return self.__name


def read_file():
    """
    :return: After a successful reading of the csv-file the
    function returns a list of ship-objects and a value to
    tell the program to keep running. If there is an issue
    while reading the file, the function returns a value to
    tell the program to stop.
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
    :param row: A row in the file to be read. This is then
    dissected in to coordinates that are checked to see if they
    are valid.
    :return: If the coordinates are not proper the function
    returns the value True, which tells the calling function to
    quit running.
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
    :param row: A row of the read csv-file. The rows components
    are used to check for overlapping coordinates.
    :param list_of_coordinates: An empty list into which ship
    coordinates are added, if they do not already exist in it.
    :return: In the case of some overlapping the function returns
    the value True and in other cases the value False.
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
    :return: Returns the created 10x10-game-board. The board
    exists in the form of a x-dict in a y-dict.
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
    :param board: Parameter is the board in its current state.
    It is then used to print the components of the board.
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
    :param list_of_ships: A list of the ship-objects.
    :param shot: The coordinates of the shot.
    :param board: The game-board into which the result of the
    shot is then entered.
    :return: Returns the game-board back to the main loop and in
    the case of continuation the value 1 and when the game should
    end the return value is 0.
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
    :param list_of_ships: A list of the ship-objects.
    :param board: The game-board into which the result of the
    shot is then entered.
    :return: When the function finds the case in which the game
    is won, it returns the value True and in the case of continuation
    it returns the value False.
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
    :param list_of_ships: A list of the ship-objects.
    :param shot: The coordinates of the shot.
    :param board: The game-board into which the result of the
    shot is then entered.
    :return: if the function detects that all of a ships coordinates
    are hit then instead of showing X on teh board, the ships coordinates
    are filled with the ships symbol.
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
    :param list_of_ships: A list of the ship-objects.
    :param board: The game-board into which the result of the
    shot is then entered.
    :return: Returns, depending on the situation, a value rep-
    resenting the continuation, which is 1 or a value telling the
    game to stop, which is 0.
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
