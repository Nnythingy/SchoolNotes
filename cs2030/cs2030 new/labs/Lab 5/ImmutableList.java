import java.util.*;
import java.util.function.Predicate;
import java.util.function.*;
import java.util.Comparator;
import java.lang.Comparable;
import java.lang.reflect.Array;

class ImmutableList<T> {
        
    private final List<T> list;

    public ImmutableList(List<T> other) {
        this.list = List.copyOf(other);
    }

    @SafeVarargs
    public ImmutableList(T... items) {
        List<T> temp = new ArrayList<>(items.length);

        for(T i: items) {
            temp.add(i);
        }

        this.list = temp;
    }

    public ImmutableList<T> add(T t) {
        List<T> newList = new ArrayList<>(this.list);
        newList.add(t);

        return new ImmutableList<T>(newList);
    }

    public ImmutableList<T> remove(T t) {
        List<T> newList = new ArrayList<>(this.list);
        newList.remove(t);

        return new ImmutableList<T>(newList);
    }
    
    public ImmutableList<T> replace(T t, T u) {
        List<T> newList = new ArrayList<>(this.list);
        Collections.replaceAll(newList, t, u);

        return new ImmutableList<T>(newList);
    }

    public ImmutableList<T> filter(Predicate<? super T> p) {
        List<T> newList = new ArrayList<>();
         
        for(T i: this.list) {
            if(p.test(i)) {
                newList.add(i);
            }
        }

        return new ImmutableList<T>(newList);
    }

    public <R> ImmutableList<R> map(Function<? super T, ? extends R> fun) {
        List<R> newList = new ArrayList<>();

        for(T i: this.list) {
            newList.add(fun.apply(i));
        }

        return new ImmutableList<R>(newList);
    }

    public ImmutableList<T> limit(long newSize) {
        
        if (newSize < 0) {
            throw new IllegalArgumentException("limit size < 0");       
        } else {
            List<T> newList = new ArrayList<>(this.list);
            long oldSize = newList.size();

            for(int i = 0; i < oldSize - newSize; i++) {
                newList.remove(newList.size() - 1);    
            }

            return new ImmutableList<T>(newList);
        }    
    }
    
    public ImmutableList<T> sorted() {
    
        for(T i: this.list) {
            if(!(i instanceof Comparable)) {
                throw new IllegalStateException("List elements do not implement Comparable");
            }
        }

        List<T> newList = new ArrayList<>();
        for(T i : this.list) {
            newList.add(i);
        }
        newList.sort(null);
        return new ImmutableList<T>(newList);

    }

    public ImmutableList<T> sorted(Comparator<T> com) {
        
        if (com == null) {
            throw new NullPointerException("Comparator is null");
        }  

        List<T> newList = new ArrayList<>();

        for (T i : this.list) {
            newList.add(i);        
        }

        newList.sort(com);
        return new ImmutableList<T>((List<T>) newList);            
    }

    public Object[] toArray() {
        Object[] array = this.list.toArray();
        return array;
    }

    public <U> U[] toArray(U[] array) {
       
        try {
            return this.list.toArray(array);

        } catch (ArrayStoreException e) {
            throw new ArrayStoreException("Cannot add element to array as " +
                            "it is the wrong type");

        } catch (NullPointerException n) {
            throw new NullPointerException("Input array cannot be null");  
        }
               
    }

    @Override
    public String toString() {
        return this.list.toString();    
    }

}
