import java.util.function.Function;
import java.util.function.Predicate;

class Result<T> {
   private T t;
   private String state;
   private String err;
   private Result (T t, String s, String e) {
         this.t = t;
         this.state = s;
         this.err = e;
   }
   T get() {
      return this.t;
   }
   static <T> Result<T> success(T value) {
           return new Result<>(value, "Success:", null);
     } 
   
     static <T> Result<T> error(String error) {
           return new Result<>(null, "Error:", error);
     } 
 
      @Override
      public String toString() {
        if(t != null) {
            return state + " " + t;
        }
            return state + " " + err;

      }
 
      Result filter(Predicate<? super T> p, String err) {
               if (t != null && !p.test(t)) {
                  return Result.error(err);
               } else {
                    return this;
               }
      }
 
      <S> Result<S> flatMap(Function<? super T, ? extends Result<S>> map) {
               if (state.equals("Error:")) {
                     return Result.error(err);
               } else {
                     try {
                         return map.apply(t);
                     } catch (Exception e) {
                        return Result.error(e.toString());
                     }
}
         }


     T orElseThrow(Exception e) throws Exception {
       if (this.state.equals("Success:")) {
              return this.t;
        } else {
               throw e;
        }

      }
 
}
