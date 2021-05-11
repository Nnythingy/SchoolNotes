class Module extends KeyableMap<String,String,Assessment> {

    public Module(String key) {
        super(key);
    }
    
    @Override
    public Module put(Assessment a) {
       this.getMap().put(a.getKey(), a);
       return this;  
    }    
} 
