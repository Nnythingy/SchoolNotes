import java.util.Scanner;

class Main6 {
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

        for (Cruise cruise : cruises) {
            int counter = cruise.getNumOfLoadersRequired();
            int j = 0; //counter for loader array

            while (counter > 0 && j < loads.length) {
                if (loads[j] == null) {
                    if ((j + 1) % 3 == 0) {
                        loads[j] = new RecycledLoader(j + 1, cruise);
                    } else {
                        loads[j] = new Loader(j + 1, cruise);
                    }
                    System.out.println(loads[j].toString());
                    counter--;

                } else if (loads[j].canServe(cruise)) {
                    loads[j] = loads[j].serve(cruise);
                    System.out.println(loads[j].toString());
                    counter--;
                }

                j++;
            }
        }
    }
}