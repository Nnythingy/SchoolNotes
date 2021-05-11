import java.io.*;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Cannonball {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk1 = new StringTokenizer(br.readLine()); // start Coordinates
        double startX = Double.parseDouble(tk1.nextToken());
        double startY = Double.parseDouble(tk1.nextToken());
        Point start = new Point(startX, startY);

        StringTokenizer tk2 = new StringTokenizer(br.readLine()); // start Coordinates
        double endX = Double.parseDouble(tk2.nextToken());
        double endY = Double.parseDouble(tk2.nextToken());
        Point end = new Point(endX, endY);

        //set up array of points of cannons
        int n = Integer.parseInt(br.readLine());
        Point[] points = new Point[n+2];
        points[0] = start;
        points[n+1] = end;

        // get points of cannons
        for (int i = 1; i <= n; i++) {
            StringTokenizer tok = new StringTokenizer(br.readLine());
            double x = Double.parseDouble(tok.nextToken());
            double y = Double.parseDouble(tok.nextToken());
            points[i] = new Point(x, y);
        }

        // Initialize empty adjacency matrix
        double[][] dists = new double[n+2][n+2];
        for (int i=0; i<n+2; i++) {
            Arrays.fill(dists[i], Double.MAX_VALUE);
            dists[i][i] = 0;
        }

        // initialize time from strat to all cannons
        for (int i=1; i<n+2; i++) {
            dists[0][i] = points[0].distTo(points[i]) / 5;
        }
        // check for all cannons, is running to them faster or canning faster
        for (int i=1; i<n+1; i++)
            for (int j=1; j<n+2; j++)
                dists[i][j] = Math.min(2 + Math.abs((points[i].distTo(points[j])-50)/5),
                        points[i].distTo(points[j])/5);

        // perform floyd warshall's to get shortest time
        for (int k=0; k<n+2; k++)
            for (int i=0; i<n+2; i++)
                for (int j=0; j<n+2; j++)
                    dists[i][j] = Math.min(dists[i][j], dists[i][k] + dists[k][j]);

        // the last cannon spot will have the shortest time
        pw.println(dists[0][n+1]);
        pw.close();
    }
}
