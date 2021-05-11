import java.util.ArrayList;

public class CircularList<P> extends ArrayList<Player> {

    public int capacity = 200; // size of the array
    public int num_items = 0; // number of items in the array
    public Player[] arr = new Player[capacity];
    
    public void insert(int index, Player item) {
        if (num_items+1 > capacity) {// array is full, enlarge it
            enlargeArr();
        }
        if (num_items - index >= 0) {
            System.arraycopy(arr, index, arr, index + 1, num_items - index);
        }
        arr[index + 1] = item; // insert item in gap
        num_items++;
    }

    // remove the item at index and return it
    public void removePlayer(int index) {
        Player p = arr[index];
        // shift item from index+1 onwards to the left to close the gap
        if (num_items - index + 1 >= 0) {
            System.arraycopy(arr, index + 1, arr, index + 1 - 1, num_items - index + 1);
        }
        num_items--;
    }

    public void enlargeArr() {
        int newSize = capacity * 2; // double the size
        Player[] temp = new Player[newSize];
        if (temp == null) { // not enough memory
            System.out.println("run out of memory!");
            System.exit(1);
        }
        // copy the original array to the new array
        for (int j=0; j < num_items; j++) {
            temp[j] = arr[j];
            arr = temp; // point arr to the new array
            capacity = newSize;
        }
    }


}
