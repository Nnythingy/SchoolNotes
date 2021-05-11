import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

interface TypeCaster<S,T>{
    public T cast (S s);
}

class ToString<S> implements TypeCaster<S,String>{
    public String cast(S s){
         return s.toString();
    }
}

class Round implements TypeCaster<Double,Integer>{
    public Integer cast(Double d){
        return (int)Math.round(d);
    }
}

class ToList<T> implements TypeCaster<T[], List<T>>{
    public List<T> cast(T[] arr){
         List<T> list = Arrays.asList(arr);
         return list;
    }
}

class ListCaster{
    public static <S, T> List<T> castList(List<S> s, TypeCaster<S,T> tc){
        List<T> newList = new ArrayList<>();
        for (S thing:s){
          newList.add(tc.cast(thing));
        }
        return newList;
    }
}