import java.io.*;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.StringTokenizer;

public class Conformity {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int n = Integer.parseInt(br.readLine());
        // map <combi as string, popularity count>
        HashMap<String, Integer> comboMap = new HashMap<String, Integer>();

        for(int i = 0; i < n; i++) {
            String[] combo = new String[5];
            StringTokenizer tk = new StringTokenizer(br.readLine());

            for(int k = 0; k < 5; k++) {
                combo[k] = tk.nextToken(); // add an array of combinations
            }

            // sort combo to get fixed combi of classes
            Arrays.sort(combo);
            // turns sorted combo into a string
            String code = combo[0];
            for(int c = 1; c < 5; c++) {
                code = code.concat(combo[c]);
            }

            // updates map for no of times the combination has appeared
            if(comboMap.containsKey(code)) { // update no of times
                int count = comboMap.get(code); // check curr no of times this key is recorded
                comboMap.put(code, count + 1);
            } else {
                comboMap.put(code, 1); // new entry, just add into map
            }
        }

        //maxValue is the most popular combination of classes
        int maxValue = Collections.max(comboMap.values());
        //count is the number of combinations that have this popularity count
        int count = Collections.frequency(comboMap.values(), maxValue);

        // prints out no of students who are in the most popular combinations
        pw.println(count*maxValue);

        pw.close();
    }
}
