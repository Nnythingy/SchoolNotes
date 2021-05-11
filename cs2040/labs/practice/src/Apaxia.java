import java.util.Scanner;

public class Apaxia {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String input = sc.nextLine();

        for(int i = 0; i < input.length()-1; i++) {
            if(input.charAt(i) == input.charAt(i+1)) {
                input = input.substring(0,i) + input.substring(i+1);
                i--;
            }
        }

        System.out.println(input);
    }
}
