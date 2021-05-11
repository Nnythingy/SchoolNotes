import java.util.*;

public class ModDijkstraDemo {
  public static final int INF = 1000000000;
  public static ArrayList< ArrayList< IntegerPair > > AdjList = new ArrayList< ArrayList< IntegerPair > >();
  public static ArrayList< Integer > D = new ArrayList< Integer >();
  public static ArrayList< Integer > p = new ArrayList< Integer >();
  public static int V, E;
  
  public static void init_SSSP(int s) { // initialization phase
    D.clear();
    D.addAll(Collections.nCopies(V, INF)); // use 1B to represent INF
    p.clear();
    p.addAll(Collections.nCopies(V, -1)); // use -1 to represent NULL
    D.set(s, 0); // this is what we know so far
  }

  public static void backtrack(int s, int u) {
    if (u == -1 || u == s) {
      System.out.printf("%d", u);
      return;
    }
    backtrack(s, p.get(u));
    System.out.printf(" %d", u);
  }

  public static void main(String[] args) {
/*
// Small graph without negative weight cycle, OK
5 7 2
1 4 6
1 3 3
2 1 2
0 4 1
2 0 6
3 4 5
2 3 7

// Small graph with some negative weight edges; no negative cycle, still OK
5 5 0
0 1 1
0 2 10
1 3 2
2 3 -10
3 4 3
 
// Small graph with negative weight cycle, infinite loop
5 5 0
0 1 1000
1 2 15
2 1 -42
2 3 10
0 4 -100
*/

    Scanner sc = new Scanner(System.in);
    V = sc.nextInt(); E = sc.nextInt();
    int source = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++)
      AdjList.add(new ArrayList < IntegerPair >()); // add neighbor list to Adjacency List

    for (int i = 0; i < E; i++) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      AdjList.get(u).add(new IntegerPair(v, w));
    }

    init_SSSP(source);

    // Modified Dijkstra's routine
    // sort based on increasing distance
    PriorityQueue < IntegerPair > pq = new PriorityQueue < IntegerPair > (); pq.offer(new IntegerPair(0, source));
    
    while (!pq.isEmpty()) { // main loop
      IntegerPair top = pq.poll(); // greedy: pick shortest unvisited vertex
      int d = top.first(),
      u = top.second();
      

      // COMPLETE THE CODE HERE !!!!!


    }
  
    for (int i = 0; i < V; i++) {
      System.out.printf("SSSP(%d, %d) = %d\n", source, i, D.get(i));
      if (D.get(i) != INF) {
        System.out.printf("Path: ");
        backtrack(source, i);
        System.out.printf("\n");
      }
      System.out.printf("\n");
    }
  }
}



class IntegerPair implements Comparable<IntegerPair> {
  Integer _first, _second;

  public IntegerPair(Integer f, Integer s) {
    _first = f;
    _second = s;
  }

  public int compareTo(IntegerPair o) {
    if (!this.first().equals(o.first()))
      return this.first() - o.first();
    else
      return this.second() - o.second();
  }

  Integer first() { return _first; }
  Integer second() { return _second; }
}
