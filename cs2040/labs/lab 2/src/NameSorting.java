//Schubert Goh A0200125E Week 5 1 Day lab

import java.io.*;
import java.util.Arrays;

public class NameSorting {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int noOfNames;

        // do-while loop for at least one input
        do {
            noOfNames = Integer.parseInt(br.readLine());
            String[] nameList = new String[noOfNames];

            // get array of strings
            for(int i = 0; i < noOfNames; i++) {
                nameList[i] = br.readLine();
            }

            //use comparator to sort by first 2 characters
            Arrays.sort(nameList, new StringComparator2<String>());

            //print first sorted array
            for(int i = 0; i < noOfNames; i++) {
                pw.println(nameList[i]);
            }
            pw.println();

        } while (noOfNames > 0);

        pw.close();
    }

}


