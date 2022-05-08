package util.exceptions;

public class WrongCommandException extends Exception {
    String command;
    boolean isCommand;

    public WrongCommandException(String command, boolean isCommand) {
        this.command = command;
        this.isCommand = isCommand;
    }

    public boolean isCommand() {
        return isCommand;
    }

    public String getCommand() {
        return command;
    }
}
