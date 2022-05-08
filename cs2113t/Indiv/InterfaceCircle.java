public class InterfaceCircle extends InterfaceShape implements InterfacePrintable{
    private int radius;

    public InterfaceCircle(int radius) {
        this.radius = radius;
    }

    @Override
    public int area() {
        return (int)(Math.PI * radius * radius);
    }

    @Override
    public void print() {
        System.out.println("Circle of area " + area());
    }
}
