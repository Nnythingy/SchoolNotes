class SmallCruise extends Cruise {

    private static final int LOADERNO = 1;
    private static final int SERVICETIME = 30;

    public SmallCruise(String name, int arrTime) {
        super(name, arrTime, LOADERNO, SERVICETIME);
    }
}
