public class Sphere extends Shape {
    protected double radius;

    public Sphere(double radius) {
        this.radius = radius;
    }

    public Sphere setRadius(double r) {
        return new Sphere(r);
    }

    @Override
    double getSurfaceArea() {
        return 4*Math.PI*radius*radius;
    }

    @Override
    double getVolume() {
        return (4/3.0)*Math.PI*Math.pow(radius, 3);
    }

    @Override
    public String toString() {
        return "Sphere [" + String.format("%.2f", this.radius) + "]";
    }
}
