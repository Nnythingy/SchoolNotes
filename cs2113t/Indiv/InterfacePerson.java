public class InterfacePerson  implements InterfacePrintable{
    private String name;
    public InterfacePerson(String name) {
        this.name = name;
    }

    public void print() {
        System.out.println("Person of name " + name);
    }
}
