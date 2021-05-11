import java.util.Arrays;

public class Test {
    public static void main(String[] args) {

        String s = "Jack   CS2040 Lab4";

        String[] temp = s.split("\\s+");
        System.out.println(Arrays.toString(temp));
    }
}
