package util.exceptions;

public class NullException extends Exception {
    public NullException(String obj) {
        System.out.println(String.format("%s is null", obj));
    }
}
