import java.util.function.UnaryOperator;
import java.util.HashSet;

abstract class IFL<T> {
    /* FIELDS AND METHODS START: DO NOT REMOVE */

    /* FIELDS AND METHODS END: DO NOT REMOVE */

    static <T> IFL<T> iterate(T seed, UnaryOperator<T> next) {
        return new IFL<T>() {
            T element = seed;
            boolean first = true;
            T get() {
                if (first) {
                    first = false;
                } else {
                    element = next.apply(element);
                }
                return element;
            }
        };
    }

    IFL<T> map(UnaryOperator<T> mapper) {
        return new IFL<T>() {
            T get() {
                return mapper.apply(IFL.this.get());
            }
        };
    }

    IFL<T> unique() {
        /* UNIQUE START: DO NOT REMOVE!!! */
return new IFL<T>() {
   T head;
   IFL<T> tail;
   HashSet<T> s = new HashSet<>();
   T get() {
            T t = IFL.this.get();
            return !s.add(t) ? null : t;
         }
};
        /* UNIQUE END: DO NOT REMOVE!!! */
    }

    IFL<T> peek() {
        /* PEEK START: DO NOT REMOVE!!! */
        T t = IFL.this.get();
        if (t != null) {
            System.out.println(t);
        } else {
            System.out.println(IFL.this.get());
        }
return new IFL<T>() {
   T head;
   IFL<T> tail;

   T get() {
       return IFL.this.get();
      }
};
        /* PEEK END: DO NOT REMOVE!!! */
    }
    abstract T get();
}

/* ADDITIONAL CODE START: DO NOT REMOVE */

/* ADDITIONAL CODE END: DO NOT REMOVE */
