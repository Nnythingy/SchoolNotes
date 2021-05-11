class UnionFind {
    public int[] p;
    public int[] rank;
    public int[] filled;
    public int[] total;

    public UnionFind(int n) {
        p = new int[n+1]; // array initial parent nos
        rank = new int[n+1]; // array of ranks
        filled = new int[n+1]; // array of no of filled drawers in each set
        total = new int[n+1]; // array of total drawers in each set

        for (int i = 0; i < n + 1; i++) {
            p[i] = i; // array of initial parent nos
            rank[i] = 0; // no ranks initially
            filled[i] = 0; // every drawer is initially empty
            total[i] = 1; // each set of 1 drawer has initially one drawer

        }
    }

    public void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i);
            int y = findSet(j);

            if (rank[x] > rank[y]) {
                p[y] = x;
                filled[x] += filled[y]; // combine no of filled and total drawers
                total[x] += total[y];
            } else {
                p[x] = y;
                filled[y] += filled[x]; // combine total
                total[y] += total[x];
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

    // checks if an object placed in drawer n can be filled using the rules
    public boolean canFill(int n) {
        int setNo = findSet(n); // finds the representive no in the set containing n

        if (filled[setNo] + 1 <= total[setNo]) { // check
            filled[setNo]++; // add a filled drawer to the set
            return true; // there are less/equal filled drawers in the set than the total, so can fill
        } else {
            return false; // already at max filled drawers in this et
        }
    }
}