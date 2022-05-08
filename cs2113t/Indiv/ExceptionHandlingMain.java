public class ExceptionHandlingMain {
    public static void printArea(String descriptor){
        //TODO: modify the code below
        try {
            System.out.println(descriptor + "=" + calculateArea(descriptor));
        } catch (NumberFormatException e) {
            System.out.println("WIDTH or HEIGHT is not a number: " + descriptor);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("WIDTH or HEIGHT is missing: " + descriptor);
        } catch (ExceptionHandlingIllegalShapeException e) {
            System.out.println("Too many dimensions: " + descriptor);
        }
    }

    private static int calculateArea (String descriptor) throws ExceptionHandlingIllegalShapeException {
        //TODO: modify the code below
        String[] dimensions = descriptor.split("x");
        if (dimensions.length > 2) {
            throw new ExceptionHandlingIllegalShapeException();
        }
        return Integer.parseInt(dimensions[0]) * Integer.parseInt(dimensions[1]);
    }

    public static void main(String[] args) {
        printArea("3x4");
        printArea("5x5");
        printArea("3xy");
        printArea("3x");
        printArea("3");
        printArea("3x4x5");
    }
}
