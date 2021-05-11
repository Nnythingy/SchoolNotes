import java.util.Scanner;

public class FizzBuzz {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int x = sc.nextInt();
        int y = sc.nextInt();
        int n = sc.nextInt();

        for(int i = 1; i <= n; i++) {
            String s = "";

            if(i%x == 0) {
                s += "Fizz";
            }
            if(i%y == 0) {
                s += "Buzz";
            }

            if(s.equals("")) {
                System.out.println(i);
            } else {
                System.out.println(s);
            }

        }
    }
}
