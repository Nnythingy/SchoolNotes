import java.util.Comparator;

class OtherTimeComparator implements Comparator<Runner> {

    @Override
    public int compare(Runner r1, Runner r2) {
        return Double.compare(r1.getOtherLegTime(), r2.getOtherLegTime());
    }
}
