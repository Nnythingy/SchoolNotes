/**
 * The AutoServer Class represents a Server who
 * can hold up to one customer that he is serving
 * Also has parameter doneTime, to see when the next customer can be served.
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

public class AutoServer extends Server {

    /**
     * This generates a blank AutoServer.
     * @param id id of this server
     */
    public AutoServer(int id) {
        this.id = id;
        this.curr = null;
        this.doneTime = -1;
    }

    /**
     * This generates an upadted AutoServer.
     * @param id id of this server
     * @param curr a customer to serve
     * @param doneTime a done time
     */
    private AutoServer(int id, Customer curr, double doneTime) {
        this.id = id;
        this.curr = curr;
        this.doneTime = doneTime;
    }

    /**
     * This will create a new server with a new customer.
     * who is being served
     *
     * @param c new customer which server will serve
     * @param time to generate donetime for this server
     * @return return new server serving this new customer
     */
    public AutoServer serve(Customer c, double time) {
        return new AutoServer(this.id, c, time);
    }

    /**
     * returns a server with no customer, removed.
     * @return a server without a curr customer
     */
    public AutoServer clear() {
        return new AutoServer(this.id, null, this.doneTime);
    }

    /**
     * check if this is a human or auto server.
     * @return false, this is not a human server
     */
    @Override
    boolean isHuman() {
        return false;
    }

    /**
     * This will return a boolean determining if server can.
     * serve customer at a certain time.
     *
     * @return return a boolean denoting if server can serve Customer c
     */
    @Override
    public boolean canServe() {
        return this.curr == null;
    }

    // string rep of self check server
    @Override
    public String toString() {
        return "self-check " + this.id;
    }
}
