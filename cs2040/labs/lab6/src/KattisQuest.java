import java.io.*;
import java.util.*;

public class KattisQuest {
    public static TreeMap<Integer, PriorityQueue<Quest>> questMap = new TreeMap<>(); // for storing data

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int n = Integer.parseInt(br.readLine()); // get number of commands

        for(int i = 0; i < n; i++) { // get details of command
            StringTokenizer tk = new StringTokenizer(br.readLine());
            String cmd = tk.nextToken();
            int energy = Integer.parseInt(tk.nextToken());

            if (cmd.equals("add")) { // add
                int gold = Integer.parseInt(tk.nextToken());
                Quest q = new Quest(energy, gold); // generate quest
                add(q); // call add method

            } else if (cmd.equals("query")) {
                pw.println(query(energy)); // print long result for query
            }
        }

        pw.close();
    }

    public static void add(Quest q) { // checks if a key is presnt
        int key = q.getEnergy();

        if (!questMap.containsKey(key)) { // if key is present, create new pq and add
            PriorityQueue<Quest> pq = new PriorityQueue<>(new GoldCom());
            pq.add(q);
            questMap.put(key, pq);
        } else { // add to existing queue
            questMap.get(key).add(q);
        }
    }

    public static long query(int e) {
        long totalGold = 0;
        int energyLvl = e;

        while (questMap.floorKey(energyLvl) != null) { // do until cannot find a lower value
            int key = questMap.floorKey(energyLvl); // get biggest value lower than input
            Quest quest = questMap.get(key).poll(); // find the most gold quest for that key
            totalGold += quest.getGold(); // add
            energyLvl -= key; // subtract energy

            if (questMap.get(key).isEmpty()) { // if the pq is empty, then remove
                questMap.remove(key);
            }
        }

        return totalGold; // return gold sum
    }
}
