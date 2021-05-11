/**
 * The event Class is a combination
 * of a time a customer, server and state
 * that shows an evnt at a specific point in time.
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

import java.lang.Comparable;

public class Event implements Comparable<Event> {
    private final Customer c;
    private final Server s;
    private final double time;
    private final State state;

    /** This will craete a new event with server (SERVE, WAIT, DONE).
     *
     * @param c customer involved
     * @param s server involved
     * @param time time this took palce
     * @param state whats happening
     */
    public Event(Customer c, Server s, double time, State state) {
        this.c = c;
        this.s = s;
        this.time = time;
        this.state = state;
    }

    // get state

    public State getState() {
        return this.state;
    }
    //get time

    public double getTime() {
        return this.time;
    }
    // get customer

    public Customer getCustomer() {
        return this.c;
    }
    //get server

    public Server getServer() {
        return s;
    }

    // return event as a string
    @Override
    public String toString() {
        String output = String.format("%.3f ",this.time) + c + " " + this.state;

        if (this.s != null) {
            output +=  " " + s;
        }
        return output;
    }

    /** Returns an int which represents the priority of an event in a queue.
     *
     * @param other another event to comapre to
     * @return an int which shows what priority the int has in a pq
     */
    @Override
    public int compareTo(Event other) {
        if (this.time > other.time) { // prioritize by time
            return 1;
        }

        if (this.time < other.time) {
            return -1;
        }

        if (this.c.getId() > other.c.getId()) { // prioritize by state
            return 1;
        }

        if (this.c.getId() < other.c.getId()) {
            return -1;
        }
        
        return 0;
    }
}