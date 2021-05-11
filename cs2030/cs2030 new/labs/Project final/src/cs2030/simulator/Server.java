/**
 * Abstract class as a base for other server types.
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

public abstract class Server {

    private int id; // for id-ing servers for events
    private Customer curr; // current serving customer
    privatedouble doneTime; // time when the curr will finish

    /**
     * abstract method for serve.
     * @param c customer involved
     * @param time time involved
     * @return nil
     */
    abstract Server serve(Customer c, double time);

    /**
     * abstract method to check if can serve.
     * @return nil
     */
    abstract boolean canServe();

    /**
     * abstract Server method to clear server.
     * @return cleared server
     */
    abstract Server clear();

    /**
     * abstract method to check if its a human or auto server.
     * @return true of false depending on type of server
     */
    abstract boolean isHuman();

    // get id
    public int getId() {
        return this.id;
    }

    // get curr customer
    public Customer getCurr() {
        return curr;
    }

    // get done time
    public double getDoneTime() {
        return doneTime;
    }

}
