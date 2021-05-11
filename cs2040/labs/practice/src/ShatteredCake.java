import java.util.Scanner;

public class ShatteredCake {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int width = sc.nextInt();
        int noOfPieces = sc.nextInt();

        int cakeVol = 0; // will be counted and summed up

        for(int i = 0; i < noOfPieces; i++) {
            int l1 = sc.nextInt();
            int l2 = sc.nextInt();

            cakeVol += l1*l2;
        }

        System.out.println(cakeVol/width);
    }
}
