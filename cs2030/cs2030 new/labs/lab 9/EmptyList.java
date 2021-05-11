public class EmptyList<T> extends InfiniteListImpl<T> {

    public EmptyList() {
        super(Lazy.ofNullable(null), () -> new EmptyList<T>());
    }

    @Override
    public boolean isEmpty() {
        return true;
    }

    @Override
    public EmptyList<T> limit(long n) {
        return new EmptyList<>();
    }
}