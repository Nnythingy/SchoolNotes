/**
* The Server Class represents a server who
* can hold up to one customer that he is serving
* and has a fixed immutable double serveTime of 1.000,
* this means that all customers will take 1.0 time to serve
*
* @author Schubert Goh
*/

class Server implements  {
    private final Customer curr;
    
    /** This will create a new server object.
     * @param c customer which server will serve
     */
    public Server(Customer c) {
        this.curr = c;
    }

    /** This will create a new server with a new customer.
     * @param c new customer which server will serve
     * @return return new server serving this new customer
     */
    public Server serve(Customer c) {
        return new Server(c);
    }

    /** This will return a boolean determining if server can 
     * serve customer at a certain time.
     * @param c new customer to test if server can serve
     * @return return a boolean denoting if server can serve Customer c
     */ 
    public boolean canServe(Customer c) {
        if (this.curr == null) {
            return true; 
        } else {
            // check if the next customer can be served when arrives
            return this.curr.getArrTime() + 1.0  <= c.getArrTime();
        }
    }

    public Customer getCurr() {
        return this.curr;
    }
}
