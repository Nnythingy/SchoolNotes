import java.util.ArrayList;
import java.util.Optional;
import java.util.function.*;


public abstract class InfiniteListImpl<T> implements InfiniteList<T> {

    public static <T> InfiniteListImpl<T> generate(Supplier<? extends T> s) {
        return new InfiniteListImpl<T>() {

            public Optional<T> get() {
                return Optional.ofNullable(s.get());
            }
        };
    }

    public static <T> InfiniteListImpl<T> iterate(T seed, UnaryOperator<T> u) {
        return new InfiniteListImpl<T>() {
            private T element = seed;
            private boolean first = true;

            public Optional<T> get() {
                if(first) {
                    first = false;
                } else {
                    element = u.apply(element);
                }
                return Optional.ofNullable(element);
            }
        };
    }

    public InfiniteList<T> limit(long max) {
        if (max < 0) {
            throw new IllegalArgumentException(Long.toString(max));
        } else {
            return new InfiniteListImpl<>() {
                long lim = max;

                public Optional<T> get() {
                    if (lim > 0) {
                        lim--;
                        return InfiniteListImpl.this.get();
                    } else {
                        return Optional.empty();
                    }
                }
            };
        }
    }

    public void forEach(Consumer<? super T> action) {
        Optional<T> curr = get();
        while (curr.isPresent()) {
            action.accept(curr.get());
            curr = get();
        }
    }

    public Object[] toArray() {
        ArrayList<T> list = new ArrayList<>();

        Optional<T> curr = get();
        while (curr.isPresent()) {
            list.add(curr.get());
            curr = get();
        }

        Object[] arr = list.toArray();
        return arr;

    }

    public <S> InfiniteList<S> map(Function<? super T, ? extends S> mapper) {
        return new InfiniteListImpl<>() {
            public Optional<S> get() {
                return InfiniteListImpl.this.get().map(mapper);
            }
        };
    }

    public InfiniteList<T> filter(Predicate<? super T> predicate) {
        return new InfiniteListImpl<T>() {
            public Optional<T> get() {
                Optional<T> curr = InfiniteListImpl.this.get();
                while(curr.isPresent()) {
                    if (!curr.filter(predicate).isPresent()) {
                        curr = InfiniteListImpl.this.get();
                        continue;
                    } else {
                        return curr.filter(predicate);
                    }
                }
                return curr;
            }
        };
    }

    public InfiniteList<T> takeWhile(Predicate<? super T> predicate) {
        return new InfiniteListImpl<>() {
            boolean pass = true;

            public Optional<T> get() {
                if (pass) {
                    Optional<T> curr = InfiniteListImpl.this.get();

                    if (curr.isPresent()) {
                        if (curr.filter(predicate).isPresent()) {
                            return curr;
                        } else {
                            pass = false;
                            return Optional.empty();
                        }
                    } else {
                        return Optional.empty();
                    }
                } else {
                    return Optional.empty();
                }

            }
        };
    }

    public long count() {
        Optional<T> curr = get();
        long count = 0;
        while (curr.isPresent()) {
            count++;
            curr = get();
        }

        return count;
    }

    public Optional<T> reduce(BinaryOperator<T> accumulator) {
        Optional<T> start = get();
        T total;

        if(start.isPresent()) {
            total = start.get();
        } else {
            return Optional.empty();
        }

        Optional<T> curr = get();

        while(curr.isPresent()) {
            total = accumulator.apply(total, curr.get());
            curr = get();
        }

        return Optional.ofNullable(total);
    }

    public T reduce(T start, BinaryOperator<T> accumulator) {
        T total = start;
        Optional<T> curr = get();

        while(curr.isPresent()) {
            total = accumulator.apply(total, curr.get());
            curr = get();
        }

        return total;
    }

}