class LongerThan implements BooleanCondition<String> {
    private final int value;

    public LongerThan(int value) {
        this.value = value;
    }
    @Override
    public boolean test(String s) {
        if(s == null) {
            return false;
        }
        return s.length() > value;
    }

}
