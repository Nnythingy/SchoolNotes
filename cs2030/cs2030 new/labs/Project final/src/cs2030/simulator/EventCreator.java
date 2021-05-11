/**
 * EventCreator creates evnts into a pq
 * and polls them to decide which events to create
 * for the next instance.
 *
 * @author Schubert Goh
 */

package cs2030.simulator;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class EventCreator {

    private static int noServe = 0;
    private static int noLeave = 0;
    private static double totalWaitTime = 0;
    private static ArrayList<Server> servers = new ArrayList<>();
    private static int serverCount = 0;
    private static int selfCheck = 0;
    private static Queue<Customer> selfCheckQ = new LinkedList<>();
    private static int maxQSize = 0;
    private static PriorityQueue<Event> pq = new PriorityQueue<>(); // event pq

    /**
     * This method generates and queues all events in chronological order.
     *
     * @param seed base seed for random generator
     * @param n no of human servers
     * @param n2 no of self checkout servers
     * @param max max length of queue
     * @param c no of customers
     * @param arr arrival rate
     * @param serv service rate
     * @param restRate rest rate for human servers
     * @param restP rest probability
     * @param greedP greed customer generation probability
     */
    public static void eventQueue(int seed, int n, int n2, int max, int c, double arr, double serv,
                                  double restRate, double restP, double greedP) {

        // sets random generator and values
        RandomGenerator rng = new RandomGenerator(seed, arr, serv, restRate);
        serverCount = n;
        selfCheck = n2;
        maxQSize = max;

        double now = 0; // first customer's arrival time

        for (int i = 1; i <= c; i++) {

            Customer cus;

            if (rng.genCustomerType() < greedP) { // decide what customer to generate
                cus = new GreedyCustomer(i, now);
            } else {
                cus = new Customer(i, now);
            }

            double time = cus.getArrTime();
            pq.add(new Event(cus, null, time, State.ARRIVE));
            now += rng.genInterArrivalTime();
        }

        // buffer server at the start
        servers.add(0, new HumanServer(0, 0));

        // add as many human/auto servers as needed
        for (int i = 1; i <= n; i++) {
            servers.add(i, new HumanServer(i, max));
        }
        for (int i = n + 1; i <= n + n2; i++) {
            servers.add(i, new AutoServer(i));
        }

        // run event queue
        while (!pq.isEmpty()) {
            Event event = pq.poll(); // get first event in queue
            if (!event.getState().equals(State.REST) && !event.getState().equals(State.BACK)) {
                System.out.println(event); // print this event if its not back or rest
            }

            // get details of the event
            State state = event.getState();
            Server server = event.getServer();
            Customer customer = event.getCustomer();
            double time = event.getTime();

            // temporary values
            State nextEventState = null;
            double nextEventTime = -1;
            Server nextServer = null;

            switch (state) {
                case ARRIVE:
                    nextEventTime = time;

                    if (servers.isEmpty()) {
                        nextEventState = State.LEAVE; // can't do either, so customer leaves
                    } else {
                        if (serveScan() != -1) { // check if there's a server that can serve
                            nextEventState = State.SERVE;
                            nextServer = servers.get(serveScan());

                        } else if (greedyScan(customer) != -1) {
                            nextEventState = State.WAIT; // try to wait greedily
                            nextServer = servers.get(greedyScan(customer));

                        } else if (waitScan() != -1) { // else try to wait normally
                            nextEventState = State.WAIT;
                            nextServer = servers.get(waitScan());

                        } else {
                            nextEventState = State.LEAVE; // can't do either, so customer leaves
                        }
                    }
                    break;

                case SERVE:

                    noServe++; //serve count increases
                    totalWaitTime += time - customer.getArrTime(); // wait time increases

                    // poll, update and read a new server into server pq
                    Server temp = servers.get(server.getId());
                    double serveTime = time + rng.genServiceTime();

                    temp = server.serve(customer, serveTime);

                    servers.set(server.getId(), temp);

                    // update time for this event
                    nextEventTime = serveTime;
                    nextEventState = State.DONE;
                    nextServer = temp;

                    break;

                case WAIT:

                    if (server.isHuman()) {
                        // poll, update and read a new server into server pq
                        Server temp2 = (Server) servers.get(server.getId());
                        temp2 = ((HumanServer) server).wait(customer); // add to servers wait queue
                        servers.set(server.getId(), temp2);

                    } else {
                        selfCheckQ.add(customer); // for self check Q
                    }

                    break;

                case DONE:

                    Server s = servers.get(server.getId()); // get correct server
                    s = s.clear(); // removes curr customer so next waiting can go in
                    servers.set(server.getId(), s);

                    if (s.isHuman()) {

                        double rest = rng.genRandomRest();
                        if (rest < restP) { // gen rest event
                            nextEventTime = time;
                            nextEventState = State.REST;
                            nextServer = s;
                            customer = null;

                        } else {
                            if (((HumanServer) s).getNext() != null) { // check if next is empty
                                customer = ((HumanServer) s).getNext();
                                nextEventTime = time;
                                nextEventState = State.SERVE;
                                nextServer = s;
                            }
                        }
                    } else { // for AutoServer

                        if (!selfCheckQ.isEmpty()) { // check if next is empty
                            customer = selfCheckQ.poll();
                            nextEventTime = time;
                            nextEventState = State.SERVE;
                            nextServer = s;
                        }
                    }
                    break;

                case REST: // only for normal server

                    Server r = servers.get(server.getId());
                    r = ((HumanServer) r).rest();
                    servers.set(r.getId(), r);

                    customer = null;
                    nextEventTime = time + rng.genRestPeriod();
                    nextEventState = State.BACK;
                    nextServer = r;

                    break;

                case BACK: // only for normal server

                    Server b = servers.get(server.getId());
                    b = ((HumanServer) b).back();
                    servers.set(b.getId(), b);

                    if (((HumanServer) b).getNext() != null) {
                        customer = ((HumanServer) b).getNext();
                        nextEventTime = time;
                        nextEventState = State.SERVE;
                        nextServer = b;
                    }

                    break;

                case LEAVE:
                    noLeave++; // update leave count
                    break;

                default:
                    break;
            }

            // add new event some of the parameters are filled
            if (nextEventTime != -1 && !nextEventState.equals(null)) {
                pq.add(new Event(customer, nextServer, nextEventTime, nextEventState));
            }
        }
        // print out final statement
        if (noServe == 0) {
            noServe++;
        }
        System.out.println(String.format("[%.3f %d %d]", totalWaitTime / noServe,
                noServe, noLeave));

    }


    /**
     * This methods scans through server list and finds id of first available server who can serve.
     * @return an int of the id of the selected server, or default -1
     *      if cannot find any available server
     */
    public static int serveScan() {
        int i = 1;

        while (i <= servers.size() - 1) {
            if (servers.get(i).canServe()) {
                return i;
            }
            i++;
        }
        return -1;
    }

    /**
     * This methods scans through server list and finds id of first avaliable server who can wait.
     * @return an int of the id of the selected server,
     *      or default -1 if cannot find any avaliable server
     */
    public static int waitScan() {
        int i = 1;

        while (i <= serverCount) {
            if (((HumanServer) servers.get(i)).canWait()) {
                return i;
            }
            i++;

        }

        if (selfCheck > 0 && selfCheckQ.size() < maxQSize) {
            return serverCount + 1; // always first avaliable self check server
        }
        return -1;
    }

    /**
     * this method scans through all queues greedily to find the one with shortest length.
     * @c A customer to verify if its greedy
     * @return an int denoting the shortest queue findable, or default -1 if no q can wait
     */
    public static int greedyScan(Customer c) {
        int n = -1;
        int min = maxQSize;

        if (c instanceof GreedyCustomer) {
            // search through human servers to find shortest q length
            for (int i = 1; i <= serverCount; i++) {
                if (((HumanServer) servers.get(i)).getQLength() < min) {
                    min = ((HumanServer) servers.get(i)).getQLength(); // update time
                    n = i; // update id
                }
            }

            // check if self checkout queue is shorter
            if (selfCheck > 0 && selfCheckQ.size() < min) {
                n = serverCount + 1;
            }
        }

        return n; // return id of selected server
    }

}