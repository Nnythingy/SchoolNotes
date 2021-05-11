import java.io.*;
import java.util.StringTokenizer;

public class BestRelayTeam {
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

        //Temp  variables for final runners and time
        double fastestTime = 0;
        Runner[] fastestTeam = new Runner[4]; // stores final 4 runners

        // Find the best combination of runners
        for(int i = 0; i < runnerNo; i++) {

            // Propose this team of the lead and 3 secondary runners
            Runner lead = runners[i];
            Runner[] nextThree = threeFastest(runners,lead);

            //get time for this team
            double teamTime = lead.getFirstTime();
            for(int j = 0; j < 3; j++) {
                teamTime += nextThree[j].getOtherLegTime();
            }

            //see if new time is faster than previous team, then replace time and team members
            if(teamTime < fastestTime || fastestTime == 0) {
                fastestTime = teamTime;
                fastestTeam[0] = lead;
                System.arraycopy(nextThree, 0, fastestTeam, 1, 3);
            }
        }

        //print fastest time and names of fastest team fastest team found
        pw.println(fastestTime);

        for (Runner runner : fastestTeam) {
            pw.println(runner.getName());
        }
        
        pw.close();
    }

    // Get three fastest second runners
    public static Runner[] threeFastest(Runner[] runners, Runner lead) {

        Runner[] threeFast = new Runner[3];
        Runner first = new Runner("I", 0, 999999999); // get max run value
        Runner second = first;
        Runner third = first;

        for (Runner runner : runners) {
            if (runner.getOtherLegTime() < first.getOtherLegTime()
                    && !runner.equals(lead)) {
                third = second;
                second = first;
                first = runner;
            } else if (runner.getOtherLegTime() < second.getOtherLegTime()
                    && !runner.equals(lead)) {
                third = second;
                second = runner;
            } else if (runner.getOtherLegTime() < third.getOtherLegTime()
                    && !runner.equals(lead)) {
                third = runner;
            }
        }

        threeFast[0] = first;
        threeFast[1] = second;
        threeFast[2] = third;

        return threeFast;
    }

}
