class While {
    public static void main(String[] args) {
        System.out.println((new WhileTest()).test());
    }
}

class WhileTest {
    public int test() {
        int i = 0;
        while (i < 5) {
            System.out.println(i);
            i = i + 1;
        }
        return i;
    }
}