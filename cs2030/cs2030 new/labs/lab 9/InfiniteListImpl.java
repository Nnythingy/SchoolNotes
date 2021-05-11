import java.util.ArrayList;
import java.util.Optional;
import java.util.function.*;


class InfiniteListImpl<T> implements InfiniteList<T> {

    private final Lazy<T> head;
    private final Supplier<InfiniteListImpl<T>> tail;

    protected InfiniteListImpl(Lazy<T> head, Supplier<InfiniteListImpl<T>> tail) {
        this.head = head;
        this.tail = tail;
    }

    public static <T> InfiniteListImpl<T> generate(Supplier<? extends T> s) {
        return new InfiniteListImpl<T>(
                Lazy.generate(s),
                () -> InfiniteListImpl.generate(s)
        );
    }

    public static <T> InfiniteListImpl<T> iterate(T seed, UnaryOperator<T> next) {
        return new InfiniteListImpl<T>(
                Lazy.ofNullable(seed),
                () -> InfiniteListImpl.iterate(next.apply(seed), next)
        );
    }

    public boolean isEmpty() {
        return false;
    }

    public InfiniteListImpl<T> peek() {
        this.head.get().ifPresent(System.out::println);
        return this.tail.get();
    }

    public <S> InfiniteListImpl<S> map(Function<? super T, ? extends S> mapper) {
        if (this.isEmpty()) {
            return new EmptyList<S>();
        } else {
            return new InfiniteListImpl<S>(
                    this.head.map(mapper),
                    () -> this.tail.get().map(mapper)
            );
        }
    }

    public InfiniteListImpl<T> filter(Predicate<? super T> p) {
        if (this.isEmpty()) {
            return new EmptyList<T>();
        } else {
            return new InfiniteListImpl<T>(
                    this.head.filter(p),
                    () -> this.tail.get().filter(p)
            );
        }
    }

    public InfiniteListImpl<T> limit(long n) {
        Supplier< InfiniteListImpl<T>> newTail;
        if (n <= 0) {
            return new EmptyList<>();
        } else if (n == 1) {
            newTail = () -> head.get().isPresent()
                    ? new EmptyList<>() : tail.get().limit(1);
        } else {
            newTail = () -> head.get().isPresent()
                    ? tail.get().limit(n - 1) : tail.get().limit(n);
        }
        return new InfiniteListImpl<T>(this.head, newTail);
    }

    public InfiniteListImpl<T> takeWhile(Predicate<? super T> predicate) {
        Lazy<T> newHead = this.head.filter(predicate);
        Supplier<InfiniteListImpl<T>> newTail = () -> newHead.get().isPresent() || this.head.get().isEmpty()
                ? this.tail.get().takeWhile(predicate) : new EmptyList<>();
        return new InfiniteListImpl<T>(newHead, newTail);
    }

//    public InfiniteListImpl<T> takeWhile(Predicate<? super T> predicate){
//        if(this.isEmpty()) {
//            return new InfiniteListImpl<>(head,() ->this.tail.get().takeWhile(predicate)) ;
//        }
//        Lazy<T> newHead = this.head.filter(predicate);
//        Supplier<InfiniteListImpl<T>> newTail = () -> (
//                newHead.get() != Optional.empty() ?
//                this.tail.get().takeWhile(predicate) : new EmptyList<>());
//
//        return new InfiniteListImpl<>(newHead,newTail);
//    }

    public Object[] toArray(){
        ArrayList<T> arr = new ArrayList<T>();
        InfiniteListImpl<T> cur = this;
        while (!cur.isEmpty()){
            T toGet = cur.head.get().orElse(null);
            if (toGet != null){
                arr.add(toGet);
            }
            cur = cur.tail.get();
        }
        return arr.toArray();
    }

    public long count() {
        long total = 0;
        InfiniteListImpl<T> cur = this;

        while (!cur.isEmpty()) {
            T toGet = cur.head.get().orElse(null);
            if (toGet != null) {
                total++;
            }
            cur = cur.tail.get();
        }
        return total;
    }

    public void forEach(Consumer<? super T> action) {
        InfiniteListImpl<T> cur = this;
        while (!cur.isEmpty()) {
            T toGet = cur.head.get().orElse(null);
            if (toGet != null) {
                action.accept(toGet);
            }
            cur = cur.tail.get();
        }
    }

    public <U> U reduce (U identity, BiFunction<U, ? super T, U> accumulator) {
        U result = identity;
        InfiniteListImpl<T> cur = this;

        while (!cur.isEmpty()) {
            T toGet = cur.head.get().orElse(null);
            if (toGet != null) {
                result = accumulator.apply(result, toGet);
            }
            cur = cur.tail.get();
        }
        return result;
    }


}
