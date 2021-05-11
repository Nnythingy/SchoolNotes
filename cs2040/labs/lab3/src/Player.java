public class Player {
    private final int playerNum;
    private final String hand;

    public Player(int num, String hand) {
        this.playerNum = num;
        this.hand = hand;
    }

    public Player changeHand(String state) {
        return new Player(playerNum, state);
    }

    public int getPlayerNum() {
        return playerNum;
    }

    public String getHand() {
        return hand;
    }
}
