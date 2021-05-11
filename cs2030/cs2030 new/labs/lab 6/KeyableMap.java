import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

class KeyableMap<T, K, V extends Keyable<K>> implements Keyable<T> {
    private T key;
    private Map<K,V> m;

    public KeyableMap(T t) {
        this.key = t;
        m = new HashMap<>();
    }
    
    public KeyableMap<T,K,V> put(V item) {
       this.m.put(item.getKey(), item);
       return this;  
    }

    public Map<K,V> getMap() {
        return m;
    }

    @Override
    public T getKey() {
        return this.key;
    }

    public Optional<V> get(K key) {
        return Optional.ofNullable(this.m.get(key));
    }

    @Override
    public String toString() {
        return this.key + ": " + this.m.values().toString().replace('[','{').replace(']','}');        
    }   

}
