public class Point {
    double x;
    double y;

    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double distTo(Point p) {
        double a = Math.abs(this.x - p.x);
        double b = Math.abs(this.y - p.y);

        return Math.sqrt(a*a + b*b);
    }
}
