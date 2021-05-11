/** 
* Main method for working operations.
*
* @author Schubert Goh
*/

// import these cause we will use them
import java.util.Scanner;
import java.util.ArrayList;

class Main {
    
    public static final int ARRIVES = 1;
    public static final int SERVED = 2;
    public static final int LEAVES = 3;

        
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // create an array list to store doubles representing customer times
        ArrayList<Double> list = new ArrayList<Double>();
        
        // loop for as many inputs as user desires
        while (sc.hasNextDouble()) {
            double temp = sc.nextDouble();
            list.add(temp);        
        }
        
        // to keep track of no of ops needed
        int count = list.size();
        
        // create a server which will be used in the method
        Server s = new Server(null);
        
        // as many inputs as entered
        for (int i = 0; i < list.size(); i++) {

            // print arrive statement, custoemr arrives
            Customer c = new Customer(i + 1, list.get(i), ARRIVES);    
            System.out.println(c);
            
            // check if server is free when a new customer arrives
            if (s.canServe(c)) {
                s = s.serve(c); // serve new customer, update status
                System.out.println(c.updateState(SERVED));
            } else {
                // server is busy, so customer leaves, change status to leaves            
                System.out.println(c.updateState(LEAVES));
            }
        }
        
        // no of customers who queued
        System.out.println("Number of customers: " + count);
    }
}
