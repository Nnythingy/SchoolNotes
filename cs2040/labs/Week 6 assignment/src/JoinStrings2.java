import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class JoinStrings2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        //get number of words to work on
        int wordCount = Integer.parseInt(br.readLine());
        StringHolder[] holders = new StringHolder[wordCount + 1];

        // insert word into a String holder for merging later
        for(int i = 1; i < wordCount + 1; i++) {
            String word = br.readLine();
            holders[i] = new StringHolder(wordCount, word);

        }

        int currHolderNo = 1;
        int otherHolderNo = 1; // temp holding

        for(int i = 0; i < wordCount - 1; i++) {
            // get the 2 ints that are positions
            StringTokenizer tk = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(tk.nextToken());
            int b = Integer.parseInt(tk.nextToken());

            // merge holders to update them
            holders[a].merge(holders[b]);
            //update holder no for reference
            currHolderNo = a;
        }

        // this is the final holder that has all the strings in order;
        StringHolder finalHolder = holders[currHolderNo];

        // print the words in this holder
        for(int i = 0; i < finalHolder.getWords().length; i++) {
            pw.print(finalHolder.getWords()[i]);
        }
        pw.println();

        pw.close();


    }
}
