/**
 * Main method for working operations.
 *
 * @author Schubert Goh
 */

import cs2030.simulator.EventCreator;

import java.util.Scanner;

public class Main {

    /**
     * Main method for working operations.
     * @param arg for generating run
     */
    public static void main(String[] arg) {
        // get all the necessary info
        Scanner sc = new Scanner(System.in);
        int seed = sc.nextInt(); // base seed for random gen
        int n = sc.nextInt(); // no of normal servers
        int n2 = sc.nextInt(); // self checkout servers
        int max = sc.nextInt(); // max queue size
        int c = sc.nextInt(); // no of customers
        double arr = sc.nextDouble(); // arrival time
        double serv = sc.nextDouble(); // serve time
        double restRate = sc.nextDouble(); // rest time
        double restP = sc.nextDouble(); // rest probability
        double greedP = sc.nextDouble(); // greedy customer probability

        EventCreator.eventQueue(seed, n, n2, max, c,
                arr, serv, restRate, restP, greedP); // perform main method
    }
}