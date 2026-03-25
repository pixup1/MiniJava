class Float {
    public static void main(String[] args) {
        System.out.println(new TestFloat().test());
    }
}

class TestFloat {
    public float test() {
        float x;
        x = 1.0f + 2.5f;
        return x;
    }
}