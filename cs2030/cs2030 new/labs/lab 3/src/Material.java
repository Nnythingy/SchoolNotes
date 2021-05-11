class Material {
    private final String name;
    private final double density;

    public Material(String name, double d) {
        this.name = name;
        this.density = d;
    }

    public double getDensity() {
        return density;
    }
}
