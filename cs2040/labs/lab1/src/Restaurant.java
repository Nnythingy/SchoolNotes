import java.util.Scanner;

public class Restaurant {
    private String name;
    private String[] menu;

    public Restaurant(String name, int n) {
        this.name = name;
        this.menu = new String[n];
    }

    public void fillMenu(Scanner sc) {
        for(int i = 0; i < this.menu.length; i++) {
            this.menu[i] = sc.nextLine();
        }
    }

    //this method checks if both pea soup and pancakes can be found
    public boolean itemsFound() {
        boolean peaSoupFound = false;
        boolean pancakesFound = false;

        for(int i = 0; i < menu.length; i++) {
            if(menu[i].equals("pea soup")) {
                peaSoupFound = true;
            } else if (menu[i].equals("pancakes")) {
                pancakesFound = true;
            }

            if(peaSoupFound && pancakesFound) {
                break;
            }
        }
       return peaSoupFound && pancakesFound;
    }

    public String getName() {
        return this.name;
    }


}
