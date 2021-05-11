import java.io.*;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class LostMap2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int n = Integer.parseInt(br.readLine()); // no of rows

        int[][] graph = new int[n][n]; // for plotting map
        boolean[][] added = new boolean[n][n]; // for checking if we've added this
        boolean[] connected = new boolean[n]; // for checking if this point is connected to the main
        PriorityQueue<Village> pq = new PriorityQueue<>(new Vcom()); // for pqing elements
        int curr = 0; // for checking with row in teh graph to traverse

        for (int i = 0; i < n; i++) { // graphing
            StringTokenizer tok = new StringTokenizer(br.readLine());
            for (int j = 0; j < n; j++) {
                graph[i][j] = Integer.parseInt(tok.nextToken());
            }
        }

        for (int i = 0; i < n - 1; i++) { // pq n-1 elements, the paths of the graph
            for (int j = 0; j < n; j++) {
                if (!added[curr][j] && !connected[j] && curr != j) { // check if should add to pq
                    pq.add(new Village(curr + 1, j + 1, graph[curr][j])); // add
                    added[curr][j] = true; // mark as added
                    added[j][curr] = true;
                }
            }

            while (connected[pq.peek().y - 1]) { // keep polling until you can find a vertice that has not been traversed
                pq.poll();
            }

            Village v = pq.poll(); // poll the first avaliable vilalge
            pw.println(v); // print
            connected[v.y - 1] = true; // the y is connected
            curr = v.y - 1; // set the nest row to find as current
        }

        pw.close();
    }
}
