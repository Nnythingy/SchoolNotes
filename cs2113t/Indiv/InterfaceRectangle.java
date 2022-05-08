public class InterfaceRectangle extends InterfaceShape implements InterfacePrintable {
    private int height;
    private int width;

    public InterfaceRectangle(int height, int width){
        this.height = height;
        this.width = width;
    }

    @Override
    public int area() {
        return height * width;
    }

    @Override
    public void print() {
        System.out.println("InterfaceRectangle of area " + area());
    }
}
