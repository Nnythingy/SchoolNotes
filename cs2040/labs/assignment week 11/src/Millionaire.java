import java.io.*;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

import static java.lang.Math.*;

public class Millionaire {
    public static int[] xVal = {1,-1,0,0};
    public static int[] yVal = {0,0,1,-1};
    public static long[][] stacks;
    public static long[][] best;
    public static boolean[][] visited;
    public static int rows;
    public static int cols;
    public static PriorityQueue<Coins> pq;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        rows = Integer.parseInt(tk.nextToken()); // no of rows
        cols = Integer.parseInt(tk.nextToken()); // no of cols

        stacks = new long[rows][cols]; // for plotting map
        best = new long[rows][cols]; // for checking best value in each stack
        visited = new boolean[rows][cols]; // for checking if a section has been traversed already

        // plot map
        for (int i = 0; i < rows; i++) {
            StringTokenizer tok = new StringTokenizer(br.readLine());
            for (int j = 0; j < cols; j++) {
                stacks[i][j] = Long.parseLong(tok.nextToken()); // plot main map
                best[i][j] = Long.MAX_VALUE; // need this for checking
            }
        }

        best[0][0] = 0; // initialize first stop
        pq = new PriorityQueue<>(new StackCompare()); // for polling best outcome
        pq.add(new Coins(0,0,0)); //add best at 0,0

        while(!pq.isEmpty()) {
            Coins currCoins = pq.poll(); // check top value
            int currX = currCoins.x;
            int currY = currCoins.y;

            if(!visited[currX][currY]) { // check if visited this grid
                visited[currX][currY] = true; // mark as visited to avoid repetition

                for (int i = 0; i < 4; i++) { // check all four sides and find the best
                    int nextX = currX + xVal[i];
                    int nextY = currY + yVal[i];

                    if (inMap(nextX, nextY)) {
                        // check if descending or ascending
                        long nextVal = max(0, stacks[nextX][nextY] - stacks[currX][currY]);
                        nextVal = max(nextVal, best[currX][currY]); // check shortest stack to go to

                        if (best[nextX][nextY] > nextVal) { // check if new value is smaller
                            best[nextX][nextY] = nextVal; // set this as best
                            pq.add(new Coins(nextX, nextY, nextVal)); // add this lowest value to pq
                        }
                    }
                }
            }
        }

        pw.println(best[rows - 1][cols - 1]); // check last slot
        pw.close();
    }

    public static boolean inMap(int x, int y) { // for checking if a point is within the grid
        return x >= 0 && y >= 0 && x < rows && y < cols;
    }

}
