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
   
    /**
     * Generates a new Customer object.
     * @param id get customer ide
     * @param arrTime get time that this customer is doing action
     * @param state  get arrival/leaves/done state
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

    /**
     * Generates a new Customer object with upadted state.
     * @param status user input of new customer status
     * @return returns a new Customer with updated state/action 
     */
    public Customer updateState(int status) {
        // return a new customer with updated status    
        return new Customer(this.id, this.arrTime, status);
    }
    
    // this will be printed when customer arrives, is served or leaves
    @Override
    public String toString() {
        String condition = "";

        if (this.state == 1) {
            condition = "arrives";
        } else if (this.state == 2) {
            condition = "served";
        } else {
            condition = "leaves";
        }

        return String.format("%.3f", arrTime) + " " + id + " " + condition;
    }
    
}
