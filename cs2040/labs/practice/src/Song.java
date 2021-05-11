public class Song {
    private final long listenCount;
    private final int num;
    private final String title;

    public Song(long l, int n, String title) {
        this.listenCount = l;
        this.num = n;
        this.title = title;
    }

    public long getListenCount() {
        return this.listenCount;
    }

    public int getNum() {
        return  this.num;
    }

    public String getTitle() {
        return this.title;
    }
}
