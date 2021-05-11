class Cruise {
    private final String name;
    private final int arrTime;
    private final int loaderNo;
    private final int serviceTime;

    public Cruise(String name, int arrTime, int loaderNo, int serviceTime) {
        this.name = name;
        this.arrTime = arrTime;
        this.loaderNo = loaderNo;
        this.serviceTime = serviceTime;

    }

    public String getName() { // for getting string output
        return this.name;
    }

    public int aTime() { // for getting string output
        return this.arrTime;
    }

    public int getNumOfLoadersRequired() {
        return this.loaderNo;
    }

    public int getArrivalTime() {
        return this.arrTime%100 + (this.arrTime/100)*60;
    }

    public int getServiceCompletionTime() {
        return this.getArrivalTime() + this.serviceTime;
    }

    @Override
    public String toString() {
        return this.name + "@" + String.format("%04d",this.arrTime);
    }

}