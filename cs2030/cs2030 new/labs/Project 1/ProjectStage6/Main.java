/** 
* Main method for working operations.
*
* @author Schubert Goh
*/

import java.util.Scanner;
import java.util.PriorityQueue;
import java.util.ArrayList;

class Main {
    
    // these will track no of served, leaves and average time
    public static int serveCount = 0;
    public static int leaveCount = 0;
    public static double totalWaitTime = 0;

    // List of string name references for customer states
    public static final int ARRIVES = 1;
    public static final int SERVED = 2;
    public static final int WAITS = 3;
    public static final int LEAVES = 4;
    public static final int DONE = 5;

    // create an priority queue to store doubles representing customer times
    public static PriorityQueue<Customer> queue = 
            new PriorityQueue<Customer>(new TimeComparator());

    // create a array;list to store servers, iterate through it for each event
    public static ArrayList<Server> serverList = new ArrayList<Server>();
    // to check if server at index can wait a customer
    public static ArrayList<Boolean> waitCheck = new ArrayList<Boolean>();
        
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int num = sc.nextInt(); // get number of servers
    
        for (int i = 0; i < num; i++) {
            serverList.add(new Server(null)); // that many servers to the list
            waitCheck.add(false); // add that many waitchecks to the list
        }
        
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
        
        String waitTime = ""; // for final average wait time total
        
        // to check for potential null errors
        if (num == 0) {
            waitTime = "0.000";        
        } else {
            waitTime = String.format("%.3f", totalWaitTime / serveCount);
        }    
        // prints out avg wait time,. no of served, no of leaves
        System.out.println("[" + waitTime + " " + serveCount + " " + leaveCount + "]");
    }

    /** 
     * Add event to priority queue based on the most recent event in the queue.
     */
    public static void addEvent() {
        
        Customer curr = queue.poll(); // get and print customer/event at front
        System.out.print(curr); // print this event
        
        // decide what to add
        if (curr.getState() == ARRIVES) { // arrives -> served by waiter or leave

            boolean done = false; // this will check if a customer is assigned or not

            for (int i = 0; i < serverList.size(); i++) {

                Server s = serverList.get(i); // chcek each server in the arraylist

                if (s.canServe(curr)) {   
                    queue.add(curr.updateState(SERVED)); // can get served immediately
                    done = true; // has found a server to serve him
                    break;
                }            
            }
            
            if (!done) {
                for (int i = 0; i < waitCheck.size(); i++) {
                    if (waitCheck.get(i) == false) {
                        queue.add(curr.updateState(WAITS)); // MAKE CUSTOMER WAIT
                        done = true; // has found a server to wait him
                        break;
                    }
                }
            }

            if (!done) {
                queue.add(curr.updateState(LEAVES)); // cannot serve or wait, so customer leaves
                leaveCount++; // customer leaves, so leave count updated    
            }

            System.out.println();

        } else if (curr.getState() == SERVED) {
            // served found, will be done in curr + 1 time 
            Customer serving = curr.updateState(DONE, curr.getArrTime() + 1);    
            queue.add(serving);
            serveCount++;

            int no = 0;

            for (int i = 0; i < serverList.size(); i++) {
                Server s = serverList.get(i);

                if (s.canServe(curr)) { // for waiting customer. update server status
                    serverList.set(i, s.serve(curr)); // make the next avaliable server serve
                    no = i; // record this for determing which server served this customer
                    waitCheck.set(i, false); // now the next customer can wait for him
                    break;   
                }
            }

            System.out.println(" " + (no + 1)); // server number

        } else if (curr.getState() == WAITS) {
            
            // need this for calculations    
            Customer temp = new Customer(0,0,ARRIVES);
            int no = 0; // for determing which serevr waited this customer

            for (int i = 0; i < waitCheck.size(); i++) {
                if (waitCheck.get(i) == false) {
                    waitCheck.set(i, true); // MAKE CUSTOMER WAIT
                    no = i; // server no recorded
                    temp = serverList.get(i).getCurr(); // get customer who's being served ahead
                    break;
                }
            }
            // set wait time for this waiting customer, serving's time will be their done time
            double waitTime = 1 + temp.getArrTime() - curr.getArrTime(); 
            totalWaitTime += waitTime; // add his wait time to total for calculations

            // set a future serve event for this customer 
            queue.add(curr.updateState(SERVED, curr.getArrTime() + waitTime)); 
            System.out.println(" " + (no + 1));  // print out server number 

        } else if (curr.getState() == DONE) {
            int no = 0;

            for (int i = 0; i < serverList.size(); i++) { // find server containing this customer
                if (curr.getId() == serverList.get(i).getCurr().getId()) {
                    no = i; // get id of server
                    break;
                }
            }

            System.out.println(" " + (no + 1)); // print out server number
        
        } else { // for when leaves is encountered
            System.out.println();
        }
    }
}
