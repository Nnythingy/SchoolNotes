class DivisibleBy implements BooleanCondition<Integer> {
    private final int value;

    public DivisibleBy(int value) {
        this.value = value;
    }

    @Override
    public boolean test(Integer i) {
        if(i == null) {
            return false;
        }
        return i % value == 0;
    }

}