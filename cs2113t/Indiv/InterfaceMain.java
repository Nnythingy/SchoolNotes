public class InterfaceMain {
    public static void printObjects(InterfacePrintable[] items) {
        for (InterfacePrintable p : items) {
            p.print();
        }
    }

    public static void main(String[] args) {
        InterfacePrintable[] printableItems = new InterfacePrintable[]{
                new InterfaceCircle(5),
                new InterfaceRectangle(3, 4),
                new InterfacePerson("James Cook")};

        printObjects(printableItems);
    }
}
