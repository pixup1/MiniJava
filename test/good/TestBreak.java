class TestBreak {
    public static void main(String[] args) {
        System.out.println(new BreakTest().test(10));
    }
}

class BreakTest {
    public int test(int n) {
        int i = 0;
        while (i < n) {
            if (i == 5) {
                break;
            }
            i = i + 1;
        }
        return i;
    }

    
}
