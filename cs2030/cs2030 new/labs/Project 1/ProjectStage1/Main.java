import java.util.ArrayList;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        ArrayList<Double> list = new ArrayList<Double>();

        while (sc.hasNextDouble()) {
            double temp = sc.nextDouble();
            list.add(temp);        
        }
        
        int count = list.size();

        for (int i = 0; i < list.size(); i++) {
            System.out.println(new Customer(i + 1, list.get(i)));
        }
        
        System.out.println("Number of customers: " + count);
    }
}
