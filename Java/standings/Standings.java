import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Standings {

    // Private
    private final ArrayList<Team> list_of_teams = new ArrayList<>();
    
    private void reorderStandings() {
        
        //
        
        ArrayList<Team> temporary = new ArrayList<>(this.list_of_teams);
        this.list_of_teams.clear();
        
        while (!temporary.isEmpty()) {
            Team bestTeam = null;
            int highestPoints = -1;
            
            for (Team team : temporary) {
                if (team.getPoints() > highestPoints) {
                    bestTeam = team;
                    highestPoints = team.getPoints();
                } else if (team.getPoints() == highestPoints) {
                    int goalDifferenceA = bestTeam.getScored() - bestTeam.getAllowed();
                    int goalDifferenceB = team.getScored() - team.getAllowed();
                    if (goalDifferenceA < goalDifferenceB) {
                        bestTeam = team;
                    } else if (goalDifferenceA == goalDifferenceB) {
                        if (bestTeam.getScored() < team.getScored()) {
                            bestTeam = team;
                        } else if (bestTeam.getScored() == team.getScored()) {
                            if (bestTeam.getName().compareTo(team.getName()) > 0) {
                                bestTeam = team;
                            }
                        }
                    }
                }
            }
            
            this.list_of_teams.add(bestTeam);
            temporary.remove(bestTeam);
        }
    }
    
    private void addTeamToList(Team team) {
        
        //
        
        this.list_of_teams.add(team);
    }
    
    // Public
    public class Team {
        
        // Private
        private final String team_name;
        private int team_wins = 0;
        private int team_ties = 0;
        private int team_losses = 0;
        private int team_scoredgoals;
        private int team_allowedgoals;
        private int team_points;
        
        // Public
        public Team(String name) {
            this.team_name = name;
        }
        
        public String getName() {
            
            // Returns the name of the team;
            
            return this.team_name;
        }
        
        public int getWins() {
            
            // Returns the amount of wins a team has
            
            return this.team_wins;
        }
        
        public int getTies() {
            
            // Returns the amount of ties a team has
            
            return this.team_ties;
        }
        
        public int getLosses() {
            
            // Returns the amount of losses a team has
            
            return this.team_losses;
        }
        
        public int getScored() {
            
            // Returns the amount of scored goals a team has
            
            return this.team_scoredgoals;
        }
        
        public int getAllowed() {
            
            // Returns the amount of allowed goals a team has
            
            return this.team_allowedgoals;
        }
        
        public int getPoints() {
            
            // Returns the amount of ladder points a team has
            
            return this.team_points;
        }
    }
    
    public Standings() {
        
        //
    }
    
    public Standings(String filename) throws IOException {
        
        //
        
        try(var file = new BufferedReader(new FileReader(filename))) {
            String row = null;
            while((row = file.readLine()) != null) {
                String[] file_row = row.split("\\t");
                String nameA = file_row[0];
                String nameB = file_row[2];
                String game_score = file_row[1];
                int scoreA = Integer.parseInt(game_score.split("-")[0]);
                int scoreB = Integer.parseInt(game_score.split("-")[1]);
                
                addMatchResult(nameA, scoreA, scoreB, nameB);
            }
        }
    }
    
    public void readMatchData(String filename) throws IOException {
        
        //
        
        try(var file = new BufferedReader(new FileReader(filename))) {
            String row = null;
            while((row = file.readLine()) != null) {
                String[] file_row = row.split("\\t");
                String nameA = file_row[0];
                String nameB = file_row[2];
                String game_score = file_row[1];
                int scoreA = Integer.parseInt(game_score.split("-")[0]);
                int scoreB = Integer.parseInt(game_score.split("-")[1]);
                
                addMatchResult(nameA, scoreA, scoreB, nameB);
            }
        }
    }
    
    public void addMatchResult(String teamNameA, int goalsA,
            int goalsB, String teamNameB) {
        
        //
        
        boolean teamA_found = false;
        boolean teamB_found = false;
        int winner;
        
        if (goalsA > goalsB) {
            winner = 1;
        } else if (goalsA < goalsB) {
            winner = 2;
        } else {
            winner = 3;
        }
        
        for (Team team : this.getTeams()) {
            if (team.getName().equals(teamNameA)) {
                teamA_found = true;
                team.team_scoredgoals += goalsA;
                team.team_allowedgoals += goalsB;
                
                if (winner == 1) {
                    // A wins
                    team.team_wins += 1;
                    team.team_points += 3;
                } else if (winner == 2) {
                    // B wins
                    team.team_losses += 1;
                } else {
                    // Tie
                    team.team_ties += 1;
                    team.team_points += 1;
                }
            }
            if (team.getName().equals(teamNameB)) {
                teamB_found = true;
                team.team_scoredgoals += goalsB;
                team.team_allowedgoals += goalsA;
                
                if (winner == 1) {
                    // A wins
                    team.team_losses += 1;
                } else if (winner == 2) {
                    // B wins
                    team.team_wins += 1;
                    team.team_points += 3;
                } else {
                    // Tie
                    team.team_ties += 1;
                    team.team_points += 1;
                }
            }
        }
        
        if (teamA_found == false) {
            Team teamA = new Team(teamNameA);
            addTeamToList(teamA);
            teamA.team_scoredgoals = goalsA;
            teamA.team_allowedgoals = goalsB;
            
            if (winner == 1) {
                // A wins
                teamA.team_wins += 1;
                teamA.team_points += 3;
            } else if (winner == 2) {
                // B wins
                teamA.team_losses += 1;
            } else {
                // Tie
                teamA.team_ties += 1;
                teamA.team_points += 1;
            }
        }
        if (teamB_found == false) {
            Team teamB = new Team(teamNameB);
            addTeamToList(teamB);
            teamB.team_scoredgoals = goalsB;
            teamB.team_allowedgoals = goalsA;
            
            if (winner == 1) {
                // A wins
                teamB.team_losses += 1;
            } else if (winner == 2) {
                // B wins
                teamB.team_wins += 1;
                teamB.team_points += 3;
            } else {
                // Tie
                teamB.team_ties += 1;
                teamB.team_points += 1;
            }
        }
        
        this.reorderStandings();
    }
    
    public ArrayList<Team> getTeams() {
        
        //
        
        return this.list_of_teams;
    }
    
    public void printStandings() {
        
        //
        
        this.reorderStandings();
        
        int nameSpace = 0;
        
        for (Team team : this.getTeams()) {
            if (team.getName().length() > nameSpace) {
                nameSpace = team.getName().length();
            }
        }
        
        for (Team team : this.getTeams()) {
            String name = team.getName();
            System.out.print(name);
            
            int spaces = nameSpace - name.length();
            for (int i = 0; i < spaces; i++) {
                System.out.print(" ");
            }
            
            String goalsAB = "";
            goalsAB += team.getScored() + "-" + team.getAllowed();
            
            System.out.format(" %3d ", team.getWins() + team.getLosses() + team.getTies());
            System.out.format("%3d ", team.getWins());
            System.out.format("%3d ", team.getTies());
            System.out.format("%3d ", team.getLosses());
            System.out.format("%6s ", goalsAB);
            System.out.format("%3d\n", team.getPoints());
        }
    }
}
