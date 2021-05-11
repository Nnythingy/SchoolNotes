import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Dominoes {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tok = new StringTokenizer(br.readLine());
        int cases = Integer.parseInt(tok.nextToken()); // no of cases

        for (int i = 0; i < cases; i++) {

            int fallenDown = 0;

            StringTokenizer tk = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(tk.nextToken());
            int m = Integer.parseInt(tk.nextToken());
            int l = Integer.parseInt(tk.nextToken());

            Domino[] dominos = new Domino[n + 1];

            for (int j = 1; j <= n; j++) {
                dominos[j] = new Domino(j);
            }

            boolean[] fallen = new boolean[n + 1];

            for (int j = 0; j < m; j++) {
                StringTokenizer tk2 = new StringTokenizer(br.readLine());
                int d1 = Integer.parseInt(tk2.nextToken());
                int d2 = Integer.parseInt(tk2.nextToken());

                dominos[d1].setNext(dominos[d2]);

            }

            for (int j = 0; j < l; j++) {
                int d = Integer.parseInt(br.readLine());
                Domino curr = dominos[d];

                if (!fallen[curr.getNo()]) {
                    fallenDown++;
                    fallen[curr.getNo()] = true;
                }

                while (curr.getNext() != null && !fallen[curr.getNext().getNo()]) {
                    fallen[curr.getNext().getNo()] = true;
                    fallenDown++;
                    curr = curr.getNext();
                }
            }

            pw.println(fallenDown);
        }

        pw.close();
    }
}
