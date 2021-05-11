/**
* Customer class represents a Customer.
* Who has a fixed immutable Arrival time
* and an id, which is determined by his position
* in the queue in the Main() method
*
* 
* @author Schubert Goh
*/

package cs2030.simulator;

public class Customer {
    private final int id;
    private final double arrTime;
   
    /** Generates a new customer object.
     * @param id get customer id
     * @param arrTime get customer arrival time
     */
    public Customer(int id, double arrTime) {
        this.id = id;
        this.arrTime = arrTime;
    }

    // get customer's arrival time for referencing by other classes
    public double getArrTime() {
        return this.arrTime;
    }

    //return customer id
    public int getId() {
        return this.id;
    }

    // this will be printed when customer arrives, is served or leaves
    @Override
    public String toString() {
        return "" + this.id;
    }

}
