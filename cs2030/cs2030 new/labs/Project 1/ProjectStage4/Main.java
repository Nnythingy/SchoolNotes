/** 
* Main method for working operations.
*
* @author Schubert Goh
*/

import java.util.Scanner;
import java.util.PriorityQueue;
import java.util.Iterator;

class Main {
    
    // need just one server for the whole instance    
    public static Server s = new Server(null);

    // List of string name references for customer states
    public static final int ARRIVES = 1;
    public static final int SERVED = 2;
    public static final int LEAVES = 3;
    public static final int DONE = 4;

    // create an array list to store doubles representing customer times
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
        
        // for final statement
        int count = queue.size();

        //print out prior arrival statement of arrivals
        System.out.println("# Adding arrivals");
        
        // use Iterator to scan through the quue and print out elemnts in order
        Iterator<Customer> preItr = queue.iterator();
        while (preItr.hasNext()) {
            System.out.println(preItr.next());
        }
        System.out.println();
                   
        while (!queue.isEmpty()) {
            // this adds an event to the queuei
            addEvent();
        }

        // no of customers who queued
        System.out.println("Number of customers: " + count);
    }

    /** 
     * This method will add customer events to the priority queue based on the latest event.
     */
    public static void addEvent() {
        
        // add top customer to the front of queue    
        Customer curr = queue.poll();    
        System.out.println("# Get next event: " + curr);
        
        // decide what to add
        if (curr.getState() == ARRIVES) { // arrives -> served by waiter or leave
            if (!s.canServe(curr)) {
                queue.add(curr.updateState(LEAVES)); // cannot serve when arrive, leave
            } else {
                s = s.serve(curr);    
                queue.add(curr.updateState(SERVED)); // can get servedr
            }
        } else if (curr.getState() == SERVED) {
            // served found, will be done in curr + 1 time 
            queue.add(curr.updateState(DONE, curr.getArrTime() + 1));        
        }
        
        // this below will make a copy of array and poll the Cuastomers in the correct order
        PriorityQueue<Customer> temp =  new PriorityQueue<Customer>(queue); 

        while (!temp.isEmpty()) {
            Customer i = temp.poll(); // remove and print the priority customer
            System.out.println(i);
        }
        System.out.println(); // add a line space after aech update

    }
}
