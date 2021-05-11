import java.io.*;
import java.util.Arrays;

public class Delimiter {

    public static char expectSymbol;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int n = Integer.parseInt(br.readLine());
        String s = br.readLine();

        char[] symbols = s.toCharArray();

        for(int i = 0; i < symbols.length; i++) {
            changeSymbol(symbols[i]);

            if(symbolMismatch(symbols[i])) {
                pw.println(symbols[i]  + " " + i);
                break;
            }

            if( i == symbols.length - 1 && !symbolMismatch(symbols[i])) {
                pw.println("ok so far");
            }
        }



        pw.close();

    }

    public static void changeSymbol(char c) {
        switch(c) {
            case '(':
                expectSymbol = ')';
            case '[':
                expectSymbol = ']';
            case '{':
                expectSymbol = '}';
        }
    }

    public static boolean symbolMismatch(char c) {
        return (c == ')' || c == ']' || c == '}') && (c != expectSymbol);
    }

}
