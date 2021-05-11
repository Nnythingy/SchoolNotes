//Schubert Goh, A0200125E, Week 4 Take Home Assignment 1A

import java.util.Scanner;

public class TrainPassengers {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int maxLoad = sc.nextInt(); // get max capacity
        int noOfStops = sc.nextInt(); // get no of stops

        // variables for tallying passengers
        int totalNo = 0;
        boolean possible = true;

        for (int i = 0; i < noOfStops; i++) {
            totalNo -= sc.nextInt();// Minus no of passengers who left train

            if(totalNo < 0) { //more people leave than train already has people
                possible = false;
            }

            totalNo += sc.nextInt(); // Add no of passengers who enter

            int leftBehind = sc.nextInt(); // get no of passengers left

            // set to false if impossible, true if not
            if(!isPossible(maxLoad, totalNo, leftBehind, i, noOfStops)) {
                possible = false;
            }
        }

        if(possible) {
            System.out.println("possible"); // no errors detected, numbers are possible
        } else {
            System.out.println("impossible"); // error found, numbers are impossible
        }
    }

    // checks if after the line of inputs, if the total number reported is possible
    public static boolean isPossible(int max, int totalNo, int leftBehind, int i, int noOfStops) {

        // either too many passengers or more left than possible
        if(totalNo > max || totalNo < 0) {
            return false;
        }
        // passengers left behind when there is still room
        if(leftBehind > 0 && totalNo != max) {
            return false;
        }
        // passengers remaining on the train at the last station
        return i != noOfStops - 1 || (totalNo == 0 && leftBehind <= 0);
    }
}
