import java.util.*;
import java.io.*;

public class TequeTest {

    // maintain three hashmaps
    // fot push_front, push_middle and push_back
    private static HashMap<Integer, Integer> front = new HashMap<>();
    private static HashMap<Integer, Integer> back = new HashMap<>();
    static int frontMin = 0;
    static int frontMax = 0;
    static int backMin = 0;
    static int backMax = 0;

    public static void main(String[] args) throws IOException {

        InputStreamReader in = new InputStreamReader(System.in);
        BufferedReader bf = new BufferedReader(in);
        PrintWriter out = new PrintWriter(System.out);

        int queries = Integer.parseInt(bf.readLine());

        for (int i = 0; i < queries; i++) {
            String[] command = bf.readLine().split(" ");
            if (command[0].equals("get"))
                out.write(Integer.toString(get(Integer.parseInt(command[1]))) + '\n');
            else {
                switch(command[0].charAt(5)) {
                    case 'f':
                        push_front(Integer.parseInt(command[1]));
                        break;
                    case 'b':
                        push_back(Integer.parseInt(command[1]));
                        break;
                    case 'm':
                        push_middle(Integer.parseInt(command[1]));
                        break;
                }
            }
        }
        System.out.println(Arrays.asList(front));
        System.out.println(Arrays.asList(back));
        out.flush();

    }

    // push_front function
    private static void push_front(int x) {
        frontMin -= 1;
        front.put(frontMin, x);
        balance();
    }

    // push_back function
    private static void push_back(int x) {
        back.put(backMax, x);
        backMax += 1;
        balance();
    }

    // push_middle function
    private static void push_middle(int x) {
        if (front.size() == back.size()) {
            backMin -= 1;
            back.put(backMin, x);
        }
        else {
            front.put(frontMax, back.get(backMin));
            frontMax += 1;
            back.put(backMin, x);
        }
    }

    // get function
    private static int get(int index) {
        if (index < frontMax - frontMin)
            return front.get(frontMin + index);
        index -= (frontMax - frontMin);
        return back.get(backMin + index);
    }

    // balance size of front and back queues
    private static void balance() {
        if (front.size() > back.size()) {
            frontMax -= 1;
            backMin -= 1;
            back.put(backMin, front.get(frontMax));
            front.remove(frontMax);
            return;
        }
        if (back.size() > front.size()+1) {
            front.put(frontMax, back.get(backMin));
            frontMax += 1;
            backMin += 1;
            back.remove(backMin-1);
        }
    }

}