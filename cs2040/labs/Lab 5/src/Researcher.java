public class Researcher {
    private final int arrTime;
    private final int leaveTime;
    private final int lockoutTime;

    // create researcher
    public Researcher(int arrTime, int leaveTime, int lockoutTime) {
        this.arrTime = arrTime;
        this.leaveTime = leaveTime;
        this.lockoutTime = lockoutTime;
    }
    // arr time
    public int getArrTime() {
        return this.arrTime;
    }
    // leave time
    public int getLeaveTime() {
        return this.leaveTime;
    }

    // lock time
    public int getLockoutTime() {
        return this.lockoutTime;
    }


}
