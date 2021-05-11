import java.io.*;
import java.util.StringTokenizer;

public class LostMap {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(tk.nextToken()); // no of rows

        int[][] graph = new int[n][n]; // for plotting map

        // plot map
        for (int i = 0; i < n; i++) {
            StringTokenizer tok = new StringTokenizer(br.readLine());
            for (int j = 0; j < n; j++) {
                graph[i][j] = Integer.parseInt(tok.nextToken());
            }
        }

        int[] mstIndex = new int[n]; // for indexing each path
        int[] minPath = new int[n]; // for finding mind distances
        boolean[] connected = new boolean[n]; // mark points as connected

        for (int i = 1; i < n; i++) {
            minPath[i] = Integer.MAX_VALUE; // set as max path
            connected[i] = false;
        }

        minPath[0] = 0; // only need n-1 paths
        mstIndex[0] = 0; // we will only need n -1 index

        for (int i = 0; i < n - 1; i++) {
            int min = Integer.MAX_VALUE; // find the min
            int minIndex = 0; // set index as 0

            for (int j = 0; j < n; j++) {
                if (!connected[j] && minPath[j] < min) {
                    min = minPath[j]; // replace, new min found
                    minIndex = j; // update min index in each index
                }
            }
            connected[minIndex] = true; // connected

            for (int j = 0; j < n; j++) {
                if (!connected[j] && graph[minIndex][j] < minPath[j]) {
                    mstIndex[j] = minIndex; // update min indexes
                    minPath[j] = graph[minIndex][j]; // update minPath
                }
            }
        }

        for (int i = 1; i < n; i++) {
            pw.println((mstIndex[i] + 1) + " " + (i + 1)); // print out all paths
        }

        pw.close();

    }
}
