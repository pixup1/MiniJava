class TestModAssign {
    public static void main(String[] args) {
        System.out.println(new TestModA().test());
    }
}

class TestModA {
    public int test() {
        int x = 5;
        int r;
        x %= 3;
        if (x == 2){
            r = 1;
        } else {
            r = 0;
        }
        return r;
    }
}
