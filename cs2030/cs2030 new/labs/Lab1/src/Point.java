import static java.lang.Math.*;

class Point {

    private final double x;
    private final double y;

    // create point
    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    //get midpoint of this and another pt
    public Point midPoint(Point other) {
        return new Point((this.x + other.x)/2, (this.y + other.y)/2);
    }

    //get angle between 2 points
    public double angleTo(Point other) {
        double xAngle = abs(other.x - this.x);
        double yAngle = abs(other.y - this.y);
        return atan2(yAngle, xAngle);
    }

    //create a new point which is moved by a certain distance at ana angle
    public Point moveTo(double radians, double dist) {
        double xAdd = dist* cos(radians);
        double yAdd = dist* sin(radians);

        return new Point(this.x + xAdd, this.y + yAdd);
    }

    // Get distance to other point
    public double distanceTo(Point other) {
        double xL = other.x - this.x;
        double yL = other.y - this.y;

        return sqrt(xL*xL + yL*yL);
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    @Override
    public String toString() {
        return "point (" + String.format("%.3f", this.x) + ", " + String.format("%.3f", this.y) + ")";
    }
}