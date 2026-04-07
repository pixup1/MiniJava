class DoWhile {
    public static void main(String[] args) {
        System.out.println((new DoWhileTest()).test());
    }
}

class DoWhileTest {
    public int test() {
        int i = 0;
        do {
            System.out.println(i);
            i = i + 1;
        } while (i < 5);
        return i;
    }
}
