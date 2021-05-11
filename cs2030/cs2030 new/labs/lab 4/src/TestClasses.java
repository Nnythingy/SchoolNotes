public class TestClasses {

}

class AlwaysTrue implements BooleanCondition {
    @Override
    public boolean test(Object o) {
        return true;
    }
}

class AddOne implements Transformer<Integer,Integer> {
     public Integer transform(Integer t) { return t + 1; }
}

class StringLength implements Transformer<String,Integer> {
     public Integer transform(String t) { return t.length(); }
}

class AlwaysNull implements Transformer<Integer,Object> {
    public Object transform(Integer t) { return null; }
}
class A { }


