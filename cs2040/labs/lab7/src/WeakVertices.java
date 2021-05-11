import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class WeakVertices {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        boolean notMinusOne = true; // to check when to end program

        do {
            int n = Integer.parseInt(br.readLine());
            if (n == -1) {
                notMinusOne = false; // end program
            }
            //use this to store inputs
            ArrayList<ArrayList<Integer>> list = new ArrayList<>();
            // add to graph
            for (int i = 0; i < n; i++) {
                StringTokenizer tk = new StringTokenizer(br.readLine());
                ArrayList<Integer> temp = new ArrayList<>();

                for(int j = 0; j < n; j++) {
                    int u = Integer.parseInt(tk.nextToken());
                    if (u == 1) {
                        temp.add(j);
                    }
                }
                list.add(temp);
            }

            if (n > 2) { // if contains more than 2, there may be a triangle
                for (int i = 0; i < list.size(); i++) {
                    ArrayList<Integer> temp = list.get(i);
                    boolean hasTri = false;

                        for (int j = 0; j < temp.size() - 1; j++) {
                            for (int k = j + 1; k < temp.size(); k++) {
                                if (list.get(temp.get(j)).contains(temp.get(k))) { // check if j and k are connected
                                    hasTri = true;
                                    break;
                                }
                            }
                        }

                    if (!hasTri) {
                        pw.print(i + " "); // no triangle found, print
                    }
                }

            } else {
                for(int i = 0; i < n; i++) { // for size of 2 and less, there will be no triangle, so print all vertices
                    pw.print(i + " ");
                }
            }

            pw.println();

        } while (notMinusOne); // terminate if found -1

        pw.close();


    }
}
