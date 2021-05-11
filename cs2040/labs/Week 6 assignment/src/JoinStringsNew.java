import java.io.*;
import java.util.StringTokenizer;

public class JoinStringsNew {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        //get number of words
        int numOfWords = Integer.parseInt(br.readLine());

        //create arrays for words and position indexing
        String[] words = new String[numOfWords + 1];
        int[] newIndexes = new int[numOfWords + 1];
        int[] queue = new int[numOfWords + 1];

        //add words to word array
        for (int i = 1; i < numOfWords + 1; i++) {
            words[i] = br.readLine();
        }

        //temp ints for indexing, start at 1 as we only work with numbers 1 to n
        int temp1 = 1;
        int temp2 = 1;

        //get as many operations as needed
        for (int i = 0; i < numOfWords - 1; i++) {
            StringTokenizer tk = new StringTokenizer(br.readLine());
            temp1 = Integer.parseInt(tk.nextToken());
            temp2 = Integer.parseInt(tk.nextToken()); // get 2 pos ints

            if (newIndexes[temp1] == 0) { // add positions to arrays to note down curr positions
                newIndexes[temp1] = temp2;
                queue[temp1] = temp2;
                continue; // skip the rest of the loop, we are done setting the indexes
            }

            int x = newIndexes[temp1]; // x is a temp int for shifting positions

            while (newIndexes[x] != 0) { // shifts to last position
                x = newIndexes[x];
            }
            newIndexes[temp1] = temp2; // replace
            queue[x] = temp2;
        }
        // at the end, ints are ordered in a position such that temp1
        // will link to the index of next string to be added
        while (queue[temp1] != 0) {
            pw.append(words[temp1]); // first string to be appended
            temp1 = queue[temp1];
        }
        //add space
        pw.append(words[temp1]).append("\n");
        pw.close();

    }
}
