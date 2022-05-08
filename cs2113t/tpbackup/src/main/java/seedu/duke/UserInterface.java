package seedu.duke;

import util.exceptions.NullException;
import util.exceptions.WrongCommandException;

import java.util.HashMap;
import java.util.Scanner;

public class UserInterface {
    private Warehouse warehouse;

    public UserInterface(Warehouse warehouse) {
        this.warehouse = warehouse;
    }

    public void run() {
        Scanner input = new Scanner(System.in);
        String userInput = input.nextLine();

        try {
            while (!userInput.equals("bye")) {
                // current implementation is just take 1st value for command
                String command = userInput.split(" ")[0];
                switch (command) {
                case "add":
                    String regex = "id/(?<id>\\d*) n/(?<name>.*) q/(?<qty>\\d*)"
                            + " d/(?<desc>\\.*";
                    Regex regexMatch = new Regex(userInput, regex);
                    HashMap<String, String> matches = regexMatch.getGroupValues();
                    Commands.addGood(matches.get("id"), matches.get("name"),
                            matches.get("qty"), matches.get("desc"), userGoods);
                    break;
                case "view":
                    //using flags here to distinguish between different views????
                    regex = "(?<flag>*[og])/ id/(?<id>\\d*)";
                    regexMatch = new Regex(userInput, regex);
                    matches = regexMatch.getGroupValues();
                    if (matches.get("flag").equals("o")) {
                        // view order with flag "o"
                        warehouse.viewOrder(matches.get("id"));
                    } else if (matches.get("flag").equals("g")) {
                        // view good with flag "g"
                        warehouse.viewGood(matches.get("id"));
                    } else {
                        // wrong command exception
                        throw new WrongCommandException("view", true);
                    }
                    break;
                case "list":
                    regex = "(?<flag>*[og])/ id/(?<id>\\d*)";
                    regexMatch = new Regex(userInput, regex);
                    matches = regexMatch.getGroupValues();
                    if (matches.get("flag").equals("o")) {
                        // list orders with flag "o"
                        warehouse.listOrders();
                    } else if (matches.get("flag").equals("g")) {
                        // list goods with flag "g"
                        warehouse.listGoods();
                    } else {
                        // wrong command exception
                        throw new WrongCommandException("view", true);
                    }
                    break;
                case "remove":
                    String format = "id/(?<id>\\d*) q/(?<qty>\\d*)";
                    regexMatch = new Regex(userInput, format);
                    HashMap<String, String> inputValues = regexMatch.getGroupValues();
                    Commands.removeGood(inputValues.get("id"), inputValues.get("qty"), userGoods);
                    break;
                case "total":
                    int total = warehouse.totalGoods();
                    System.out.printf("There are %d goods in total.\n", total);
                    break;
                case "help":
                    Commands.help();
                    break;
                default:
                    //error exception here
                    throw new WrongCommandException("", false);
                    break;
                }
                System.out.println("Another command?");
                userInput = input.nextLine();
            }
        } catch (WrongCommandException wrongCommandException) {
            if (wrongCommandException.isCommand()) {
                String wrongCommand = wrongCommandException.getCommand();
                System.out.printf("%s command was used wrongly. Type help to see examples\n",
                        wrongCommand);
            } else {
                System.out.println("No such command. Type help to see examples");
            }
        } catch (NullException nullException) {

        }
    }
}
