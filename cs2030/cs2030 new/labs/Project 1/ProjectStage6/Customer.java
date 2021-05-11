/**
* Customer class represents a Customer.
* Who has a fixed immutable Arrival time
* and an id, which is determined by his position
* in the queue in the Main() method
* 
* <p>Customer also has a number status to tell if he arrived, is served
* or is leaving
* 
* @author Schubert Goh
*/

class Customer {
    private final int id;
    private final double arrTime;
    private final int state; // state is a number that denotes customer arrived, served or leaves
   
    /** Generates a new customer object.
     * @param id input customer id
     * @param arrTime get customer arrival time
     * @param state get the status of the current customer
     */
    public Customer(int id, double arrTime, int state) {
        this.id = id;
        this.arrTime = arrTime;
        this.state = state;
    }

    // get customer's arrival time for referencing by other classes
    public double getArrTime() {
        return this.arrTime;
    }

    // return a customers state to check what to do with him
    public int getState() {
        return this.state;
    }

    //return customer id
    public int getId() {
        return this.id;
    }
    
    /** Generates a new customer with updated status.
     * @param status get a new status for the customer
     * @return returns a new customer with this updated status
     */
    public Customer updateState(int status) {
        // return a new customer with updated status    
        return new Customer(this.id, this.arrTime, status);
    }
    
    /** Generates a new customer with updated status and time for when he is done.
     * @param status get a new status for the customer
     * @param time get a new time for this customer at this status
     * @return returns a new customer with this updated status
     */
    public Customer updateState(int status, double time) {
        // return a new customer with updated status and time only when his is done  
        return new Customer(this.id, time, status);
    }

    
    // this will be printed when customer arrives, is served or leaves
    @Override
    public String toString() {
        String condition = "";

        if (this.state == 1) {
            condition = "arrives";
        } else if (this.state == 2) {
            condition = "served by";
        } else if (this.state == 3) {
            condition = "waits to be served by";
        } else if (this.state == 4) {
            condition = "leaves";
        } else {
            condition = "done serving by";
        }

        return String.format("%.3f", arrTime) + " " + id + " " + condition;
    }
    
}
