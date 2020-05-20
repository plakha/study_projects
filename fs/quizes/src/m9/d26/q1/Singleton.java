package m9.d26.q1;

public class Singleton<T> {
    private static Singleton<?> instance = null;

    public static <T> Singleton<T> getInstance() {
	if (null == instance) {
	    System.out.println("Create Instance");
	    instance = new Singleton<T>();
	}

	System.out.println("return instance");

	return extracted();
    }

    @SuppressWarnings("unchecked")
    private static <T> Singleton<T> extracted() {
	return (Singleton<T>) instance;
    }

}
