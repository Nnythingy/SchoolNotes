import java.io.*;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Zipf {

    public static PriorityQueue<Song> songList = new PriorityQueue<>(new Compares());

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int num = Integer.parseInt(tk.nextToken());
        int top = Integer.parseInt(tk.nextToken());


        for(int i = 1; i <= num; i++) {
            StringTokenizer tk2 = new StringTokenizer(br.readLine());
            long listen = Long.parseLong(tk2.nextToken());
            String name = tk2.nextToken();

            songList.add(new Song(listen*(i), i, name));
        }

        for(int i = 0 ; i < top; i++) {
            Song curr = songList.poll();
            assert curr != null;
            pw.println(curr.getTitle());
        }

        pw.close();


    }
}
