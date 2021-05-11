import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int noOfPts = sc.nextInt();
        Point[] ptArray = new Point[noOfPts];

        for (int i = 0; i < noOfPts; i++) { // create as many points as desired
            double x = sc.nextDouble();
            double y = sc.nextDouble();
            ptArray[i] = new Point(x, y);
        }

        System.out.println("Maximum Disc Coverage: " + maxCover(ptArray));

    }

    // create a circle from the getCircle() method
    public static Circle createCircle(Point p, Point q, double radius) {
        Point midPt = p.midPoint(q);
        double angle = p.angleTo(midPt);
        double dis = p.distanceTo(midPt);
        double distanceToMove = Math.sqrt((radius * radius) - (dis * dis));
        Point centre = midPt.moveTo(angle + (Math.PI/2), distanceToMove); // get all that's needed, move to centre

        return Circle.getCircle(centre, radius); // return circle based on found centre
    }

    //count how many pts in array are within a circle
    public static int findCoverage(Circle c, Point[] pts) { //test max no of pts covered
        int count = 0;

        for (Point pt : pts) { // test if each point is within circle
            if (c.contains(pt)) {
                count++;
            }
        }
        return count;
    }

    // find the circle with the max no of pts covered, return no of points within
    public static int maxCover(Point[] pts) {
        int maxCount = 0;

        for (int i = 0; i < pts.length - 1; i++) {
            for (int j = i + 1; j < pts.length; j++) {
                Circle c1 = createCircle(pts[i], pts[j], 1); // create a circle

                if (findCoverage(c1, pts) > maxCount) {
                    maxCount = findCoverage(c1, pts); // update if a new max coverage is found
                }
            }
        }

        return maxCount;
    }
}