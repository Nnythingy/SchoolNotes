   class X {
          private int num;
          public X( int num) {
                   this.num = num;
          }
          @Override
            public String toString() {
                   return "X:" + num;
            }
   }

   class Y {
           private final X x;
           public Y (X x) {
                    this.x = x;
           }

           @Override
            public String toString() {
                    return "Y->" + x.toString();
            }
   }
