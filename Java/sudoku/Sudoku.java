import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Arrays;

public class Sudoku {

    // private
    private final HashMap<Integer, HashMap<Integer, String>> board = new HashMap<>();
    
    // public
    public Sudoku() {
        
        for (int y = 0; y < 9; y++) {
            HashMap<Integer, String> row = new HashMap<>();
            for (int x = 0; x < 9; x++) {
                row.put(x, " ");
            }
            this.board.put(y, row);
        }
    }
    
    public void set(int i, int j, char c) {
        
        ArrayList<String> accepted;
        accepted = new ArrayList<>(Arrays.asList(" ", "1", "2", "3", "4", "5",
                "6", "7", "8", "9"));
        
        if (i > 8 | j > 8) {
            System.out.format("Trying to access illegal cell (%d, %d)!\n", i, j);
        } else if (!accepted.contains(String.valueOf(c))) {
            System.out.print("Trying to set illegal character ");
            System.out.format("%s to (%d, %d)!\n", String.valueOf(c), i, j);
        } else {
            for (var row : this.board.get(i).keySet()) {
                if (row == j) {
                    this.board.get(i).put(j, String.valueOf(c));
                }
            }
        }
    }
    
    public boolean check() {
        
        int y = 0;
        int x = 0;
        int y_loc = 0;
        int x_loc = 0;
        int lowestduplicate = 10;
        boolean doubles = false;
        
        // Check rows
        while (y < 9) {
            HashSet<String> char_check = new HashSet<>();
            while (x < 9) {
                String duplicate = this.board.get(y).get(x);
                if (!" ".equals(duplicate)) {
                    if (!char_check.contains(duplicate)) {
                        char_check.add(duplicate);
                    } else {
                        doubles = true;
                        if (Integer.parseInt(duplicate) < lowestduplicate) {
                            lowestduplicate = Integer.parseInt(duplicate);
                            y_loc = y;
                        }
                    }
                }
                x++;
            }
            if (doubles == true) {
                System.out.format("Row %d has multiple %d's!\n", y_loc, lowestduplicate);
                return false;
            }
            x = 0;
            y++;
        }
        
        y = 0;
        x = 0;
        lowestduplicate = 10;
        
        // Check columns
        while (x < 9) {
            HashSet<String> char_check = new HashSet<>();
            while (y < 9) {
                String duplicate = this.board.get(y).get(x);
                if (!" ".equals(duplicate)) {
                    if (!char_check.contains(duplicate)) {
                        char_check.add(duplicate);
                    } else {
                        doubles = true;
                        if (Integer.parseInt(duplicate) < lowestduplicate) {
                            lowestduplicate = Integer.parseInt(duplicate);
                            x_loc = x;
                        }
                    }
                }
                y++;
            }
            if (doubles == true) {
                System.out.format("Column %d has multiple %d's!\n", x_loc, lowestduplicate);
                return false;
            }
            y = 0;
            x++;
        }

        y = 0;
        x = 0;
        y_loc = 0;
        x_loc = 0;
        lowestduplicate = 10;
        HashSet<String> char_check = new HashSet<>();
        
        // Check the blocks
        while (y < 9) {
            while (x < 9) {
                String duplicate = this.board.get(y).get(x);
                if (!" ".equals(duplicate)) {
                    if (!char_check.contains(duplicate)) {
                        char_check.add(duplicate);
                    } else {
                        doubles = true;
                        if (Integer.parseInt(duplicate) < lowestduplicate) {
                            lowestduplicate = Integer.parseInt(duplicate);
                            y_loc = y;
                            x_loc = x;
                        }
                    }
                }
                
                if ((y + 1) % 3 == 0 && (x + 1) % 3 == 0) {
                    char_check.clear();
                }
                
                if ((x + 1) % 3 != 0 && x != 8) {
                    x++;
                } else if ((x + 1) % 3 == 0 && (y + 1) % 3 != 0) {
                    x -= 2;
                    y++;
                } else if ((x + 1) % 3 == 0 && (y + 1) % 3 == 0 && x != 8) {
                    x++;
                    y -= 2;
                } else if (x == 8 && (y + 1) % 3 == 0 && y != 8) {
                    x -= 8;
                    y++;
                } else {
                    return true;
                }
                
                // Tehtävässä virhe, koordinaatit ilmoitetaan mallissa ristikkäin
                // muodossa (y, x). Tästä syystä outous seuraavassa pätkässä.
                if (doubles == true) {
                    int new_y_loc = y_loc - (y_loc % 3);
                    int new_x_loc = x_loc - (x_loc % 3);
                    System.out.format("Block at (%d, %d) has multiple %d's!\n", new_y_loc, new_x_loc, lowestduplicate);
                    return false;
                }
            }
        }
        
        // If no illegalities were found
        return true;
    }
    
    public void print() {
        
        int xctr = 0;
        
        int y = 0;
        int x = 0;
        
        while (y < 9) {
            if (y % 3 == 0) {
                System.out.println("#####################################");
                } else {
                    System.out.println("#---+---+---#---+---+---#---+---+---#");
                }
            while (x < 9) {
                if (xctr % 3 == 0) {
                System.out.print("#");
                } else {
                    System.out.print("|");
                }
                System.out.format("%2s ", this.board.get(y).get(x));
                if (x == 8) {
                    System.out.println("#");
                }
                x++;
                xctr++;
            }
            x = 0;
            y++;
        }
        
        System.out.println("#####################################");
    }
}
