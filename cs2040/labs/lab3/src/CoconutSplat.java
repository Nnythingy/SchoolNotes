import java.io.*;
import java.util.StringTokenizer;

public class CoconutSplat {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int syllables = Integer.parseInt(tk.nextToken());
        int playerNo = Integer.parseInt(tk.nextToken());

        if(syllables == 1) {
            pw.println(playerNo);
            pw.close();
            System.exit(0);
        }

        CircularList<Player> players = new CircularList<Player>();
        players.num_items = playerNo;

        for (int i = 0; i < playerNo; i++) {
            players.add(i, new Player(i + 1, "folded"));
        }
        int currIndex = 0;


        while(players.num_items > 1) {
            currIndex = (currIndex + syllables - 1) % players.num_items;
            Player curr = players.get(currIndex);

            switch (curr.getHand()) {
                case "folded":
                    curr = curr.changeHand("fist");
                    if(currIndex == players.num_items) {
                        players.add(currIndex + 1, new Player(curr.getPlayerNum(), "fist"));
                        players.num_items++;
                    } else {
                        players.insert(currIndex + 1, new Player(curr.getPlayerNum(), "fist"));
                    }
                    break;
                case "fist":
                    players.set(currIndex, curr.changeHand("palm"));
                    currIndex++;
                    break;
                case "palm":
                    players.removePlayer(currIndex);
                    break;
            }
        }

        pw.println(players.get(0).getPlayerNum());

        pw.close();
    }
}
