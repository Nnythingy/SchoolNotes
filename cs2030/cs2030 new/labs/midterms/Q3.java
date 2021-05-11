import java.util.List;
import java.util.Map;

class Case {
    private int id;
}

class ImportedCase extends Case {
    private String country;
}

class Contact {
    final static int CASUAL = 0;
    final static int CLOSE = 1;
    final static int FAMILY_MEMBER = 2;
    private Case caseA;
    private Case caseB;
    private int state;

}

class Cluster {
    private String name;
    private List<Case> caseList;
        
}

class DataBase {
    Map<Case, List<Contact>> contactList;
    Map<Case, List<Cluster>> clusters;
}
