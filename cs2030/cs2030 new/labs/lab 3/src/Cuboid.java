class Cuboid extends Shape {
    protected final double height;
    protected final double width;
    protected final double length;

    public Cuboid(double h, double w, double l) {
        this.height = h;
        this.width = w;
        this.length = l;
    }

    @Override
    public double getSurfaceArea() {
        return 2*this.height*this.width
                + 2*this.height*this.length
                + 2*this.width*this.length;
    }

    @Override
    public double getVolume() {
        return height*width*length;
    }

    public Cuboid setHeight(double h) {
        return new Cuboid(h, this.width, this.length);
    }

    public Cuboid setWidth(double w) {
        return new Cuboid(this.height, w, this.length);
    }

    public Cuboid setLength(double l) {
        return new Cuboid(this.height, this.width, l);
    }

    @Override
    public String toString() {
        return "Cuboid [" + String.format("%.2f", this.height) + " x "
                + String.format("%.2f", this.width) + " x "
                + String.format("%.2f", this.length) + "]";
    }
}
