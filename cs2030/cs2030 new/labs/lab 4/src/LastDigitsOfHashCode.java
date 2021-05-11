class LastDigitsOfHashCode implements Transformer<Object, Integer> {
    private final int digits;

    public LastDigitsOfHashCode(int i) {
        this.digits = i;
    }

    @Override
    public Integer transform(Object o) {

        int hash;

        if(o instanceof Integer) {
            String s = o.toString();
            hash = Integer.parseInt(s);
        } else {
            String s = o.toString();
            hash = s.hashCode();
        }

        return Math.abs(hash % (int) Math.pow(10, digits));
    }
}
