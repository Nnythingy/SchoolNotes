import java.util.Scanner;

public class Sum {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int no = sc.nextInt();
        int[] val = new int[no];

        for(int i = 0; i < no; i++) {
            int num = sc.nextInt();
            val[i] = sc.nextInt();
        }

        for(int i = 0; i < no; i++) {
            int v = val[i] * (val[i] + 1);
            System.out.println((i+1) + " " + v/2 + " " + (v - val[i]) + " " + v);
        }
    }
}
