import java.util.Optional;
import java.util.NoSuchElementException;

class Roster extends KeyableMap<String, String, Student> {

    public Roster(String key) {
        super(key);
    }

    @Override
    public Roster put(Student s) {
       this.getMap().put(s.getKey(), s);
       return this;  
    }

    public String getGrade(String student, String mod, String exam) throws NoSuchRecordException {
        try {
          Optional <Student> stu = this.get(student);
          Optional <Module> modu = stu.flatMap(x -> x.get(mod));
          Optional <Assessment> ass = modu.flatMap(x -> x.get(exam));
          Assessment a = ass.orElseThrow();
          return a.getGrade();
          
        } catch (NoSuchElementException e) {
          throw new NoSuchRecordException("No such record: " + student +
                          " " + mod + " " + exam);        
        }
    }

    
}
