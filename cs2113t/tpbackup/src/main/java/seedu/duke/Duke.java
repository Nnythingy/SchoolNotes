package seedu.duke;

import util.exceptions.NullException;

import java.util.Scanner;

/**
 * Main entry-point for the java.duke.Duke application.
 */
public class Duke {
    public static void hello() {
        String logo = "Simplst";
        System.out.println("Hello from\n" + logo);
        System.out.println("What would you like to do?");
    }

    private static void bye() {
        System.out.println("Bye");
    }

    public static void main(String[] args) throws NullException {
        UserInterface ui;
        // boolean isSaveFileLoaded = hasSaveFileLoad();

        hello();
        if (false) {
            // load save file;
            // int capacity = 0;
            // welcome user back;
            // ui = new UserInterface(new Warehouse(capacity));
        } else {
            System.out.println("New login. Please type the total number of goods"
                    + " your warehouse can hold");
            ui = new UserInterface(new Warehouse(1000));
        }
        ui.run();
        bye();
    }
}
