import java.io.*;
import java.util.HashMap;
import java.util.Stack;

public class DElimiter {

    public static Stack<String> chars = new Stack<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int num = Integer.parseInt(br.readLine());
        String line = br.readLine();

        boolean notOk = false;

        for(int i = 0; i < num; i++) {
            String curr = String.valueOf(line.charAt(i));

            if (curr.equals("(") || curr.equals("[") || curr.equals("{")) {
                chars.push(curr);

            } else if (curr.equals(")") || curr.equals("]") || curr.equals("}")) {

                if (chars.isEmpty()) {
                    pw.println(curr + " " + i);
                    notOk = true;
                    break;
                } else {
                    String temp = chars.pop();
                    if (!check(curr, temp)) {
                        pw.println(curr + " " + i);
                        notOk = true;
                        break;
                    }
                }
            }
        }

        if(!notOk) {
            pw.println("ok so far");
        }
        pw.close();
    }

    public static boolean check(String c, String t) {
        if(c.equals(")") && t.equals("(")) {
            return true;
        } else if (c.equals("}") && t.equals("{")) {
            return true;
        } else return c.equals("]") && t.equals("[");
    }
}
