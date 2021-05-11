import java.util.List;
import java.util.ArrayList;

    public class D {
             
        static <T> List<T> add(List<T> list, T t) {
            List<T> newList = new ArrayList<>(list);
            newList.add(t);
            return newList;    
        }
        
        static <T> List<T> join(List<T> list1, List<? extends T> list2) {
            
            List<T> newList = new ArrayList<>(list1);
            List<T> newList2 = new ArrayList<>(list2);     

            if(newList.equals(newList2)) {
                return newList;
            } else {
                newList.addAll(newList2);
            }

            return newList;
        }      
    
   }
