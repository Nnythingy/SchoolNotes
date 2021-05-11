import java.io.*;
import java.util.StringTokenizer;

public class TenKInds {

    public static int[][] grid;
    public static int[][] fillMap;
    public static boolean[][] filled;
    public static int rows;
    public static int cols;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        rows = Integer.parseInt(tk.nextToken()); // no of rows
        cols = Integer.parseInt(tk.nextToken()); // no of cols

        grid = new int[rows][cols]; // for plotting map
        fillMap = new int[rows][cols]; // for plotting map
        filled = new boolean[rows][cols]; // for checking if a section has been filled already

        // plot map
        for (int i = 0; i < rows; i++) {
            String line = br.readLine();
            for (int j = 0; j < cols; j++) {
                grid[i][j] = line.charAt(j) - '0';
                fillMap[i][j] = line.charAt(j) - '0'; // fill both fill map and original
            }
        }

        int f = 2; // for getting sections in the map

        // fill map into sections
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!filled[i][j]) {
                    refill(grid[i][j], f, i, j); // fill the whole connected section
                    f++; // next no for nest section
                }
            }
        }

        int cases = Integer.parseInt(br.readLine()); // get number of test cases

        for (int i = 0; i < cases; i++) {
            // get coordinates of start and end
            StringTokenizer tok = new StringTokenizer(br.readLine());
            int x1 = Integer.parseInt(tok.nextToken()) - 1;
            int y1 = Integer.parseInt(tok.nextToken()) - 1;
            int x2 = Integer.parseInt(tok.nextToken()) - 1;
            int y2 = Integer.parseInt(tok.nextToken()) - 1;

            if(grid[x1][y1] != grid[x2][y2]) { // original numbers don't match
                pw.println("neither");
            } else {
                if (grid[x1][y1] == 0 && fillMap[x1][y1] == fillMap[x2][y2]) { // binary match
                    pw.println("binary");
                } else if (grid[x1][y1] == 1 && fillMap[x1][y1] == fillMap[x2][y2]) { //decimal match
                    pw.println("decimal");
                } else {
                    pw.println("neither"); // no match found
                }
            }
        }
        pw.close();
    }

    public static void refill(int original, int newNo, int x1, int y1) {

        fillMap[x1][y1] = newNo; // fill this with new no
        filled[x1][y1] = true; // set to filled

        if (x1 - 1 >= 0 && fillMap[x1 - 1][y1] == original && !filled[x1 - 1][y1]) {
            refill(original, newNo, x1 - 1, y1); // keep searching
        }
        // search bottom grid
        if (x1 + 1 < rows && fillMap[x1 + 1][y1] == original && !filled[x1 + 1][y1]) {
            refill(original, newNo,x1 + 1, y1); // keep searching
        }
        // search left grid
        if (y1 - 1 >= 0 && fillMap[x1][y1 - 1] == original && !filled[x1][y1 - 1]) {
            refill(original, newNo, x1,y1 - 1); // keep searching
        }
        // search right grid
        if (y1 + 1 < cols && fillMap[x1][y1 + 1] == original && !filled[x1][y1 + 1]) {
            refill(original, newNo,  x1 , y1 + 1); // keep searching
        }
    }
}
