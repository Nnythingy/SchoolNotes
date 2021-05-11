class Student extends KeyableMap<String, String, Module> {

    public Student(String key) {
        super(key);
    }

    @Override
    public Student put(Module mod) {
       this.getMap().put(mod.getKey(), mod);
       return this;  
    }

    
}
