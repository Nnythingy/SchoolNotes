/**
* The Server Class represents a server who
* can hold up to one customer that he is serving
* and has a fixed immutable double serveTime of 1.000,
* this means that all customers will take 1.0 time to serve
*
* @author Schubert Goh
*/

class Server {
    private final Customer curr;
    
    /**
     * Generates a new server. 
     * @param c user input of customer that server will serve
     */ 
    public Server(Customer c) {
        this.curr = c;
    }

    /** 
     * Generates a new server with a new customer to replace the old one.
     * @param c user input of customer to serve
     * @return returns a new server serving Customer c
     */
    public Server serve(Customer c) {
        return new Server(c);
    }

    /** 
     * Check if the server can serve new customer given time conditions.
     * @param c user input of custoemryto serve
     * @return returns true if can serve customer,else return false if server is busy
     */
    public boolean canServe(Customer c) {
        if (this.curr == null) {
            return true; 
        } else {
            // check if the next customer can be served when arrives
            return this.curr.getArrTime() + 1.0  <= c.getArrTime();
        }
    }
}
