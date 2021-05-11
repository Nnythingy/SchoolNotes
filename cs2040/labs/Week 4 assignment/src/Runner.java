class Runner {
    private final String name;
    private final double firstLegTime;
    private final double otherLegTime;

    public Runner(String name, double firstTime, double otherTime) {
        this.name = name;
        this.firstLegTime = firstTime;
        this.otherLegTime = otherTime;
    }

    public double getFirstTime() {
        return this.firstLegTime;
    }

    public double getOtherLegTime() {
        return this.otherLegTime;
    }

    public String getName() {
        return name;
    }

}
