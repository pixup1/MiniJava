class For {
    public static void main(String[] args) {
        System.out.println((new TestFor()).test());
    }
}

class TestFor {
    public int test() {
        int i;
        int s;
        s = 0;
        for (i = 0; i < 10; i = i + 1) {
            s = s + i;
        }
        return s;
    }
}