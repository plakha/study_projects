package m9.d26.q1;

public class SingletonTest {
    public static void main(String[] args) {

	@SuppressWarnings("unused")
	Singleton<?> instance = Singleton.getInstance();
	instance = Singleton.getInstance();

    }
}
