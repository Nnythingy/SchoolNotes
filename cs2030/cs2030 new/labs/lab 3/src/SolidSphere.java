public class SolidSphere extends Sphere implements DensityMass {

    private final double density;

    public SolidSphere(double radius, double d) {
        super(radius);
        this.density = d;
    }

    public SolidSphere setRadius(double r) {
        return new SolidSphere(r, this.density);
    }
    @Override
    public double getDensity() {
        return this.density;
    }
    @Override
    public double getMass() {
        return this.getDensity()*this.getVolume();
    }

    @Override
    public String toString() {
        return "Solid" + super.toString()  + " with a mass of " + String.format("%.2f", this.getMass());
    }
}
