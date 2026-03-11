class TestDivAssign {
    public static void main(String[] args) {
        System.out.println(new TestDivA().test());
    }
}

class TestDivA {
    public int test() {
        int x = 5;
        int r;
        x /= 3;
        if (x == 1){
            r = 1;
        } else {
            r = 0;
        }
        return r;
    }
}
