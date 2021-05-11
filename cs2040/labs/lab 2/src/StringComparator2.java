import java.util.Comparator;

class StringComparator2<S> implements Comparator<String> {

    @Override
    public int compare(String s1, String s2) {
        return s1.substring(0,2).compareTo(s2.substring(0,2)); //compares first 2 characters
    }
}
