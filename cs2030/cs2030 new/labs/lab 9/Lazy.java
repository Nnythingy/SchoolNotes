import java.util.function.Predicate;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.Optional;

class Lazy<T> {
    private T t;
    private Supplier<? extends T> supp;
    private boolean isCached;
    
    private Lazy(T t) {
        this.t = t;
        this.isCached = true;
    }

    private Lazy(Supplier<? extends T> s) {
        this.t = t;
        this.isCached = false;
        this.supp = s; 
    }

    public static <T> Lazy<T> ofNullable(T v) {
        return new Lazy<>(v);
    }

    public static <T> Lazy<T> generate(Supplier<? extends T> s) {
        return new Lazy<>(s);
    }

    public Optional<T> get() {
        if (!isCached) {
            this.t = this.supp.get();
            this.isCached = true;
        }    
        return Optional.ofNullable(this.t);
    }

    public Lazy<T> filter(Predicate<? super T> p) {
        return new Lazy<T>(() -> this.get().filter(p).orElse(null));
    }

    public <R> Lazy<R> map(Function<? super T, ? extends R> mapper) {
        return new Lazy<R>(() -> this.get().map(mapper).orElse(null));
    } 
    
    @Override
    public String toString() {
        if (!isCached) {
            return "?";
        } else {
            return "" + t;
        }
    }    
}
