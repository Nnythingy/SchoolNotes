import java.util.Comparator;

public class TimeCompareLeave implements Comparator<Researcher> {
    @Override
    public int compare(Researcher r1, Researcher r2) { // for sorting by leave time
        if (r1.getLeaveTime() > r2.getLeaveTime()) {
            return 1;
        } else if (r1.getLeaveTime() < r2.getLeaveTime()) {
            return -1;
        }
        return 0;
    }
}