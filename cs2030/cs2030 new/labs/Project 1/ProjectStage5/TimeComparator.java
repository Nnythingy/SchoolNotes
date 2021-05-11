/** Comparator takes in 2 Customers
* and sorts them in from shortest time to latest
* To ensure that they are sorted in the final queue during polling
*/
import java.util.Comparator;

class TimeComparator implements Comparator<Customer> {

    /**
     * This will return an int denoting the position to insert a customer in main queue,
     * based on time of event and id (lower ids mean customer who came earlier).
     * @param c1 first customer to compare
     * @param c2 second customer to compare to the first
     * @return an int to determine how the customer should be added to the queue
     */
    @Override
    public int compare(Customer c1, Customer c2) {
        if ((c1.getArrTime() == c2.getArrTime()) && c1.getId() < c2.getId()) {
            return -1; // if times are equal, numvber events based on first come first serve
        } else if ((c1.getArrTime() == c2.getArrTime()) && c1.getId() > c2.getId()) {
            return 1;
        } else if (c1.getArrTime() > c2.getArrTime()) {
            return 1; // number based on time
        } else if (c1.getArrTime() < c2.getArrTime()) {
            return -1; 
        }
        return 0;
    }    
}
