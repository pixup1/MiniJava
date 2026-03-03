class Main {
    public static void main(String[] args) {
        System.out.println(new TestIncPre().test());
    }
}

class TestIncPre {
    public int test() {
        int x = 5;
        ++x;
        return x;
    }
}