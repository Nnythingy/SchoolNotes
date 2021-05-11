/**
 * GreedyCustomer class represents a GreedyCustomer.
 * Who has a fixed immutable Arrival time
 * and an id, which is determined by his position
 * in the queue in the Main() method
 * Greedy customer will always choose the shortest queue available if he has to wait
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

public class GreedyCustomer extends Customer {
    /**
     * Generates a new greedy customer object.
     *
     * @param id      get customer id
     * @param arrTime get customer arrival time
     */
    public GreedyCustomer(int id, double arrTime) {
        super(id, arrTime);
    }

    @Override
    public String toString() {
        return "" + this.getId() + "(greedy)";
    }
}
