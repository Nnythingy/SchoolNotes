import java.io.*;
import java.util.StringTokenizer;

public class CoconutSplat2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int syllables = Integer.parseInt(tk.nextToken());
        int playerNo = Integer.parseInt(tk.nextToken());

        Player[] arr = new Player[playerNo*2];

        for (int i = 0; i < playerNo; i++) {
            insert(i, new Player(i + 1, "folded"), arr, playerNo);
        }

        int currIndex = 0;

        while(playerNo > 1) {
            currIndex = (currIndex + syllables - 1)% playerNo;
            Player curr = arr[currIndex];

            switch (curr.getHand()) {
                case "folded":
                    curr.changeHand("fist");
                    if(arr[currIndex+1] == null) {
                        arr[currIndex+1] = new Player(curr.getPlayerNum(), "fist");
                    } else {
                        insert(currIndex + 1, new Player(curr.getPlayerNum(), "fist"), arr, playerNo);
                    }
                    playerNo++;
                    break;
                case "fist":
                    curr.changeHand("palm");
                    currIndex++;
                    break;
                case "palm":
                    removePlayer(currIndex, arr, playerNo);
                    playerNo--;
                    break;
            }
        }

        pw.println(arr[0].getPlayerNum());

        pw.close();

    }

    public static void insert(int index, Player p, Player[] arr, int numItems) {
        if (numItems - index >= 0) {
            System.arraycopy(arr, index, arr, index + 1, numItems - index);
        }
        arr[index + 1] = p; // insert item in gap
    }

    public static void removePlayer(int index, Player[] arr, int numItems) {
        Player p = arr[index];
        // shift item from index+1 onwards to the left to close the gap
        if (numItems - index + 1 >= 0) {
            System.arraycopy(arr, index + 1, arr, index + 1 - 1, numItems - index + 1);
        }
        numItems--;
    }
}
