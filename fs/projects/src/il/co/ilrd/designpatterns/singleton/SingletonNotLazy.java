package il.co.ilrd.designpatterns.singleton;
/*
 * Thread safe but not lazy: the instantiation will happen as soon as the class loads, 
 * and not on the first getInstance() evokation.
 * 
 */
public class SingletonNotLazy implements Singleton {
	private static final Singleton SINGLE_INSTANCE = new SingletonNotLazy();
	
	private SingletonNotLazy() {}
	
	public static Singleton getInstance() {
		return SINGLE_INSTANCE;
	}
}


class TestSingletonSingletonNotLazy {
	public static void main(String[] args) {
		Singleton first = SingletonNotLazy.getInstance();
		Singleton second = SingletonNotLazy.getInstance();
		
		if (first == second) {
			System.out.println("Singleton!");
		} else {
			System.out.println("No!");
		}
		
		if (first.equals(second)) {
			System.out.println("Singleton!!");
		} else {
			System.out.println("No!!");
		}
	}
}
