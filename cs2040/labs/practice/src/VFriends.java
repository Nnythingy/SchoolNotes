import java.io.*;
import java.util.StringTokenizer;

public class VFriends {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int testCases = Integer.parseInt(br.readLine());

        for(int i = 0; i < testCases; i++) {
            int actions = Integer.parseInt(br.readLine());
            UnionFind friendSets = new UnionFind();

            for(int j = 0; j < actions; j++) {
                StringTokenizer tk = new StringTokenizer(br.readLine());
                String name1 = tk.nextToken();
                String name2 = tk.nextToken();


            }

        }
    }
}
