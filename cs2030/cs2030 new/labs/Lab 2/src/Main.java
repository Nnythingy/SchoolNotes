import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int cruiseNo = sc.nextInt();
        Cruise[] cruises = new Cruise[cruiseNo];

        for (int i = 0; i < cruiseNo; i++) {
            String name = sc.next();
            int arrTime = sc.nextInt();

            if (name.charAt(0) == 'B') {
                int length = sc.nextInt();
                int passengers = sc.nextInt();
                cruises[i] = new BigCruise(name, arrTime, length, passengers);
            } else {
                cruises[i] = new SmallCruise(name, arrTime);
            }
        }

        Loader[] loads = new Loader[40];

        for (int i = 0; i < cruises.length; i++) {
                int counter = cruises[i].getNumOfLoadersRequired();
                int j = 0; //counter for loader array

                while(counter > 0 && j < loads.length) {
                    if(loads[j] == null) {
                        loads[j] = new Loader(j+1, cruises[i]);
                        System.out.println(loads[j].toString());
                        counter--;

                    } else if (loads[j].canServe(cruises[i])) {
                        loads[j] = loads[j].serve(cruises[i]);
                        System.out.println(loads[j].toString());
                        counter--;
                    }

                    j++;
                }
        }
    }
}

