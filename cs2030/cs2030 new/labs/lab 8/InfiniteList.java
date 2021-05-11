import java.util.ArrayList;
import java.util.Optional;
import java.util.function.*;

interface InfiniteList<T> {
    public Optional<T> get();

    public static <T> InfiniteList<T> generate(Supplier<? extends T> s) {
       return InfiniteListImpl.generate(s);
    }

    public static <T> InfiniteList<T> iterate(T seed, UnaryOperator<T> u) {
        return InfiniteListImpl.iterate(seed, u);
    }

    public InfiniteList<T> limit(long max);

    public void forEach(Consumer<? super T> action);

    public Object[] toArray();

    public <S> InfiniteList<S> map(Function<? super T, ? extends S> mapper);

    public InfiniteList<T> filter(Predicate<? super T> predicate);

    public InfiniteList<T> takeWhile(Predicate<? super T> predicate);

    public long count();

    public Optional<T> reduce(BinaryOperator<T> accumulator);

    public T reduce(T start, BinaryOperator<T> accumulator);
}
