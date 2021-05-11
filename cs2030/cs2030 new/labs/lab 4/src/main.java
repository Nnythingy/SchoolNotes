public class main {
    public static void main(String[] args) {
        Box a = Box.of(Box.of(new A())).map(new BoxIt<>());
        System.out.println(a);
    }
}
