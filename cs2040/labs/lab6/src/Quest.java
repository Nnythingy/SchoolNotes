import java.util.StringTokenizer;

public class Quest {
    private int energy; // energy cost of a quest
    private int gold; // gold reward from this quest

    public Quest(int e, int g) { // create new quest
        this.energy = e;
        this.gold = g;
    }

    public int getEnergy() { // get energy for this quest
        return energy;
    }

    public int getGold() { // get gold for this quest
        return gold;
    }
    @Override
    public String toString() {
        return "(" + energy + "," + gold + ")";
    }
}
