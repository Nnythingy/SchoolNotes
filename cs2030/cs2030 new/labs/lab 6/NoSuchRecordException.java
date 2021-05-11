public class NoSuchRecordException extends Exception {
    public NoSuchRecordException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "NoSuchRecordException: " + this.getMessage();
    }
}
