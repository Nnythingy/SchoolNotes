import java.util.Arrays;
import java.util.Scanner;

public class Skener {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int r = Integer.parseInt(sc.next());
        int c = Integer.parseInt(sc.next());

        String[] lines = new String[r];

        int mulR = Integer.parseInt(sc.next());
        int mulC = Integer.parseInt(sc.next());

        for(int i = 0; i < r; i++) {
            lines[i] = "**--**";
        }

//        for(int i = 0; i < r; i++) {
//            String tempStr = "";
//            for(int j = 0; j < lines[i].length(); j++) {
//                for(int k = 0; k < mulC; k++) {
//                    tempStr += lines[i].charAt(j);
//                }
//            }
//            lines[i] = tempStr;
//        }

        System.out.println(Arrays.toString(lines));

    }
}
