public class Vertice {
    private final int id;
    private final int edges;

    public Vertice(int id, int e) {
        this.id = id;
        this.edges = e;
    }

    public int getId() {
        return this.id;
    }

    public int getEdges() {
        return this.edges;
    }
}
