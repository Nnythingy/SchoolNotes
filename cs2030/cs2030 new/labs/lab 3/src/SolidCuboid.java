class SolidCuboid extends Cuboid implements DensityMass {

    private final double density;

    public SolidCuboid (double h, double w, double l, double d) {
        super(h, w, l);
        this.density = d;
    }
    @Override
    public double getDensity() {
        return this.density;
    }
    @Override
    public double getMass() {
        return this.density*this.getVolume();
    }

    @Override
    public SolidCuboid setHeight(double h) {
        return new SolidCuboid(h, this.width, this.length, this.density);
    }

    @Override
    public SolidCuboid setWidth(double w) {
        return new SolidCuboid(this.height, w, this.length, this.density);
    }

    @Override
    public SolidCuboid setLength(double l) {
        return new SolidCuboid(this.height, this.width, l, this.density);
    }

    @Override
    public String toString() {
        return "Solid" + super.toString() + " with a mass of " + String.format("%.2f", this.getMass());
    }

}