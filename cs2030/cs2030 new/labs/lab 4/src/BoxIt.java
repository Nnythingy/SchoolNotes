public class BoxIt<Object> implements Transformer<Object, Box<Object>> {
    @Override
    public Box<Object> transform(Object o) {
        return Box.of(o);
    }
}
