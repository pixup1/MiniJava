class Main {
    public static void main(String[] args) {
        System.out.println(new TestAffec().test());
    }
}

class TestAffec {
    public int test() {
        int x = 5;
        int r;
        if (x == 5){
            r = 1;
        } else {
            r = 0;
        }

        return r;
    }
}