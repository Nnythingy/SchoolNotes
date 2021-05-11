import java.util.ArrayList;
import java.util.List;
import java.util.function.Supplier;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.BiFunction;
import java.util.function.Consumer;

class InfiniteListImpl<T> implements InfiniteList<T> {
    private final Lazy<T> head;
    private final Supplier<InfiniteListImpl<T>> tail;

    protected InfiniteListImpl(Lazy<T> head, Supplier<InfiniteListImpl<T>> tail) {
        this.head = head;
        this.tail = tail;
    }

    public static <T> InfiniteListImpl<T> generate(Supplier <? extends T> s) {
        return new InfiniteListImpl<T>(Lazy.generate(s), () -> InfiniteListImpl.generate(s));
    }

    public static <T> InfiniteListImpl<T> iterate(T seed, Function<? super T, ? extends T> next) {
        Lazy<T> newHead = Lazy.ofNullable(seed);
        Supplier<InfiniteListImpl<T>> newTail = () -> InfiniteListImpl.iterate(next.apply(seed), next);
        return new InfiniteListImpl<T>(newHead, newTail);
    }

    public InfiniteListImpl<T> peek() {
        this.head.get().ifPresent(System.out::println);
        return this.tail.get();
    }

    public boolean isEmpty() {
        return false;
    }

    public <R> InfiniteListImpl<R> map(Function<? super T, ? extends R> mapper) {
        Lazy<R> newHead = this.head.map(mapper);
        Supplier<InfiniteListImpl<R>> newTail = () -> this.tail.get().map(mapper);
        return new InfiniteListImpl<R>(newHead, newTail);

    }
    public InfiniteListImpl<T> filter(Predicate<? super T> predicate) {
        Lazy<T> newHead = this.head.filter(predicate);
        Supplier<InfiniteListImpl<T>> newTail = () -> this.tail.get().filter(predicate);
        return new InfiniteListImpl<T>(newHead, newTail);
    }


    public InfiniteListImpl<T> limit(long n) {
        Supplier< InfiniteListImpl<T>> newTail;
        if (n <= 0) {
            return new EmptyList<>();
        } else if (n == 1) {
            newTail = () -> head.get().isPresent() ? new EmptyList<>() : tail.get().limit(1);
        } else {
            newTail = () -> head.get().isPresent() ? tail.get().limit(n - 1) : tail.get().limit(n);
        }
        return new InfiniteListImpl<T>(this.head, newTail);
    }

    public InfiniteListImpl<T> takeWhile(Predicate<? super T> predicate) {
        Lazy<T> newHead = this.head.filter(predicate);
        Supplier<InfiniteListImpl<T>> newTail = () -> newHead.get().isPresent() || this.head.get().isEmpty() ?
            this.tail.get().takeWhile(predicate) : new EmptyList<>();
        return new InfiniteListImpl<T>(newHead, newTail);
    }
    public Object[] toArray() {
        InfiniteListImpl<T> ls = this;
        List<Object> arrList = new ArrayList<>();
        while (!ls.isEmpty()) {
            ls.head.get().ifPresent((x) -> arrList.add(x));
            ls = ls.tail.get();
        }
        return arrList.toArray();
    }

    public long count() {
        InfiniteListImpl<T> ls = this;
        List<Object> arrList = new ArrayList<>();
        long count = 0;
        while (!ls.isEmpty()) {
            if (ls.head.get().isPresent()) {
                count++;
            }
            ls = ls.tail.get();
        }
        return count;
    }

    public <U> U reduce(U identity, BiFunction<U, ? super T, U> accumulator) {
        InfiniteListImpl<T> ls = this;
        while(!ls.isEmpty()) {
            if (ls.head.get().isPresent()) {
                identity  = accumulator.apply(identity, ls.head.get().get());
            }
            ls = ls.tail.get();
        }
        return identity;
    }
    public void forEach(Consumer<? super T> action) {
        InfiniteListImpl<T> ls = this;
        while(!ls.isEmpty()) {
            ls.head.get().ifPresent(action);
            ls = ls.tail.get();
        }
    }


}
