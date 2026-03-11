class TestPostInc {
    public static void main(String[] args) {
        System.out.println(new PostInc().test());
    }
}

class PostInc {
    public int test() {
        int x = 5;
        x++;
        return x;
    }
}