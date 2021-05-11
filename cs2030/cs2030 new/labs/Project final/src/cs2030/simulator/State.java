/**
 * The State Class is an enum.
 * that conatins enum representation of different
 * event states
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

public enum State {
    // list of states
    DONE("done serving by"),
    SERVE("served by"),
    ARRIVE("arrives"), 
    WAIT("waits to be served by"),
    LEAVE("leaves"),
    REST("rests"),
    BACK("back");

    private final String state; // states as strings

    // choose state
    private State(String state) {
        this.state = state;
    }

    // print out event state
    @Override
    public String toString() {
        return this.state;
    }

}