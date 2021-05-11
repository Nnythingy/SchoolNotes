import java.io.*;
import java.util.StringTokenizer;

public class Ucpc {

    public static int rank = 1; // for checking rank of fav team

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int teams = Integer.parseInt(tk.nextToken()); // no of teams
        int actions = Integer.parseInt(tk.nextToken()); // no of updates

        Team[] teamList = new Team[teams + 1];
        boolean[] teamIn = new boolean[teams + 1];
        AVLTree<Team> betterTeams = new AVLTree<>();


        for(int i = 1; i <= teams; i++) {
            teamList[i] = new Team(i);
        }
        // check if team can be inserted
        for (int i = 0; i < actions; i++) {
            StringTokenizer tk2 = new StringTokenizer(br.readLine());
            int teamNo = Integer.parseInt(tk2.nextToken());
            int penalties = Integer.parseInt(tk2.nextToken());

            if(teamIn[teamNo]) {
                betterTeams.delete(teamList[teamNo]);
            }

            teamList[teamNo].updateScore(penalties);

            if (teamNo != 1 && teamList[teamNo].compareTo(teamList[1]) > 0) {
                if(!teamIn[teamNo]) {
                    rank++;
                    teamIn[teamNo] = true;
                }
                betterTeams.insert(teamList[teamNo]);

            } else if (teamNo == 1) {
                while (!betterTeams.isEmpty() && betterTeams.minNode().val.compareTo(teamList[1]) <= 0) {
                    teamIn[betterTeams.minNode().val.getId()] = false;
                    betterTeams.delete(betterTeams.minNode().val);
                    rank--;
                }
            }

            pw.println(rank);
        }

        pw.close();
    }
}
