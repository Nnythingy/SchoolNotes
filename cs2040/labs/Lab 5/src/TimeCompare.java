import java.util.Comparator;

public class TimeCompare implements Comparator<Researcher> {
    @Override
    public int compare(Researcher r1, Researcher r2) { // for sorting by arrival time
        if (r1.getArrTime() > r2.getArrTime()) {
            return 1;
        } else if (r1.getArrTime() < r2.getArrTime()) {
            return -1;
        } else if (r1.getArrTime() == r2.getArrTime() && r1.getLeaveTime() > r2.getLeaveTime()) {
            return 1;
        } else if (r1.getArrTime() == r2.getArrTime() && r1.getLeaveTime() < r2.getLeaveTime()) {
            return -1;
        }
        return 0;
    }
}
