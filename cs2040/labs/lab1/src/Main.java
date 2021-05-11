import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        //find number of restaurants
        int n = Integer.parseInt(sc.nextLine()); //n is no of restaurants
        Restaurant[] resList = new Restaurant[n];

        // create as many restaurants as stated
        for(int i = 0; i < n; i++) { //run for list of restaurants
            //find no of menu items
            int menuItems = Integer.parseInt(sc.nextLine());
            //get restaurant name
            String name = sc.nextLine();
            //create restaurant
            Restaurant r = new Restaurant(name,menuItems);
            r.fillMenu(sc); // accepts input strings as menu items
            resList[i] = r; //adds to array for checking
        }

        //searches through each list, finds the first restaurant with both items
        boolean found = false; //set this for cant find printing

        for(int i = 0; i < n; i++) {
            if (resList[i].itemsFound()) {
                System.out.println(resList[i].getName());
                found= true;
                break;
            }
        }

        //no restaurants found
        if(!found) {
            System.out.println("Anywhere is fine I guess");
        }
    }
}
