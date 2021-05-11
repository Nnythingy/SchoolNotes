class Loader {
    protected final int num;
    protected final Cruise c;

    public Loader(int num, Cruise c) {
        this.num = num;
        this.c = c;
    }

    public Loader(int num) {
        this.num = num;
        this.c = null;
    }

    public Loader serve(Cruise cru) {
        if(canServe(cru)) {
            return new Loader(this.num, cru);
        }
        return null;
    }

    public boolean canServe(Cruise cru) {
        if(this.c == null) {
            return true;
        } else {
            return this.c.getServiceCompletionTime() <= cru.getArrivalTime();
        }
    }

    @Override
    public String toString() {
        String print = "Loader " + this.num;

        if(this.c != null) {
            print += " serving " + c.getName() + "@"
                    + String.format("%04d",c.aTime());
        }

        return print;
    }
}