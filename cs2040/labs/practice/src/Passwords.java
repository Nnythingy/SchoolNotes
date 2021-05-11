import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Passwords {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new
                OutputStreamWriter(System.out)));

        int n = Integer.parseInt(br.readLine());
        double[] probs = new double[n];

        for(int i = 0; i < n; i++) {
            StringTokenizer tk = new StringTokenizer(br.readLine()); // use this to divide input into vals
            String pass = tk.nextToken();
            double prob = Double.parseDouble(tk.nextToken());

            probs[i] = prob; // get array of probabilities
        }

        Arrays.sort(probs);
        double totalTime = 0;
        int j = 1;

        for(int i = n-1; i >= 0; i--) {
            totalTime += probs[i]*(j);
            j++;
        }

        pw.println(String.format("%.4f", totalTime));
        pw.close();
    }
}
