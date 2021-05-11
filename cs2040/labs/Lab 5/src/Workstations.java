import java.io.*;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Workstations {
    // for queueing researchers based on arrival time and their leaving time when using the workstations, respectively
    public static PriorityQueue<Researcher> waiting = new PriorityQueue<>(new TimeCompare());
    public static PriorityQueue<Researcher> workStations = new PriorityQueue<>(new TimeCompareLeave());

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int num = Integer.parseInt(tk.nextToken()); // no of researchers
        int lockTime = Integer.parseInt(tk.nextToken()); // time for auto lockout

        for(int i = 0; i < num; i++) { // add researchers to the queue, and sort them by arrival time
            StringTokenizer tkk = new StringTokenizer(br.readLine());
            int arr = Integer.parseInt(tkk.nextToken());
            int duration = Integer.parseInt(tkk.nextToken());

            waiting.add(new Researcher(arr, arr + duration, arr + duration + lockTime));
        }

        int unlockCount = 0; // count how many unlocks are done

        while(!waiting.isEmpty()) {
            Researcher curr = waiting.poll(); // poll the waiting queue
            boolean assigned = false; // true when a researcher is given a workstation

            while(!assigned) { // while researcher has not found a waiting spot
                if (workStations.isEmpty()) { // case when the workstations are all empty
                    workStations.add(curr);
                    unlockCount++;
                    assigned = true;
                // case when there is something in the queue but the workstation is unavailable
                } else if (curr.getArrTime() >= workStations.peek().getArrTime() &&
                        curr.getArrTime() < workStations.peek().getLeaveTime()) {
                    workStations.add(curr);
                    unlockCount++;
                    assigned = true;
                    // case when the workstation is available
                } else if (curr.getArrTime() >= workStations.peek().getLeaveTime() &&
                        curr.getArrTime() <= workStations.peek().getLockoutTime()) {
                    workStations.poll();
                    workStations.add(curr);
                    assigned = true;
                } else { // case when the first workstation is beyond waiting time, so keep polling until can find one
                    workStations.poll();
                }
            }
        }

        pw.println(num - unlockCount); //.difference in how many locks were saved
        pw.close();
    }
}
