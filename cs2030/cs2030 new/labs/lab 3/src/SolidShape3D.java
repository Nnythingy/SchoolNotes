class SolidShape3D implements DensityMass {
    private final Shape shape;
    private final Material mat;

    public SolidShape3D(Cuboid c, Material m) {
        this.shape = c;
        this.mat = m;
    }

    public SolidShape3D(Sphere sph, Material m) {
        this.shape = sph;
        this.mat = m;
    }

    @Override
    public double getDensity() {
        return this.mat.getDensity();
    }

    @Override
    public double getMass() {
        return getDensity()*shape.getVolume();
    }

    @Override
    public String toString() {
            return "Solid" + this.shape.toString() + " with a mass of "
                    + String.format("%.2f", this.getMass());
    }
}
