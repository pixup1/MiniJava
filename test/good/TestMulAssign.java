class TestMulAssign {
    public static void main(String[] args) {
        System.out.println(new TestMulA().test());
    }
}

class TestMulA {
    public int test() {
        int x = 5;
        int r;
        x *= 3;
        if (x == 15){
            r = 1;
        } else {
            r = 0;
        }
        return r;
    }
}
