class Box<O> {
    private final O o;
    private static Box<?> EMPTY_BOX = new Box<>(null);

    private Box(O o) {
        this.o = o;
    }

    public static <O> Box<O> of(O o) {
        if(o == null) {
            return null;
        } else {
            return new Box<>(o);
        }
    }

    public O get() {
        return o;
    }

    public static <O> Box<O> empty() {
        @SuppressWarnings("unchecked")
        Box<O> box = (Box<O>) EMPTY_BOX;
        return box;
    }

    public boolean isPresent() {
        return this.o != null;
    }

    public static <O> Box<O> ofNullable(O o) {
        if(o == null) {
            return Box.empty();
        } else {
            return new Box<>(o);
        }
    }

    public Box <O> filter(BooleanCondition<? super O> t) {
        boolean check = t.test(this.get());

        if(!check) {
            return Box.empty();
        } else {
            return this;
        }
    }

    public <U> Box<U> map(Transformer<? super O, U> t) {
        if (this.o == null) {
            return empty();
        } else {
            return new Box<U>(t.transform(this.o));
        }
    }

    @Override
    public boolean equals(Object other) {
        if(this == other) {
            return true;
        } else if (this.get() == null) {
            return false;
        } else if (other instanceof Box) {
            Box<?> box = (Box<?>) other;
            return this.get().equals(box.get());
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        if(o == null) {
            return "[]";
        } else {
            return "[" + o + "]";
        }
    }
}