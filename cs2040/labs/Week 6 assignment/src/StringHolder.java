public class StringHolder { // String holder will hold multiple words as needed
    private String[] words;
    private int numOfWords;

    public StringHolder(int wordCount, String w) {
        this.words = new String[wordCount];
        words[0] = w;
        this.numOfWords = 1;
    }

    public int getWordCount() {
        return this.numOfWords;
    }

    public String[] getWords() {
        return this.words;
    }

    public void merge(StringHolder other) {
        // fill up array with new words
        for(int i = this.numOfWords; i < this.getWordCount() + other.getWordCount(); i++) {
            this.words[i] = other.getWords()[i - this.getWordCount()];
            this.numOfWords++;
        }
    }
}
