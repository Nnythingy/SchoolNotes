public class Week5Main {
    private static Week5Shape[] shapes = new Week5Shape[100];
    private static int shapeCount = 0;

    public static void addShape(Week5Shape s){
        shapes[shapeCount] = s;
        shapeCount++;
    }

    public static void printAreas(){
        for (int i = 0; i < shapeCount; i++){
            shapes[i].print();
        }
    }

    public static void main(String[] args) {
        addShape(new Week5Circle(5));
        addShape(new Week5Rectangle(3, 4));
        addShape(new Week5Circle(10));
        addShape(new Week5Rectangle(4, 4));
        printAreas();
    }
}
