    class B extends A {
          public B() {
            super("B");
          }
  
   }

   class C extends A {
          public C() {
            super("C");
          }

   }

   class A {
          private final String a;

          public A() {
            a = "A";
          }
   
          public A(String s) {
            a = s;
          }

          public <O> A add(O o) {
                  return new A(a + o);
          }

          @Override
          public String toString() {
              return a;                
          }

   } 

 

  
