import java.io.*;
import java.util.HashMap;
import java.util.StringTokenizer;

public class Teque {

    // hash maps to store ints and tabulate them, so that the maps are always the same size
    // maps contain elements hashed to indexes to find them in O(1) time
    static HashMap<Integer, Integer> a = new HashMap<Integer, Integer>();
    static HashMap<Integer, Integer> b = new HashMap<Integer, Integer>();

    // used to keep track of indexes for incoming values, lowest index and cap index
    static int aFirst = 0;
    static int aLast = 0;
    static int bFirst = 0;
    static int bLast = 0;


    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int num = Integer.parseInt(br.readLine()); // no of inputs

        for(int i = 0; i < num; i++) {
            StringTokenizer tk = new StringTokenizer(br.readLine());
            String command = tk.nextToken();
            int value = Integer.parseInt(tk.nextToken());

            if(command.equals("get")) {
                pw.println(get(value)); // get value
            } else {
                switch (command.charAt(5)) { // methods
                    case 'f' :
                        pushFront(value);
                        break;
                    case 'b' :
                        pushBack(value);
                        break;
                    case 'm' :
                        pushMid(value);
                        break;
                }
            }
        }

        pw.close();
    }

    // add to the front of the sequence
    public static void pushFront (int value) {
        aFirst--; // update first index
        a.put(aFirst, value);
        tabulate();
    }
    // add to teh back of the values
    public static void pushBack (int value) {
        b.put(bLast, value);
        bLast++; // update last index
        tabulate();
    }

    public static void pushMid (int value) {
        // adds input to the start of b (midpoint)
        if(a.size() == b.size()) { // put at start of b , where if total no is odd, b should have one more element than a
            bFirst--;
        } else { //its odd
            a.put(aLast, b.get(bFirst)); // moves bFirst element to back of a
            aLast++;
        }
        b.put(bFirst, value); // places element at start of b
    }

    // ensures maps are of equal size, or if total no is odd, b, has one more than a
    public static void tabulate() {
        if (a.size() > b.size()) { // shifts last element in a to start of b
            aLast--;
            bFirst--;
            b.put(bFirst, a.get(aLast));
            a.remove(aLast);
        } else if (b.size() > a.size() + 1) { // shifts first element in b to start of a, making them equal
            a.put(aLast, b.get(bFirst)); // hash element to the last in a
            b.remove(bFirst); // remove element
            aLast++;
            bFirst++;

        }
    }

    public static int get(int key) {

        // check whether this key is in map a or b
        if(key < a.size()) {
            return a.get(aFirst + key); // keys always ordered consecutively
        } else {
            key -= a.size(); // jumps forward
            return b.get(bFirst + key); // keys always ordered consecutively
        }
    }
}
