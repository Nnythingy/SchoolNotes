public class Team implements Comparable<Team> {
    private final int id;
    private int problems;
    private int penalties;

    public Team(int id) {
        this.id = id;
        this.problems = 0;
        this.penalties = 0;
    }
    public int getId() {
        return this.id;
    }

    public void updateScore(int p) { // for every input
        this.problems++;
        this.penalties += p;
    }
    @Override
    public int compareTo(Team other) { // compare to other team

        if (this.problems != other.problems) {
            return this.problems - other.problems;
        } else if (this.penalties != other.penalties) {
            return other.penalties - this.penalties;
        }
        return other.getId() - this.getId();
    }

    @Override
    public String toString() {
        return "Team: " + this.id + " Problems: " + this.problems + " Penalties: " + this.penalties;
    }
}
