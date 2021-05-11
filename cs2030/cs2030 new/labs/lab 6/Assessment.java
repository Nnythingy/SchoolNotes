class Assessment implements Keyable<String> {
    public String name;
    public String grade;
    
    public Assessment (String n, String g) {
        this.name = n;
        this.grade = g;
    }

    @Override
    public String getKey() {
        return this.name;
    }

    public String getGrade() {
        return this.grade;
    }
    
    @Override
    public String toString() {
        return "{" + this.name + ": " + this.grade + "}";
    }




      

}
