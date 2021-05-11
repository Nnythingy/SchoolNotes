class Customer {
    private final int id;
    private final double arrTime;

    /** 
     * Method for instanitiating a new Customer/Event.
     * @param id users's input
     * @param arrTime user's input
     * @return instance of customer
     */
    public Customer(int id, double arrTime) {
        this.id = id;
        this.arrTime = arrTime;
    }

    /** 
     * Method to return Customer information as a String.
     * @return customer arrival statement
     */
    @Override
    public String toString() {
        return id + " arrives at " + String.format("%.3f", arrTime);
    }
    
}
