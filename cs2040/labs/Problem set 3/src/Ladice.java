import java.io.*;
import java.util.StringTokenizer;

public class Ladice {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int items = Integer.parseInt(tk.nextToken()); // no of items
        int drawers = Integer.parseInt(tk.nextToken()); // no of available drawers

        UnionFind uf = new UnionFind(drawers); // create a new union find with max no of drawers

        for (int i = 0; i < items; i++) {
            StringTokenizer tk2 = new StringTokenizer(br.readLine());
            int d1 = Integer.parseInt(tk2.nextToken()); // first drawer no
            int d2 = Integer.parseInt(tk2.nextToken()); // second drawer no

            if (uf.canFill(d1) || uf.canFill(d2)) { // see if there is an unfilled drawer in the set 1 or 2
                pw.println("LADICA");
                uf.unionSet(d1,d2); // join
            } else {
                pw.println("SMECE"); // no empty drawer found, discard
            }
        }

        pw.close();
    }
}
