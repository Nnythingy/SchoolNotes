import java.util.Comparator;

public class Vcom implements Comparator<Village> {
    @Override
    public int compare(Village o1, Village o2) {
        if (o1.val < o2.val) {
            return -1;
        } else if (o1.val > o2.val) {
            return 1;
        }
        return 0;
    }
}
