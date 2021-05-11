import java.util.ArrayList;   
    class A {
           private final ArrayList<Integer> nums;
           public A (int num) {
                   this.nums = new ArrayList<Integer>();
                   this.nums.add(num);
           }

           public A (ArrayList<Integer> nums) {
                   this.nums = new ArrayList<Integer>(nums);
           }


           public A next(int num) {
                   ArrayList<Integer> newList = new ArrayList<>(this.nums);
                   newList.add(num);
                   return new A(newList);
           }

           @Override
            public String toString() {
                    String s = "";
                    for (int i = 0; i < this.nums.size(); i++) {
                           s += "[A:" + this.nums.get(i) + "]";
                    }
                    return s;
            }
   }
