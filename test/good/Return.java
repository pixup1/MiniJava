class Return {
    public static void main(String[] args) {
        System.out.println(new TestReturn().fact(5));
    }
}

class TestReturn{
    public int fact(int n){
        if (n < 2){
            return 1;
        }
        return n * this.fact(n - 1);
    }
}
