public class GradeHelper {
    public static double getGradeCap (String grade) {
        double CAP = 0;
        switch (grade) {
            case "A+":
            case "A":
                CAP = 5.0;
                break;
            case "A-":
                CAP = 4.5;
                break;
            case "B+":
                CAP = 4.0;
                break;
            case "B":
                CAP = 3.5;
                break;
            case "B-":
                CAP = 3.0;
                break;
            case "C":
                CAP = 2.5;
            default:
                CAP = 0;
        }
        return CAP;
    }

    public static double[] getMultipleGradeCaps (String[] grades) {
        double[] caps = new double[grades.length];
        for (int i = 0; i < grades.length; i++) {
            caps[i] = getGradeCap(grades[i]);
        }

        return caps;
    }

    /*
    public static void main (String[] args) {
        System.out.println("A+: " + getGradeCap("A+"));
        System.out.println("A " + getGradeCap("A"));
    }
    */
    public static void main(String[] args) {
        String[] grades = new String[]{"A+", "A", "A-"};
        double[] caps = getMultipleGradeCaps(grades);
        for (int i = 0; i < grades.length; i++) {
            System.out.println(grades[i] + ":" + caps[i]);
        }
    }
}
