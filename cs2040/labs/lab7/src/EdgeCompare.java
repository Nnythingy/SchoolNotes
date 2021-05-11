import java.util.Comparator;

public class EdgeCompare implements Comparator<Vertice> {

    @Override
    public int compare(Vertice v1, Vertice v2) {
        if (v1.getEdges() < v2.getEdges()) {
            return -1;
        } else if (v1.getEdges() > v2.getEdges()) {
            return 1;
        }
        return 0;
    }
}
