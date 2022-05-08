package seedu.duke;

import util.exceptions.LargeQuantityException;
import util.exceptions.NullException;

import java.util.ArrayList;

public class Warehouse {
    private int capacity;
    private static ArrayList<Order> orderLists = new ArrayList<Order>();

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public void viewOrder(String orderId) {
        try {
            Integer idToBeViewed = Integer.parseInt(orderId);
            for (Order order : orderLists) {
                if (idToBeViewed.equals(order.getId())) {
                    return;
                }
            }
            System.out.println("Could not find item with given id!");
        } catch (NumberFormatException e) {
            System.out.println("Invalid format entered! Check format and try again!");
        }
    }

    public void viewGood(String goodId) {
        try {
            Integer idToBeViewed = Integer.parseInt(goodId);
            for (Order order : orderLists) {
                for (Good good : order.getGoods()) {
                    if (idToBeViewed.equals(good.getId())) {
                        System.out.println("Viewing item with id " + good.getId());
                        System.out.println("Item name: " + good.getName());
                        System.out.println("Item description: " + good.getDescription());
                        System.out.println("Item quantity: " + good.getQuantity());
                        return;
                    }
                }
            }
            System.out.println("Could not find item with given id!");
        } catch (NumberFormatException e) {
            System.out.println("Invalid format entered! Check format and try again!");
        }
    }

    // Prints all inventory in a numbered list in order of input
    public void listOrders() {
        if (orderLists.isEmpty()) {
            System.out.println("There are currently no orders.");
            return;
        }
        System.out.println("List of inventory items:");
        int counter = 0;
        for (Order order : orderLists) {
            System.out.println((counter + 1) + ". " + order);
            counter++;
        }
    }

    // Prints all inventory in a numbered list in order of input
    public void listGoods() {
        //int numberOfUserGoods = userGoods.size();
        if (orderLists.isEmpty()) {
            System.out.println("There are no inventory in the warehouse.");
            return;
        }
        System.out.println("List of inventory items:");
        System.out.println("id | name");
        int counter = 0;
        for (Order order: orderLists) {
            for (Good good : order.getGoods()) {
                System.out.println((counter + 1) + ". " + good);
                counter++;
            }
        }
    }

    public int totalGoods() throws NullException {
        if (orderLists == null) {
            throw new NullException("userGoods");
        }
        assert(orderLists != null);
        int total = 0;
        for (Order order: orderLists) {
            for (Good good: order.getGoods()) {
                total += good.getQuantity();
            }
        }
        return total;
    }

    public void setCapacity(int capacity) {
        try {
            if (capacity < totalGoods()) {
                throw new LargeQuantityException();
            }
            this.capacity = capacity;
            System.out.printf("Current Warehouse capacity is %d\n", capacity);
        } catch (NullException nullException) {
            orderLists = new ArrayList<Order>();
            this.capacity = capacity;
            System.out.printf("Current Warehouse capacity is %d\n", capacity);
        } catch (LargeQuantityException largeQuantityException) {
            System.out.println("Current total goods in the warehouse is more"
                    + " than input capacity");
        }
    }
}
