/** 
* Main method for working operations.
*
* @author Schubert Goh
*/

import java.util.Scanner;
import java.util.PriorityQueue;

class Main {
    
    // need just one server for the whole instance    
    public static Server s = new Server(null);

    // these will track no of served, leaves and average time
    public static int serveCount = 0;
    public static int leaveCount = 0;
    public static double totalWaitTime = 0;

    // update latest customer being served
    public static Customer serving = null;    
    public static boolean someoneWaiting = false; // used to check if anyone is waiting  

    // List of string name references for customer states
    public static final int ARRIVES = 1;
    public static final int SERVED = 2;
    public static final int WAITS = 3;
    public static final int LEAVES = 4;
    public static final int DONE = 5;

    // create an priority queue to store doubles representing customer times
    public static PriorityQueue<Customer> queue = 
            new PriorityQueue<Customer>(6, new TimeComparator());
        
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
    
        // startIndex for indexing customers
        int startIndex = 1;
                
        // loop for as many inputs as user desires, 
        // create a new indexed customer to add to the queue
        while (sc.hasNextDouble()) {
            double temp = sc.nextDouble();
            queue.add(new Customer(startIndex, temp, ARRIVES));
            startIndex++;        
        }
            
        while (!queue.isEmpty()) {   
            // this adds an event to the queue   
            addEvent();
        }

        // prints out avg wait time,. no of served, no of leaves
        System.out.println("[" + String.format("%.3f", totalWaitTime / serveCount) + " " +
                       serveCount + " " + leaveCount + "]");
    }

    /** 
     * Add event to priority queu based on the most recent event in the queue.
     */
    public static void addEvent() {
        
        Customer curr = queue.poll(); // get and print customer/event at front
        System.out.println(curr); // print this event
        
        // decide what to add
        if (curr.getState() == ARRIVES) { // arrives -> served by waiter or leave
            if (s.canServe(curr)) {
                s = s.serve(curr);    
                queue.add(curr.updateState(SERVED)); // can get served immediately

            } else if (!someoneWaiting) {
                queue.add(curr.updateState(WAITS)); // there is no one waiting in front
                someoneWaiting = true;    
            
            } else {
                queue.add(curr.updateState(LEAVES)); // cannot serve when arrive, leave 
                leaveCount++;
            }    

        } else if (curr.getState() == SERVED) {
            // served found, will be done in curr + 1 time 
            serving = curr.updateState(DONE, curr.getArrTime() + 1);    
            queue.add(serving);
            serveCount++;

            if (s.canServe(curr)) { // for waiting customer. update server status
                s = s.serve(curr);   
            }

            someoneWaiting = false; // server serves this customer, so nest customer can wait

        } else if (curr.getState() == WAITS) {
            // set wait time for this waiting customer, serving's time will be their done time
            double waitTime = serving.getArrTime() - curr.getArrTime(); 
            totalWaitTime += waitTime; // add his wait time to total for calculations

            // set a future serve event for this customer 
            queue.add(curr.updateState(SERVED, curr.getArrTime() + waitTime));    
        }
    }
}
