import java.io.*;
import java.util.HashMap;
import java.util.StringTokenizer;

public class BoatParts {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        HashMap<Integer,String> partMap = new HashMap<Integer, String>();
        int currIndex = 0;

        StringTokenizer tk = new StringTokenizer(br.readLine());

        int noOfParts = Integer.parseInt(tk.nextToken());
        int days = Integer.parseInt(tk.nextToken());

        for (int i = 0; i < days; i++) {
            String part = br.readLine();

            if(!partMap.containsValue(part)) {
                currIndex++;
                partMap.put(currIndex, part);
            }

            if(currIndex == noOfParts) {
                pw.println(i+1);
                break;
            }
        }

        if(currIndex < noOfParts) {
            pw.println("paradox avoided");
        }

        pw.close();

    }
}
