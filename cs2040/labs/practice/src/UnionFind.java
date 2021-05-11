import javax.print.DocFlavor;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;

class UnionFind {
    public ArrayList<Integer> p;
    public ArrayList<Integer> rank;
    public HashMap<Integer, String> names;
    public ArrayList<Integer> friends;


    public UnionFind(int n) {
        p = new ArrayList<Integer>(); // array initial parent nos
        rank = new ArrayList<Integer>(); // array of ranks
        friends = new ArrayList<Integer>();
        names = new HashMap<>();
        q
    }

    public void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i);
            int y = findSet(j);

            if (rank[x] > rank[y]) {
                p[y] = x;
            } else {
                p[x] = y;

                if (rank[x] == rank[y]) { // if they are the same rank sets, y, becomes higher
                    rank[y]++;
                }
            }
        }
    }
    // returns parent node of the set containing i
    public int findSet(int i) {
        if (p[i] == i) {
            return i;
        } else {
            p[i] = findSet(p[i]);
            return p[i];
        }
    }
    // check if the 2 are in the same set
    public boolean isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

}