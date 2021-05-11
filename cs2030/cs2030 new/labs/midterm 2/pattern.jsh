String num(int n) {
        return IntStream.range(0,n)
                .map(x -> n-x)
                .mapToObj(x -> String.valueOf(x))
                .reduce("", (x,y) -> x + y);
    }

    String dot(int n) {
        return Stream.generate(() -> ".").limit(n).reduce("", (x,y) -> x + y);
    }
    
    String pattern(int n) {
        return IntStream
                .rangeClosed(0,n -1)
                .mapToObj(x -> dot(x) + num(n - x))
                .reduce("", (x,y) -> x + y);

    }
