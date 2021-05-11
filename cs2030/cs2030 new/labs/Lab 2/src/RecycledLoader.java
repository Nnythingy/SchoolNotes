public class RecycledLoader extends Loader {

    public RecycledLoader(int num, Cruise c) {
        super(num, c);
    }

    @Override
    public boolean canServe(Cruise cru) {
        if(this.c == null) {
            return true;
        } else {
            return this.c.getServiceCompletionTime() + 60 <= cru.getArrivalTime();
        }
    }

    public RecycledLoader serve(Cruise cru) {
        if(canServe(cru)) {
            return new RecycledLoader(this.num, cru);
        }
        return null;
    }

    @Override
    public String toString() {
        String print = "Loader " + this.num + " (recycled)";

        if(this.c != null) {
            print += " serving " + c.getName() + "@"
                    + String.format("%04d",c.aTime());
        }

        return print;
    }
}
