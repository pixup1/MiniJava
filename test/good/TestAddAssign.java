class TestAddAssign {
    public static void main(String[] args) {
        System.out.println(new TestAddA().test());
    }
}

class TestAddA {
    public int test() {
        int x = 5;
        int r;
        x += 3;
        if (x == 8){
            r = 1;
        } else {
            r = 0;
        }
        return r;
    }
}
