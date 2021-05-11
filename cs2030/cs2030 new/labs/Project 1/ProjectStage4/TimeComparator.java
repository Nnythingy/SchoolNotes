/** Comparator takes in 2 Customers
* and sorts them in from shortest time to latest
* To ensure that they are sorted in the final queu during pollinge
*/
import java.util.Comparator;

class TimeComparator implements Comparator<Customer> {
    /** Gets an int to determine placemnet of customers/evnts in the priority queue.
     * @param c1 gets first customer
     * @param c2 gets 2nd customer to comapre to c1
     * @return returns an int to determine placement when adding events to the priority queue
     */
    @Override
    public int compare(Customer c1, Customer c2) {
        if (c1.getArrTime() >= c2.getArrTime()) {
            return 1;
        } else if (c1.getArrTime() < c2.getArrTime()) {
            return -1;
        }

        return 0;
    }    
}
