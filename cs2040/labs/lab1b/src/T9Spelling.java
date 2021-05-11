//Schubert Goh, A0200125E, Week 4 Lab, Lab group 6

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class T9Spelling {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); //get n lines of messages
        String[] numLines = new String[n]; //create a string array to store numerical outputs

        for(int i = 0; i < n; i++) {
            String s = br.readLine(); //get an input of text message
            String nums = ""; //get a blank string to be filled with corresponding numbers
            for(int j = 0; j < s.length(); j++) {

                // check if there is a need for spaces, if the incoming number is the same as the previous
                if(nums.length() > 0 && nums.charAt(nums.length() - 1) == getNumberInput(s.charAt(j)).charAt(0)) {
                    nums += " "; // add a space
                }
                nums += getNumberInput(s.charAt(j)); // add the number input to the line to be printed
            }
            numLines[i] = nums; // add the number line to the array
        }

        //print out the lines by looking through the array
        for(int i = 0; i < n; i++) {
            System.out.println("Case #" + (i+1) + ": " + numLines[i]);
        }
    }

    // return the numerical input needed for the character given
    public static String getNumberInput(char letter) {
        switch (letter) {
            case ' ':
                return "0";
            case 'a':
                return "2";
            case 'b':
                return "22";
            case 'c':
                return "222";
            case 'd':
                return "3";
            case 'e':
                return "33";
            case 'f':
                return "333";
            case 'g':
                return "4";
            case 'h':
                return "44";
            case 'i':
                return "444";
            case 'j':
                return "5";
            case 'k':
                return "55";
            case 'l':
                return "555";
            case 'm':
                return "6";
            case 'n':
                return "66";
            case 'o':
                return "666";
            case 'p':
                return "7";
            case 'q':
                return "77";
            case 'r':
                return "777";
            case 's':
                return "7777";
            case 't':
                return "8";
            case 'u':
                return "88";
            case 'v':
                return "888";
            case 'w':
                return "9";
            case 'x':
                return "99";
            case 'y':
                return "999";
            case 'z':
                return "9999";
            default:
                return " ";
        }
    }
}
