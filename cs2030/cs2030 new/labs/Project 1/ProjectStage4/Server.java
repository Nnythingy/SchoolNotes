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
     * Creates a new server. 
     * @param c gets a customer for the server
     */ 
    public Server(Customer c) {
        this.curr = c;
    }

    /**
     * Creates a new server with a new customer.
     * @param c gets a new customer for the server
     */ 
    public Server serve(Customer c) {
        return new Server(c);
    }

    /**
     * Determines if at current time, can server serve a new customer.
     * @param c getss acustomer to serve
     * @return returns boolean denoting if Customer c can be served
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
