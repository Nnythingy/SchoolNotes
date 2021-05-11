import java.util.Comparator;

public class Compares implements Comparator<Song> {

    @Override
    public int compare(Song o1, Song o2) {
        if(o1.getListenCount() > o2.getListenCount()) {
            return -1;
        } else if (o1.getListenCount() < o2.getListenCount()) {
            return 1;
        } else if (o1.getNum() > o2.getNum()) {
            return 1;
        } else if (o1.getNum() < o2.getNum()) {
            return -1;
        }
        return 0;
    }
}
