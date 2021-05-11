/**
 * The HumanServer Class extends Server who
 * can hold up to one customer that he is serving
 * Also has parameter doneTime, to see when the next customer can be served
 * Server has queue of Customers to serve, with a max size denoted by maxWait
 * Also has boolean to denoting if he is resting, in which case he cannot serve
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

import java.util.LinkedList;
import java.util.Queue;

public class HumanServer extends Server {
    private final Queue<Customer> waiting; // current waiting customer
    private final int maxWait; // max length of waiting queue
    private final boolean resting;

    /**
     * This will create a new blank server object.
     * For initialization
     * @param id id no of the server
     * @param max max number of people that can fit in the queue
     */
    public HumanServer(int id, int max) {
        this.id = id;
        this.curr = null;
        this.doneTime = -1;
        this.waiting = new LinkedList<>();
        this.maxWait = max;
        this.resting = false;
    }

    /**
     * This will create a new updated server object.
     *
     * @param c        customer which server will serve
     * @param w queue of remaining customers who will wait
     * @param max max queue length
     * @param doneTime input time to see ehen the next customer can be served
     * @param id       use same id as prev server
     * @param b for setting resting state
     */
    private HumanServer(Customer c, Queue<Customer> w, int max,
                        double doneTime, int id, boolean b) {
        this.id = id;
        this.curr = c;
        this.doneTime = doneTime;
        this.waiting = w;
        this.maxWait = max;
        this.resting = b;
    }

    /**
     * This will create a new server with a new customer.
     * who is being served
     *
     * @param c new customer which server will serve
     * @param time to generate donetime for this server
     * @return return new server serving this new customer
     */
    @Override
    public HumanServer serve(Customer c, double time) {
        if (!waiting.isEmpty()) { // check if there are customers present in the queue
            Queue<Customer> copy = new LinkedList<>(this.waiting);
            copy.poll();
            return new HumanServer(c, copy, this.maxWait,
                    time, this.getId(), this.resting); // serve the next customer in queue
        } else {
            return new HumanServer(c, new LinkedList<>(), this.maxWait,
                    time, this.getId(), this.resting); // serve customer
        }
    }

    /**
     * This will return a boolean determining if server can.
     * serve customer at a certain time.
     *
     * @return return a boolean denoting if server can serve Customer c
     */
    @Override
    public boolean canServe() {
        if (this.resting) { // cannot serve because the server is resting
            return false;
        }
        return this.getCurr() == null;
    }

    /**
     * returns a server with no customer, removed.
     * @return a server without a curr customer
     */
    @Override
    public HumanServer clear() {
        return new HumanServer(null, this.waiting, this.maxWait,
                this.getDoneTime(), this.getId(), this.resting);
    }

    /**
     * This will create a new server with a new waiting customer.
     *
     * @param c    new customer which server will wait
     * @return return new server waiting this new customer
     */
    public HumanServer wait(Customer c) {
        Queue<Customer> copy = new LinkedList<>(this.waiting);
        copy.add(c);
        return new HumanServer(this.getCurr(), copy, this.maxWait,
                this.getDoneTime(), this.getId(), this.resting);
    }

    /**
     * check if there's space in this server's queue.
     * @return true if there is space (curr spoce < max size), else false
     */
    public boolean canWait() {
        return this.waiting.size() < this.maxWait;
    }

    /**
     * return a server with resting status.
     * @return a server with resting status set to true
     */
    public HumanServer rest() {
        return new HumanServer(this.getCurr(), this.waiting, this.maxWait,
                this.getDoneTime(), this.getId(), true);
    }

    /**
     * return a server who comes back from resting.
     * @return a server with resting status set to false, denoting he's ready to serve
     */
    public HumanServer back() {
        return new HumanServer(this.getCurr(), this.waiting, this.maxWait,
                this.getDoneTime(), this.getId(), false);
    }

    /**
     * return the next customer in the waiting queue.
     * @return the customer in the front of the queue
     */
    public Customer getNext() {
        if (this.waiting.isEmpty()) {
            return null;
        }
        return this.waiting.peek();
    }

    /**
     * return thr length of this waiting queue.
     * @return length of the customer queue
     */
    public int getQLength() {
        return this.waiting.size();
    }

    /**
     * check if this is a human or auto server.
     * @return true, this is a human server
     */
    @Override
    public boolean isHuman() {
        return true;
    }

    @Override
    public String toString() {
        return "server " + this.getId();
    }

}