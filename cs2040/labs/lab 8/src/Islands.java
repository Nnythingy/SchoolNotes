import java.io.*;
import java.util.StringTokenizer;

public class Islands {

    public static char[][] grid;
    public static boolean[][] visited;
    public static int iCount = 0;
    public static int rows;
    public static int cols;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        rows = Integer.parseInt(tk.nextToken()); // no of rows
        cols = Integer.parseInt(tk.nextToken()); // no of cols

        grid = new char[rows][cols]; // for plotting map
        visited = new boolean[rows][cols]; // check if island is visited

        // plot map
        for (int i = 0; i < rows; i++) {
            String line = br.readLine();
            for (int j = 0; j < cols; j++) {
                grid[i][j] = line.charAt(j);
            }
        }
        // check how many new land grids you can find
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!visited[i][j] && grid[i][j] == 'L') {
                    traverse(i, j); // search for adjacent land/cloud
                    iCount++; // new land found, add to total
                }
            }
        }
        pw.println(iCount); // print total no of islands found
        pw.close();
    }

    // keep searching until land/clouds can no longer be found
    public static void traverse(int i, int j) {
        visited[i][j] = true; // visited this point

        // search top grid
        if (i - 1 >= 0 && (grid[i -1][j] == 'C' || grid[i -1][j] == 'L') && !visited[i - 1][j]) {
            traverse(i - 1, j); // keep searching
        }
        // search bottom grid
        if (i + 1 < rows && (grid[i + 1][j] == 'C' || grid[i + 1][j] == 'L') && !visited[i + 1][j]) {
            traverse(i + 1, j); // keep searching
        }
        // search left grid
        if (j - 1 >= 0 && (grid[i][j - 1] == 'C' || grid[i][j - 1] == 'L') && !visited[i][j - 1]) {
            traverse(i, j - 1); // keep searching
        }
        // search right grid
        if (j + 1 < cols && (grid[i][j + 1] == 'C' || grid[i][j + 1] == 'L') && !visited[i][j + 1]) {
            traverse(i, j + 1); // keep searching
        }

    }



}
