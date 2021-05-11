import java.util.stream.IntStream;
import java.util.stream.*;

class Main {
    public static int gcd(int x, int y) {
        return Stream
                .iterate(new Pair(x, y),
                         next -> next.y() != 0,
                         next -> new Pair(next.y(), next.x() % next.y()))
                .reduce((a,b) -> b)
                .get().y();      
    }
    
    public static class Pair {
        private final int x;
        private final int y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int x() {
            return this.x;
        }

        public int y() {
            return this.y;
        }
    }
}
