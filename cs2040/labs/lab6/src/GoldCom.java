import java.util.Comparator;

public class GoldCom implements Comparator<Quest> {

    @Override
    public int compare(Quest q1, Quest q2) { // compares quests by gold for the pq
        if(q1.getGold() > q2.getGold()) {
            return -1;
        } else if (q1.getGold() < q2.getGold()) {
            return 1;
        }
        return 0;
    }
}
