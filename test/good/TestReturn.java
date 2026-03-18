class TestReturn {
    public static void main(String[] args) {
        System.out.println(new ReturnFactorial().test(5));
    }
}


class ReturnFactorial {
    public int test(int n) {
        if (n <= 1) {
            return 1;
        } else {
            return n * this.test(n - 1);
        }
    }
}