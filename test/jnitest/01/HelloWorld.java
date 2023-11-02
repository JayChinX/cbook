
class HelloWorld {

    static {
        System.loadLibrary("helloworld");
    }

    private native String test();

    public static void main(String[] args) {
        System.out.println(System.getProperty("java.library.path"));
        System.out.println(new HelloWorld().test());
    }
}