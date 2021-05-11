import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BestRelayTeam2 {
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new
                OutputStreamWriter(System.out)));

        int runnerNo = Integer.parseInt(br.readLine()); // get no of runners
        Runner[] runners = new Runner[runnerNo];

        // get inputs to create an array of Runner Objects
        for(int i = 0; i < runnerNo; i++) {
            StringTokenizer tk = new StringTokenizer(br.readLine()); // use this to divide input into vals

            String name = tk.nextToken(); // get runner name
            double firstTime = Double.parseDouble(tk.nextToken()); // get runner first lap time
            double otherTime = Double.parseDouble(tk.nextToken()); // get runner other lap time

            runners[i] = new Runner(name, firstTime, otherTime); // create runner from inputs
        }

        //sort runners by their other leg time
        Arrays.sort(runners, new OtherTimeComparator());

        //Temp  variables for final runners and time
        double fastestTime = 0;
        Runner[] fastestTeam = new Runner[4]; // stores final 4 runners

        // Find the best combination of runners
        for(int i = 0; i < runnerNo; i++) {

            // Propose this team of the lead and 3 secondary runners
            Runner[] tempTeam = new Runner[4];
            tempTeam[0] = runners[i];
            addThreeFastest(runners, tempTeam); // this adds the first 3 fastest second runners found

            //get time for this team
            double teamTime = tempTeam[0].getFirstTime();
            for(int j = 1; j < 3; j++) {
                teamTime += tempTeam[j].getOtherLegTime();
            }

            //see if new time is faster than previous team, then replace time and team members
            if(teamTime < fastestTime || fastestTime == 0) {
                fastestTime = teamTime;
                System.arraycopy(tempTeam, 0, fastestTeam, 0, 4);
            }
        }

        //print fastest time and names of fastest team fastest team found
        pw.println(fastestTime);

        for (Runner runner : fastestTeam) {
            pw.println(runner.getName());
        }

        pw.close();
    }

    public static void addThreeFastest(Runner[] runners, Runner[] tempTeam) {
        int tempPos = 1;
        int runnerPos = 0;

        while(tempPos <= 3) {
            if(tempTeam[0] != runners[runnerPos]) {
                tempTeam[tempPos] = runners[runnerPos];
                tempPos++;
            }
            runnerPos++;
        }
    }
}
