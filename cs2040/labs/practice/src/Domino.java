public class Domino {
    private int no;
    private Domino next;

    public Domino(int n) {
        this.no = n;
        this.next = null;
    }

    public Domino getNext() {
        return this.next;
    }

    public int getNo() {
        return this.no;
    }

    public void setNext(Domino d) {
        this.next = d;
    }

    public String toString() {
        return "[" + no + "," + next + "]";
    }
}
