class TestReturn {
    public static void main(String[] args) {
        System.out.println(new Factorial().fibo(5));
    }
}

class Factorial {
    public int fibo(int n) {
        if (n < 2) {
            return n;
        } else {
            return this.fibo(n - 1) + this.fibo(n - 2);
        }
    }
}