class TestContinue {
    public static void main(String[] args) {
        System.out.println(new ContinueTest().test(10));
    }
}

class ContinueTest {
    public int test(int n) {
        int i = 0;
        while (i < n) {
            i = i + 1;
            if (i == 5) {
                continue;
            }
        }
        return i;
    }
}