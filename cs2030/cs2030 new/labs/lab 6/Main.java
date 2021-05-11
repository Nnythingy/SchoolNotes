import java.util.Scanner;

public class Main {
    
    public static Roster roster = new Roster(""); 

    public static void main(String[] args) throws NoSuchRecordException {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        for (int i = 0; i < n; i++) {
    
            String stuName = sc.next();
            String modCode = sc.next();
            String assess = sc.next();
            String grade = sc.next();
            
            Assessment a = new Assessment(assess, grade);

            if (!roster.getMap().containsKey(stuName)) {
                Student stu = new Student(stuName);
                Module mod = new Module(modCode);
                mod.put(a);
                stu.put(mod);
                roster.put(stu);
            } else {
                if (!roster.getMap().get(stuName).getMap().containsKey(modCode)) {
                    Module mod = new Module(modCode);
                    mod.put(a);
                    roster.getMap().get(stuName).put(mod);
                } else {
                    roster.getMap().get(stuName).getMap().get(modCode).put(a);
                }
            }       
        }
        
        while (sc.hasNext()) {

            String stu = sc.next();
            String modCode = sc.next();
            String assess = sc.next();
            
            try {
              System.out.println(roster.getGrade(stu, modCode, assess));
            } catch (NoSuchRecordException e) {
              System.out.println(e);  
            }
        }
    }
}
