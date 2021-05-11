class BigCruise extends Cruise {

    private static final int LOADERFACTOR = 40;
    private static final int SERVICESPEED = 50;

    public BigCruise(String name, int arrTime, int length, int passengerNo) {
        super(name, arrTime, (length + LOADERFACTOR - 1)/LOADERFACTOR,
                (passengerNo + SERVICESPEED - 1)/SERVICESPEED );
    }
}
