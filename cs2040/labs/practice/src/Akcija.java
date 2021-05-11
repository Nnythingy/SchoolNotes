import java.io.*;
import java.util.Arrays;

public class Akcija {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int noOfBooks = Integer.parseInt(br.readLine());
        int[] prices = new int[noOfBooks];
        int totalCost = 0;

        for(int i = 0; i < noOfBooks; i++) {
            int bookCost = Integer.parseInt(br.readLine());
            prices[i] = bookCost;
            totalCost += bookCost;
        }

        Arrays.sort(prices);

        for (int i = noOfBooks%3; i < prices.length; i += 3) {
            totalCost -= prices[i];
        }

        pw.println(totalCost);

        pw.close();
    }
}
