import java.util.Comparator;

public class StackCompare implements Comparator<Coins> {
    @Override
    public int compare(Coins c1, Coins c2) { // poll smallest in front
        if (c1.value - c2.value > 0) {
            return 1;
        } else if (c1.value - c2.value < 0){
            return -1;
        }
        return 0;
    }
}
